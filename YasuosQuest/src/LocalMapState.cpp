#include "../headers/stdafx.h"
#include "../headers/LocalMapState.h"
#include "../headers/StateMachine.h"
#include "../headers/InputManager.h"
#include "../headers/Level.h"
#include "../headers/Achievments.h"
#include "../headers/Player.h"
#include "../headers/MessageWindow.h"


LocalMapState::LocalMapState(StateMachine* s_machine) 
		: hud_window(s_machine->getGraphics()->getSize().x, s_machine->getGraphics()->getSize().y), 
		  log_window(0, 0, 300, 200, 12),
		GameState(s_machine) {

	
	i_manager = new InputManager(*s_machine);
	notifications_window = new MessageWindow(s_machine->getGraphics()->getSize().x / 2, 100, 200, 200, 64);
	id = 0;

	if (loadTextures()){

		if (!font.loadFromFile("arial.ttf")){ std::cout << "Could not load font" << std::endl;	}

		num_level = 1;

		createLevel(num_level);
		level_up_points.push_back(5);
		level_up_points.push_back(10);
		level_up_points.push_back(50);
		level_up_points.push_back(70);
		level_up_points.push_back(100);
		level_up_points.push_back(110);
		level_up_points.push_back(130);
		level_up_points.push_back(150);
		level_up_points.push_back(170);
		createPlayer();	

		hud_window.setFillColor(sf::Color(0, 0, 0, 120));
		hud_window.setSize(sf::Vector2f((float)s_machine->getGraphics()->getSize().x, 40));
		hud_window.setPosition(0, 0);
		hud_window.setPlayerAttributesWindow(player);
		
		//Set the log window under the hud window and to the far right
		log_window.setPosition(s_machine->getGraphics()->getSize().x - log_window.getSize().x - 32, s_machine->getGraphics()->getSize().y - log_window.getSize().y - 68);

		hurt_buffer.loadFromFile(HURT_SOUND);
		attack_buffer.loadFromFile(ATTACK_SOUND);
		die_buffer.loadFromFile(DIE_SOUND);

	}
	else{	std::cout << ERROR_LOADING_SPRITE_SHEET << std::endl; }


}


LocalMapState::~LocalMapState(){

	delete currentLevel;
}




/****************************************************************************************************************************
*
*												Initializing Functions
*
****************************************************************************************************************************/


void LocalMapState::createLevel(int map_num) {
	
	currentLevel = new Level(this, map_num, &font);
	if (player){
		player->setList(&currentLevel->getEntities());
		currentLevel->addEntity(player);
	}
}


bool LocalMapState::loadTextures(){

	//load the location for each texture image
	const int size = 1;
	std::string textures_list[size];
	textures_list[0] = { PLAYER_SPRITE_SHEET };

	//Using one texture reference to load all textures.
	sf::Texture texture;
	//Load all textures
	for (int i = 0; i < size; i++){

		std::string sprite_sheet = textures_list[i];

		if (!texture.loadFromFile(sprite_sheet, sf::Rect<int>(0, 0, 0, 0))){

			return false;

		}
		else{

			texture_map_list.insert(std::pair<std::string, sf::Texture>(sprite_sheet, texture));
		}
	}

	return true;
}


void LocalMapState::createPlayer(){
	int MAX_ITEMS = 2;
	int MAX_SPELLS = MAX_ITEMS;

	player = new Player(texture_map_list.at(PLAYER_SPRITE_SHEET), currentLevel, 0, 3);
	player->initAttributes(1);
	player->setID( 1 );

	sSpell* spells = new sSpell[MAX_SPELLS];
	sItem* items = new sItem[MAX_ITEMS];

	std::cout << "Items before address" << items << std::endl;
	std::cout << "Spells before address " << spells << std::endl;
	for (int i = 0; i < MAX_ITEMS; i++){

		std::string names("Sword ");
		std::string item_num = std::to_string(i);
		std::string result = names + item_num;

		items->Category = ItemCategories::WEAPON;
		items->Flags = 0;
		strcpy_s(items->Name, item_num.c_str());
		strcpy_s(items->Description, "A short weak weapon");
		items->Price = 1;
		items->Size = 0.3f;
		items->Usage = 0;
		items->Value = i*2;
		items->Weight = 1.0f;
		//Since items and spells have the same max count, this is fine


		strcpy_s(spells->Name, "entity");
		strcpy_s(spells->Description, "Fireball");
		spells->Chance = 10;
		spells->CureClass = 0;
		spells->Distance = 4.0;
		spells->DmgClass = 0;
		spells->Effect = 0;
		spells->Range = 4.0;
		spells->Target = 0;
		
		items++;
		spells++;
	}

	items--;//Go back to last item and spell in list
	spells--;

	player->init(&font, items, spells, 0, 0);

	//Reinit some attributes
	player->definition.Experience = 0;
	player->setSpeed(1.5);
	player->definition.Attack = 4;
	player->definition.ChargeRate = 70.0f;         // Countdown rate to attack
	//player->setCharge(40.0f);

	player->addObserver(new Achievments());
	player->addObserver(this);//TODO entities may need to have LocalMapState observer also

	Terrain* terrain;
	int x = 0, y = 0;

	do{

		x = rand() % MAX_TERRAINS_ROW;
		y = rand() % MAX_TERRAINS_COL;
		terrain = currentLevel->getTerrain(x, y);
		if (terrain->isWalkable() && !terrain->isWater())
			break;

	} while (true);

	player->setPosition(x,240.0f);
	player->setList(&currentLevel->getEntities());//TODO tightly coupled

	currentLevel->addEntity(player);
	
}

void LocalMapState::updateMessages(Entity* entity, long elapsed){

	entity->updateMessage(elapsed);

	//Update game notification messages
	long messageTimer = 0;
	messageTimer = notifications_window->getMessageTimer();
	if (messageTimer > 0)//If message time exists, decrease its timer value
		notifications_window->setMessageTimer(messageTimer - elapsed);
	else{

		notifications_window->setMessage("", 0, sf::Color::Green);
	}
}


/****************************************************************************************************************************
*
*												Update Functions
*
****************************************************************************************************************************/

void LocalMapState::update(long elapsedTime){

	updateEntities(elapsedTime);

}



bool LocalMapState::updateEntities(long elapsed){

	float XMove, YMove;
	static long effectCounter = 0;
	bool ToProcess, DeadChar;

	// Update effect counter
	effectCounter += elapsed;

	// Loop through all characters on the current level
	for (std::size_t i = 0; i < currentLevel->getEntityCount(); i++){

		Entity* entity = currentLevel->getEntity(i);
		if (entity == NULL) continue;

		// Only update if enabled, not asleep or paralyzed
		bool enabled = entity->isEnabled();
		if (enabled) {

			// Update action timer if in use
			long actionTimer = entity->getActionTimer();//Todo make this a pointer
			if (actionTimer != 0) {//In use if the value is not zero

				actionTimer = actionTimer - elapsed;
				entity->setActionTimer(actionTimer);
				if (actionTimer < 0)//Action timer can't be less than zero, reset it to zero
					entity->setActionTimer(0);
			}

			// Update text message timer
			updateMessages(entity, elapsed);
			//TODO maybe check message timer to see if it's less than zero, the same way we did with actionTimer

			// Reset charge counter if attacking, spell, or item
			long action = entity->getAction();
			if (action == CHAR_ATTACK || action == CHAR_SPELL || action == CHAR_ITEM){
				
				log_window.addMessage(*entity->getLogMessage());
				entity->setCharge(0.0f);
			}

			// Kill character if no health left
			long healthPoints = entity->getHealth();
			if (healthPoints <= 0 && action != CHAR_DIE) {//If no health and they are still alive
				entity->setAction(CHAR_DIE, 0);
				action = CHAR_DIE;
				actionTimer = 0;
			}

			// Mark that processing can continue later on
			ToProcess = true;

			// Mark character as still alive
			DeadChar = false;

			long ailments = entity->getAilments();
			checkAilments(ailments);

			// Process non-idle, non-walk actions
			if (action != CHAR_IDLE && action != CHAR_MOVE && !actionTimer) {
				//TODO wrap switch case in if statement for ToProcess
				//Less redundant code this way.
				switch (action) {

				case CHAR_ATTACK:
					// Process attack
					if (ToProcess == true){
						entity->attack();
					}
					break;

				case CHAR_SPELL:
					// Manually cast a spell
					//if (m_SpellController != NULL && m_MSL != NULL && ToProcess == TRUE) {
					//m_SpellController->Add(CharPtr->SpellNum, CharPtr, CharPtr->SpellTarget, nCharPtr->x_pos, CharPtr->y_pos,
					//CharPtr->ZPos, 
					//CharPtr->TargetX, 
					//	CharPtr->TargetY, 
					//CharPtr->TargetZ);
					//	}
					break;

				case CHAR_ITEM:
					if (ToProcess == true)
						//item(CharPtr, CharPtr, 
						//CharPtr->ItemNum, CharPtr->CharItem);
						break;

				case CHAR_DIE:
					Entity* attacker = entity->getAttacker();
					death(attacker, entity);
					DeadChar = true;   // Mark character as dead
					ToProcess = false; // Don't allow updates
					entity->setEnable( entity->getID(), false);
				
					break;
				}
			}//End process non-idle , non-walk action

			// Clear movement
			XMove = YMove = 0.0f;

			// Only continue if allowed (in case character died)
			if (ToProcess == true) {

				// Only allow updates if lock/timer not in use 
				if (enabled && !actionTimer && !entity->isLocked()) {
				
					entity->setAction(CHAR_IDLE);
					if (entity->getType() ==  CHAR_PC){
						player->pcUpdate(elapsed, &XMove, &YMove);

					}else{
						// Get movement
						entity->update(elapsed, &XMove, &YMove);
					}
					// Check for validity of movement (clear if invalid)
						if (checkMove(entity, &XMove, &YMove) == false) {
							XMove = YMove = 0.0f;
							entity->setAction(CHAR_IDLE);
					}
				}
				// Process movement of character
				processUpdate(entity, elapsed, XMove, YMove);
				// Increase action charge of character
				//	cout << "before charge set " << entity->getCharge() << endl;

				entity->setCharge(entity->getCharge() + (float)elapsed/1000.0f * entity->getChargeRate() );
				if (entity->getCharge() > 100.0f){
					entity->setCharge(100.0f);
				}
			}//End ToProcess == true case
		
			ailments = entity->getAilments();
			ToProcess = checkAilments(ailments);//If there are ailments (Sleeping etc), then we don't process

			// Process timed ailments (only on live characters)
			if (!DeadChar && ailments) {

				// Sleeping characters have 4% to wake up
				if (ailments & AILMENT_SLEEP && (rand() % 100)<4)
					entity->setAilments(ailments &= ~AILMENT_SLEEP);
				ailments = entity->getAilments();
				// Paralyzed character have 2% chance to recover
				if (ailments & AILMENT_PARALYZE && (rand() % 100) < 2){
					ailments &= ~AILMENT_PARALYZE;
					entity->setAilments(ailments);
				}

				ailments = entity->getAilments();
				// Posion removes 2 hp every 2 seconds
				if (ailments & AILMENT_POISON && effectCounter >= 4000) {
					long health = entity->getHealth();
					health = health - 2;
					entity->setHealth(health);
					entity->addMessage("Poison -2 HP", 500, sf::Color::Yellow);
				}
			}
		}//End ifEnabled()

	}//End looping all entities

	// Reset effect counter (after 4 seconds)
	if (effectCounter >= 4000)
		effectCounter = 0;

	return true;

}


bool LocalMapState::processUpdate(Entity *Character, long elapsed, float XMove, float YMove){

	// Move playable character
	if (Character == player){
		Character->move(elapsed, XMove, YMove);

	}
	//Move another way if the current movement direction is blocked
	else{ //Move NPC character


		if (!Character->move(elapsed, XMove, YMove)){ Character->calculateDirection(); }

	}
	return true;
}



void LocalMapState::render(){

	sf::RenderWindow* graphics = getStateMachine()->getGraphics();

	currentLevel->drawLevel(graphics);
	drawHud(graphics);
	drawLogWindow(graphics);
	drawNotifcation(graphics);
	for (std::size_t i = 0; i < currentLevel->getEntityCount(); i++){

		Entity* e = currentLevel->getEntity(i);
		if (e == NULL){ continue; }

		drawEntity(graphics, e);
	}
}


/****************************************************************************************************************************
*
*												Draw Functions
*
****************************************************************************************************************************/


void LocalMapState::drawEntity(sf::RenderWindow* graphics, Entity* e){

	
	e->draw(graphics);
}

void LocalMapState::drawLogWindow(sf::RenderWindow* graphics){

	log_window.draw(graphics);
}

void LocalMapState::drawHud(sf::RenderWindow* graphics){
	Entity* selected_entity = NULL;

	for (std::size_t i = 0; i < currentLevel->getEntityCount(); i++){

		Entity* e = currentLevel->getEntity(i);
		if (e == NULL){ continue; }
		if (e->hasSelectedFocus()){
			selected_entity = e;
			break;
		}
	}

	if (selected_entity){

		hud_window.setSelectedEntityWindow(selected_entity);
	}
	else{

		hud_window.clearSelectedEntityWindow();
	}

	hud_window.setPlayerAttributesWindow(player);
	hud_window.draw(graphics);
}

void LocalMapState::drawNotifcation(sf::RenderWindow* graphics){

	notifications_window->draw(graphics);

}

/****************************************************************************************************************************
*
*												Getters and setter Functions
*
****************************************************************************************************************************/

void LocalMapState::setNotification(std::string msg, long timer, sf::Color color){

	notifications_window->setMessage(msg,  timer, color);
	notifications_window->setPosition((float)(getStateMachine()->getGraphics()->getSize().x / 2), 100.0f);

}

int LocalMapState::getId(){

	return id;
}

sf::Vector2u LocalMapState::getWindowGraphicSize(){

	//getStateMachine()->getGraphics();
	return this->getStateMachine()->getGraphics()->getSize();

}

bool LocalMapState::checkAilments(long ailments){

	// Don't allow an update if asleep or paralyzed
	
	if ((ailments & AILMENT_SLEEP) || (ailments & AILMENT_PARALYZE))
		return false;

	return true;
}


/****************************************************************************************************************************
*
*												Check Functions
*
****************************************************************************************************************************/


bool LocalMapState::checkMove(Entity *Character, float *XMove, float *YMove){

	//Entity *CharPtr;
	//float XDiff, YDiff, Dist;
	//float Radius1, Radius2;
	float x_pos, y_pos;

	// Error checking
	if (Character == NULL)
		return false;  // Don't allow movement

	x_pos = Character->getPosition().x + (*XMove);
	y_pos = Character->getPosition().y + (*YMove);

	//Check if player has reached an exit
	//Get tile at player's position
	int tile_x_coordinate = (int)x_pos / Terrain::TILE_WIDTH;
	int tile_y_coordinate = (int)y_pos / Terrain::TILE_HEIGHT;

	Terrain* tile = currentLevel->getTerrain(tile_x_coordinate, tile_y_coordinate);
	if (tile == NULL){	return false; }

	//TODO move this code statement to another place
	if ( tile->isExit() ){

		std::cout << "exit we have" << std::endl;
		if ( num_level + 1 <= FINAL_LEVEL){//Advance to next level
			createLevel(++num_level);

		}
		currentLevel->addEntity(player);
		return false;
	}

	/*
		// Get character's X/Z radius
		sf::IntRect rect = Character->getTextureRect();
		Radius1 = std::max(rect.width - rect.left, rect.height - rect.top) * 0.5f;
		Character->setTextureRect(rect);
	
		//Character->setBounds(rect.left, rect.top, 0.0, rect.width, rect.height, 0.0);
		// Check movement against other characters
		for (std::size_t i = 0; i < currentLevel->getEntityCount(); i++){
			CharPtr = currentLevel->getEntity(i);
			if (CharPtr == NULL) continue;

			// Don't check against self or disabled characters
			if (Character != CharPtr && CharPtr->isEnabled()) {
				// Don't check against other PC characters
				if (Character->getType() == CHAR_PC && 	CharPtr->getType() == CHAR_PC)
					break;

				// Get distance between characters
				XDiff = (float)fabs(x_pos - CharPtr->getPosition().x);
				YDiff = (float)fabs(y_pos - CharPtr->getPosition().y);
				Dist = XDiff*XDiff + YDiff*YDiff;

				// Get checking character's X/Y bounding radius
				sf::IntRect other_rect = CharPtr->getTextureRect();
				Radius2 = std::max(other_rect.width - other_rect.left, other_rect.height - other_rect.top) * 0.5f;
				CharPtr->setTextureRect(other_rect);
				//Character->setBounds(other_rect.left, other_rect.top, 0.0, other_rect.width, other_rect.height, 0.0);

				if (rect.contains(45,45))
					return false;
				// Don't allow movement if intersecting
				if (Dist <= (Radius1*Radius1 + Radius2*Radius2))
					return false;
			}
		}

	*/

	// Bounds check movement if MinX != MaxX
	/*	if (Character->MinX != Character->MaxX) {
	if (x_pos < Character->MinX || x_pos > Character->MaxX)
	*XMove = 0.0f;
	if (y_pos < Character->MinY || y_pos > Character->MaxY)
	*YMove = 0.0f;

	// Return no movement at all
	if (!(*XMove) && !(*YMove))
	return false;
	*/

	if (Character->MinX != Character->MaxX) {
		if (x_pos < 0 || x_pos > 1024)
			*XMove = 0.0f;
		if (y_pos < 0 || y_pos > 768)
			*YMove = 0.0f;

		// Return no movement at all
		if (!(*XMove) && !(*YMove))
			return false;

	}
	// Call overloaded check custom collisions (maps, etc)
	//	if (ValidateMove(Character, XMove, YMove, ZMove) == FALSE)
	//return false;  // Don't allow movement

	return true;
}





/****************************************************************************************************************************
*
*												Event Functions
*
****************************************************************************************************************************/

//Handles all game events eg. Mouse and Window click events.
void LocalMapState::handleEvents(long elapsed){

	
}

void LocalMapState::handleInput(long elapsed){

	Command* command = i_manager->handleKeyPresses();
	if (command){//LocalMapState is the invoker of Command objects
		command->execute(player, elapsed);
	}

	command = i_manager->handleMousePresses();
	if (command){//LocalMapState is the invoker of Command objects
		command->execute(player, elapsed);
	}
}

void LocalMapState::onEnter(){
	//Begin playing local map music
	playMusic(LOCAL_MAP_MUSIC);
}

void LocalMapState::onExit(){

	music.stop();
}


void LocalMapState::onNotify(Entity& entity, Event event){

	switch (event){

	case EVENT_ATTACK:
		//updateNotification(entity.getEntityType() + std::string(entity.getMessage().getString()), 500, 500);
		playSound(attack_buffer);
		break;

	case EVENT_HURT:
		//updateNotification(entity.getEntityType() + std::string(entity.getMessage().getString()), 500, 500);
		playSound(hurt_buffer );
		break;

	case EVENT_DIE:
		//updateNotification(entity.getEntityType() + std::string(entity.getMessage().getString()), 500, 500);
		playSound(die_buffer);
		break;

		// Handle other events, and update_...			
	}
}



//Plays long running music clip
bool LocalMapState::playMusic(std::string path){

	if (!music.openFromFile(path))
	return false; // error

	music.setLoop(true);
	music.play();
	return true;
}

//Plays short running audio clip
bool LocalMapState::playSound(sf::SoundBuffer& clip){

	sound.setBuffer(clip);
	sound.play();
	return true;

}



bool LocalMapState::pCDeath(Entity *Character) { 
	
	setNotification("Game Over", 10000, sf::Color::Red);
	return true;
}

bool LocalMapState::nPCDeath(Entity *Character) { 

	
	return true; 

}

bool LocalMapState::death(Entity *Attacker, Entity *Victim){


	// If a PC or NPC dies, then don't remove from list
	if (Victim->getType() == CHAR_PC || Victim->getType() == CHAR_NPC) {

		// Mark this as disabled so no updates
		Victim->setEnable(Victim->getID(), false );

		// Call outside death function for PC's
		if (Victim->getType() == CHAR_PC)	pCDeath(Victim);
		
		else{	nPCDeath(Victim);	}
	}
	else {//Enemy died

		// Give attacker the victim's (enemies) experience
		if (Attacker != NULL) {
			
			if (experience(Attacker, Victim->definition.Experience)){

				checkLeveledUp(Attacker);
			}
			Attacker->incrementKillCount();
			
			//Display an in-game system log message 
			sf::Text msg;
			msg.setFont(font);
			msg.setCharacterSize(12);
			msg.setColor(sf::Color::Green);
			msg.setString(Attacker->getEntityType() + " killed " + Victim->getEntityType());
			log_window.addMessage(msg);
			
			msg.setString(Attacker->getEntityType() + " gained +" + std::to_string(Victim->definition.Experience) + " XP ");
			msg.setColor(sf::Color::Green);
			log_window.addMessage(msg);
		}

		// Drop this's money
		//	if (m_MIL != NULL && Victim->definition.Money)
		//	DropMoney(Victim->x_pos, Victim->y_pos, Victim->ZPos, \
				//	Victim->definition.Money);

		// Randomly drop an item (as specified in definition)
		//	if ((rand() % 100) < Victim->definition.DropChance)
		//	DropItem(Victim->x_pos, Victim->y_pos, Victim->ZPos,	Victim->definition.DropItem);

		// Decrease mesh count and release if no more
		//m_Meshes[Victim->definition.MeshNum].Count--;
		//	if (!m_Meshes[Victim->definition.MeshNum].Count) {
		//m_Meshes[Victim->definition.MeshNum].Mesh.Free();
		//	m_Meshes[Victim->definition.MeshNum].Animation.Free();
		//}

		// Remove dead Entity from list
		currentLevel->removeEntity(Victim);
		//m_thisParent = Victim->Next;

		//if (Victim->Next != NULL)
		//Victim->Next->Prev = Victim->Prev;

		//if (Victim->Prev == NULL && Victim->Next == NULL)
		//	m_thisParent = NULL;

		///	Victim->Prev = Victim->Next = NULL;
		//delete Victim;
	}

	onNotify(*Victim, EVENT_DIE);
	return true;
}


//Adds experience to the given entity
bool LocalMapState::experience(Entity* entity, long Amount){
	
	if (entity){

		entity->addExperience(Amount);
		return true;
	}
	else 
		return false;
}

void LocalMapState::checkLeveledUp(Entity *entity ){

	if (entity == player && hasLeveledUp(entity->getExperience())){

		player->levelUp();
	}
}

bool LocalMapState::hasLeveledUp(int amount){
	bool isLeveled = false;

	std::cout << " Level up points is " << level_up_points.front() << std::endl;
	std::cout << " Amount is " << amount << std::endl;
	if ( (!level_up_points.empty() ) && amount >= level_up_points.front()){

		level_up_points.pop_front();
		isLeveled = true;
	}
	
	return isLeveled;
}


Entity* LocalMapState::findEntityAtCoordinate(sf::Vector2i coords){

	Entity* entity_at_coordinate = NULL;

	std::vector<Entity*>entities_list = currentLevel->getEntities();
	for (std::vector<Entity*>::iterator it = entities_list.begin(); it != entities_list.end(); it++){

		Entity* entity = (*it);

		if (entity->contains(sf::Vector2f((float)coords.x, (float)coords.y)))
			entity_at_coordinate = entity;
	}
	return entity_at_coordinate;
}

//Reset all entities selected focus attribute except for the one passed as a argument
void LocalMapState::resetAllEntitiesFocusExcept(Entity* selected_entity){
	
	std::vector<Entity*>entities_list = currentLevel->getEntities();

	for (std::vector<Entity*>::iterator it = entities_list.begin(); it != entities_list.end(); it++){

			Entity* entity = (*it);

			if (entity != selected_entity && entity->hasSelectedFocus())
				entity->setAsFocusedEntity(false);
	}


}

void LocalMapState::resetAllEntitiesFocus(){

	std::vector<Entity*>entities_list = currentLevel->getEntities();

	for (std::vector<Entity*>::iterator it = entities_list.begin(); it != entities_list.end(); it++){

		Entity* entity = (*it);

		if (entity->hasSelectedFocus())
			entity->setAsFocusedEntity(false);
	}
}
