#include "../headers/stdafx.h"
#include "../headers/Entity.h"
#include "../headers/Level.h"
#include "../headers/Route.h"
#include "../headers/LocalMapState.h"
#include "../headers/FocusedAttributesWindow.h"

//int row the row of the tilesheet sprite sprite
//int col the col of the tilesheet for sprite
Entity::Entity(sf::Texture& texture, Level* level, int row, int col) {


	source.x = 0;
	source.y = 0;
	kills = 0;
	log_message = new sf::Text();
	sprite.setTexture(texture);

	this->current_level = level;
	list = NULL;

	m_Font = NULL;  // Clear cFont pointer
	m_MIL = NULL;  // Clear MIL pointer
	m_MSL = NULL;  // Clear MSL pointer

	int single_sprite_width = int(texture.getSize().x / NUM_SPRITES_IN_ROW); //TODO Assumming there are 4 frames
	int single_sprite_height = int(sprite.getGlobalBounds().height / NUM_SPRITES_IN_COL);
	sprite.setTextureRect(sf::Rect<int>(0, 0, single_sprite_width, single_sprite_height));
	
	//m_thisParent = NULL;  // Clear this list
	//m_Numthiss = 0;

	//m_definitioninitionFile[0] = 0;     // Clear definition filename

	//m_NumMeshes = 0;     // Clear mesh data
	//m_Meshes = NULL;
	//m_TexturePath[0] = 0;

	//m_NumAnimations = 0;     // Clear animation data
	//m_Animations = NULL;

	//m_SpellController = NULL;  // Clear spell controller
	selectSpriteSet(row, col);
	setMessageTimer(1000);

}


void Entity::initAttributes(int num_level){



	// Abilities
	definition.Agility = (rand() % 3 + 1) + num_level * 2;            // Agility ability
	definition.Attack = ((rand() % 2) + 1)*num_level;   // Attack ability
	definition.Defense = ((rand() % 2) + 1) *num_level;           // defense ability
	definition.Resistance = (rand() % 3 + 1) + num_level * 2;// Magic resistance ability
	definition.Mental = (rand() % 3 + 1) + num_level * 2;            // Mental ability
	definition.ToHit = 700;              // Chance to hit
	definition.Charge = (float)(rand() % 101);

	// Attributes
	definition.HealthPoints = (rand() % num_level + 1) * 10;       // # health points (maximum)
	definition.ManaPoints = (rand() % 3 + 1) + num_level * 2;         // # mana points (maximum)
	definition.Level = num_level;              // Experience num_level
	definition.Experience = (rand() % num_level + 1) * 2;         // Experience points

	// Inventory
	definition.ItemFilename[MAX]; // CharICS filename 
	definition.Weapon = 0;             // Equipped Weapon
	definition.Armor = 0;              // Equipped Armor
	definition.Shield = 0;             // Equipped Shield
	definition.Accessory = 0;          // Equipped Accessory

	// Dropping item data
	definition.DropChance = 1;         // % of dropping item when killed
	definition.DropItem = 1;           // Item # to drop when killed

	// Attack/Magic chances and effects
	definition.Range = 50.1;              // Attack range
	definition.ChargeRate = (float)(rand() % 40) + 40.0f;         // Countdown rate to attack
	definition.ToAttack = (rand() % num_level + 10) * 10;           // Percent to attack
	definition.ToMagic = 1;            // Percent to use magic
	definition.EffectChance = 1;       // Chance of attack effect occuring
	definition.Effects = 1;            // Bit flags of attack effects


	//this->Definition = 0;
	this->AI = CHAR_WANDER;                 // STAND, WANDER, etc
	this->Enabled = true;         // Enabled flag (for updates)
	this->current_health = this->definition.HealthPoints;
	this->ManaPoints = 10;
	this->Ailments = 0;           // Ailments against character
	this->Action = CHAR_MOVE;             // Current action

	this->Locked = false;             // Specific action lock
	this->ActionTimer = 0;        // Lock action countdown timer

	this->Attacker = NULL;     // Attacking character (if any)
	this->Victim = NULL;   // Character to attack

	this->SpellNum = 0;           // Spell to cast when ready
	this->SpellTarget = 0;        // Target type of spell
	this->TargetX = this->TargetY = 0; // Spell target coords

	this->ItemNum = 0;             // Item to use when ready
	this->CharItem = NULL;      // Item to remove from inventory

	this->Distance = 5.0;           // Follow/Evade distance
	this->TargetChar = NULL;   // Character to follow

	this->NumPoints = 0;          // # points in route
	this->CurrentPoint = 0;       // Current route point

	this->messageTimer = 1000;       // Text message timer

	long  Money = (rand() % num_level) * rand() % 5;              // Amount of money
	if (rand() % 2 == 0){

		definition.Speed = 1.2;
	}
	else{

		definition.Speed = 1.4;
	}
	

	//definition.MagicSpells[2];     // Bit flags to mark known spells
	//long  MeshNum;            // Mesh/anim # to load

}


bool Entity::init(sf::Font* font, sItem *mIL, sSpell *MSL, long NumAnimations, sCharAnimationInfo *Anims){

	// Get font object pointer
	m_Font = font;
	//current_message.setFont(*m_Font);
	log_message->setFont(*m_Font);
	log_message->setCharacterSize(12);
	
	entity_type_text.setFont(*m_Font);
	entity_type_text.setCharacterSize(16);

	// Store MIL and MSL pointer

	m_MIL = mIL;
	m_MSL = MSL;

	entity_sound = new std::string[MAX_SOUNDS];
	entity_sound[0] = "audio/attack1.ogg";
	entity_sound[1] = "audio/hurt1.ogg";
	entity_sound[2] = "audio/die1.ogg";

	// Store spell controller pointer
	//m_SpellController = SpellController;

	return true;
}

Entity::~Entity(){

	delete m_Font;
	delete current_level;
}

/*
* @param xpos and ypos: The amount in pixels to check if is valid move
*/
bool Entity::isValidLevelMove(int xpos, int ypos) {

	if (xpos / 32 < 0 || ypos / 32 < 0 || xpos/32 >= MAX_TERRAINS_ROW || ypos/32 >= MAX_TERRAINS_COL) return false;

	Terrain* terrain = current_level->getTerrain(xpos/32, ypos/32);

	if (terrain != NULL && terrain->isWalkable() && !terrain->isWater()) return true;

	return false;
}


void Entity::setAsFocusedEntity(bool val){

	is_focused = val;

}

bool Entity::hasSelectedFocus(){

	return is_focused;
}

bool Entity::hasMessageTimeExpired(){

	return messageTimer <= 0;
}


MessageWindow& Entity::getMessageWindow(){

	return current_message;
}


bool Entity::update( long Elapsed, float *XMove, float *YMove){

	float MoveX, MoveY, Speed;
	float XDiff, YDiff, Dist, Radius;
	//float y1, y2;
	//long  i, SpellNum;
	//bool SpellCast;
//	Entity *CharPtr;

	// Clear movements and action
	MoveX = MoveY =  0.0f;

	// Calculate movement speed
	Speed = (float)Elapsed / 1000.0f * getSpeed(this);

		// Move Character based on their type
		switch (this->AI) {

		case CHAR_STAND:
			break;

		case CHAR_WANDER:
			// Calculate new distance and direction if needed
			this->Distance -= Elapsed;
			if (this->Distance <= 0.0f) {

				// Calculate a new distance to travel
				this->Distance = (float)(rand() % 2000) + MAXIMUM_WALKING_DISTANCE_OFFSET;

				// Calculate a new direction
				calculateDirection();
			}

			// Process walk or stand still

			if (this->Distance > MINIMUM_WALKING_DISTANCE) {

				MoveX = (float)sin(this->Direction) * Speed;
				MoveY = (float)cos(this->Direction) * Speed;
				this->Action = CHAR_MOVE;
			}
			else {//The padding in between zero and the min walking distance
				//With out this padding, the entity will never idle,eg. continously walk and changing directions
				// Stand still for random amount of time
				this->Action = CHAR_IDLE;
			}

			break;

		case CHAR_ROUTE:

			// Determine if character has reached point
			XDiff = (float)fabs(this->sprite.getPosition().x - this->routes[this->CurrentPoint].XPos);
			YDiff = (float)fabs(this->sprite.getPosition().y - this->routes[this->CurrentPoint].YPos);
			Dist = XDiff*XDiff + YDiff*YDiff;
			Radius = getXYRadius(this) * 0.25f;

			// Go to next point if reached
			if (Dist < (Radius*Radius)) {
				this->CurrentPoint++;
				if (this->CurrentPoint > this->NumPoints)
					this->CurrentPoint = 0;

				// Calculate new differences and distance
				XDiff = (float)fabs(this->sprite.getPosition().x - this->routes[this->CurrentPoint].XPos);
				YDiff = (float)fabs(this->sprite.getPosition().y - this->routes[this->CurrentPoint].YPos);
				Dist = XDiff*XDiff + YDiff*YDiff;
			}

			// Setup movement towards target
			Dist = (float)sqrt(Dist);
			if (Speed > Dist)
				Speed = Dist;

			MoveX = (this->routes[this->CurrentPoint].XPos - this->sprite.getPosition().x) / Dist * Speed;
			MoveY = (this->routes[this->CurrentPoint].YPos - this->sprite.getPosition().y) / Dist * Speed;
			// Set new direction
			this->Direction = (float)atan2(MoveX, MoveY);

			// Set new action
			this->Action = CHAR_MOVE;
			break;

		case CHAR_FOLLOW:
			if (this->TargetChar != NULL) {

				// Check distance between thiss
				XDiff = (float)fabs(this->sprite.getPosition().x - this->TargetChar->sprite.getPosition().x);
				YDiff = (float)fabs(this->sprite.getPosition().y - this->TargetChar->sprite.getPosition().y);
				Dist = XDiff*XDiff + YDiff*YDiff;

				// Update if further then distance
				if (Dist > (this->Distance*this->Distance)) {

					// Setup movement towards target
					Dist = (float)sqrt(Dist);
					if (Speed > Dist)
						Speed = Dist;
					MoveX = (this->TargetChar->sprite.getPosition().x - this->sprite.getPosition().x) / Dist * Speed;
					MoveY = (this->TargetChar->sprite.getPosition().y - this->sprite.getPosition().y) / Dist * Speed;

					// Set new direction
					this->Direction = (float)atan2(MoveX, MoveY);

					// Set new action
					this->Action = CHAR_MOVE;
				}
			}
			break;

		case CHAR_EVADE:
			if (this->TargetChar != NULL) {

				// Check distance between thiss
				XDiff = (float)fabs(this->sprite.getPosition().x - this->TargetChar->sprite.getPosition().x);
				YDiff = (float)fabs(this->sprite.getPosition().y - this->TargetChar->sprite.getPosition().y);
				Dist = XDiff*XDiff + YDiff*YDiff;

				// Update if closer then distance
				if (Dist < (this->Distance*this->Distance)) {

					// Setup movement away from target
					Dist = (float)sqrt(Dist);
					if (Speed > Dist)
						Speed = Dist;
					MoveX = -(this->TargetChar->sprite.getPosition().x - this->sprite.getPosition().x) / Dist * Speed;
					MoveY = -(this->TargetChar->sprite.getPosition().y - this->sprite.getPosition().y) / Dist * Speed;

					// Set new direction
					this->Direction = (float)atan2(MoveX, MoveY);

					// Set new action
					this->Action = CHAR_MOVE;
				}
			}

			break;
		}//End switch
		checkAttack(CHAR_MONSTER, CHAR_PC, Radius, Dist, XDiff, YDiff, MoveX, MoveY);
	*XMove = MoveX;
	*YMove = MoveY;

	

	return true;
}

void Entity::updateMessage(long elapsed){

	MessageWindow& message_window = getMessageWindow();

	if (!message_window.hasMessageTimeExpired()){//If message time exists, decrease its timer value

		message_window.setMessageTimer(message_window.getMessageTimer() - elapsed);
	}
	else{

		getNextMessage();
	}

	float x = getPosition().x;
	float y = (getPosition().y - sprite.getLocalBounds().height - 32); 
	current_message.update(x, y, elapsed);
	
}




/*
*Process a given entity for an attack
*@param attacking_entity_type is the entity doing the attack
*@param attakee_entity_type the entity getting attacked
*/
void Entity::checkAttack(long attacking_entity_type, long attakee_entity_type, float Radius, float Dist, float XDiff, float YDiff, float &MoveX, float &MoveY){

	// Process entity actions if at full charge
	//if (this->getType() == CHAR_MONSTER &&  this->getCharge() >= 100.0f)
	if (this->getType() == attacking_entity_type &&  this->getCharge() >= 100.0f) {
		// Determine chance of attacking
		int rand_chance = rand() % 100;

		if ((rand_chance <= this->definition.ToAttack)){
			// Scan through list and pick a character
			for (std::vector<Entity*>::iterator it = list->begin(); it != list->end(); it++){

				Entity* CharPtr = (*it);
				// Randomly pick enabled target (a PC),
				// and make sure the target is not hurt or dead.
				if (CharPtr != this
					&& CharPtr->Type == attakee_entity_type//If the current entity is the type we want to attack
					&& (rand() % 100) < 50
					&& CharPtr->Action != CHAR_DIE
					&& CharPtr->Action != CHAR_HURT) {

					// Get distance to target
					XDiff = fabs(this->sprite.getPosition().x - CharPtr->sprite.getPosition().x);
					YDiff = fabs(this->sprite.getPosition().y - CharPtr->sprite.getPosition().y);
					Dist = XDiff * XDiff + YDiff * YDiff;

					// Make sure in range to attack
					Radius = getXYRadius(this);

					Radius += this->definition.Range;
					// Attack if in range
					if ((Radius*Radius) >= Dist) {
						// Set attack data
						this->Victim = CharPtr;
						CharPtr->Attacker = this;

						if (Type != CHAR_PC){//Player does not need to do this
							
							// Clear movement
							MoveX = MoveY = 0.0f;
							// Point towards target character
							XDiff = CharPtr->sprite.getPosition().x - this->sprite.getPosition().x;
							YDiff = CharPtr->sprite.getPosition().y - this->sprite.getPosition().y;
							this->Direction = atan2(XDiff, YDiff);
						}
						// Perform attack action
						setAction(CHAR_ATTACK);
						break;//Once we found an enemy, we focus on it
					}
				}
			}
		}
		else{//Spells

			// Determine chance of spell casting
			//Long list of code omitted
		}
	}
}

float Entity::getXYRadius(Entity *character){
	float MinX, MaxX, MinY, MaxY;
	float x, y;

	// Error checking
	if (character == NULL)
		return 0.0f;

	MinX = character->sprite.getLocalBounds().left;
	MinY = character->sprite.getLocalBounds().top;
	MaxX = character->sprite.getLocalBounds().width;
	MaxY = character->sprite.getLocalBounds().height;

	x = (float)std::max(fabs(MinX), fabs(MaxX));
	y = (float)std::max(fabs(MinY), fabs(MaxY));

	return std::max(x, y);
}


bool Entity::move(long elapsed, float x, float y){

	float x_move = (float)(sprite.getPosition().x + (x * elapsed));
	float y_move = (float)(sprite.getPosition().y + (y * elapsed));

	if (isValidLevelMove((int)x_move, (int)y_move)){
		sprite.setPosition(x_move, y_move);
		entity_type_text.setPosition(x_move, y_move - 32);

		// Set new animation
		switch (Action){

		case CHAR_MOVE:

			const sf::Texture* texture = sprite.getTexture();

			int width = (int)sprite.getLocalBounds().width;//The Sprites' width
			int height = (int)sprite.getLocalBounds().height;//The Sprites' height

			if (source.x > 2){//Have we reached the last frame?

				//Reset the frame to the first animation
				source.x = 0;
			}

			int frame = (source.x * width) + selected_sprite_set_in_row;//The frame image to show

			float direction = getDirection();

			if (direction >= 1.0 && direction < 2.5)
				source.y = RIGHT;
			else if (direction >= 2.5 && direction < 4.0)
				source.y = UP;
			else if (direction >= 4.0 && direction < 6)
				source.y = LEFT;
			else
				source.y = DOWN;


			int direction_image = (source.y*height) + (selected_sprite_set_in_col);//The direction image to show

			//Display the specified portion (image) from the Entitysheet.
			sprite.setTextureRect(sf::Rect<int>(frame, direction_image, width, height));

			source.x++;//Move to next frame
		}

		return true;
	}

	return false;
}


void Entity::draw(sf::RenderWindow* graphics){


	drawStats(graphics);
	drawMessages(graphics);
	graphics->draw(sprite);

}


void Entity::drawStats(sf::RenderWindow* graphics){

	//The health of the entity
	drawHealth(graphics);
	graphics->draw(entity_type_text);
}

void Entity::drawMessages(sf::RenderWindow* graphics){

		//Check to see if the messages time to show has expired
		//If not, then draw the message

	if (current_message.hasMessage()){

		current_message.draw(graphics);

	}		
}



void Entity::drawHealth(sf::RenderWindow* graphics){

	//TODO add the below code in update instead of draw
	//Heath background
	sf::RectangleShape entity_health_text_bg;
	entity_health_text_bg.setFillColor(sf::Color(15, 15, 255, 155));
	entity_health_text_bg.setSize(sf::Vector2f(sprite.getLocalBounds().width, 8));
	entity_health_text_bg.setPosition(sprite.getPosition().x, sprite.getPosition().y - 8);

	sf::Text entity_health_text;
	const sf::String entity_status = std::to_string(getHealth());
	entity_health_text.setString(entity_status);
	entity_health_text.setFont(*m_Font);
	entity_health_text.setCharacterSize(16);
	entity_health_text.setPosition(entity_health_text_bg.getPosition().x + 4, entity_health_text_bg.getPosition().y + entity_health_text_bg.getSize().y / 2 - 16);
	entity_health_text.setColor(sf::Color::Green);

	//Render code
	graphics->draw(entity_health_text_bg);
	graphics->draw(entity_health_text);

}



void Entity::calculateDirection(){//Calculutes a new direction for the entity

	this->Direction = (float)(rand() % 360)*0.01744444f;
}

void Entity::setList(std::vector<Entity*>* list){

	this->list = list;
}

void Entity::addExperience(long amount){

	char Text[128];
	definition.Experience += amount;

	sprintf_s(Text, "+%lu XP", amount);
	addMessage(Text, 1000, sf::Color::Yellow);

}

void Entity::removeExperience(long amount){

	char Text[128];
	definition.Experience -= amount;

	sprintf_s(Text, "-%lu XP", amount);
	addMessage(Text, 1000, sf::Color::Red);
}

long Entity::getExperience(){

	return definition.Experience;
}

long Entity::getMana(){

	return definition.ManaPoints;
}

int Entity:: getLevel(){

	return definition.Level;
}

void Entity::levelUp(){

	definition.Level++;
	definition.HealthPoints += 2;
	definition.ManaPoints += 2;
	definition.Attack+= 1;
	definition.Defense += 1;
	//definition.ChargeRate += 0.2;
	definition.Agility+= 1;
	
	setHealth(definition.HealthPoints);
	
	char Text[128];
	sprintf_s(Text, "You have gained a level - Level %lu ", definition.Level);
	
	getLocalMap()->setNotification(Text, 5000, sf::Color::Yellow);
	sprintf_s(Text, "level +%lu ", definition.Level);
	addMessage(Text, 1000, sf::Color::Yellow);

}


void Entity::setMessage(char * text,  long timer, sf::Color color){

	current_message.setMessage( text, timer, color );

}


void Entity::setDirection(float dir){

	Direction = dir;
}

float Entity::getDirection(){

	return Direction;
}


void Entity::setID(int id){

	this->ID = id;

}

int Entity::getID(){

	return this->ID;
}

bool Entity::isEnabled(){

	return Enabled;
}

bool Entity::isLocked(){

	return Locked;
}


long  Entity::getActionTimer(){

	return ActionTimer;
}

long  Entity::getAction(){

	return Action;
}

bool Entity::setRoutes(long IDNum, long NumPoints, Route* Routes){

	CurrentPoint = 0;

	this->routes = Routes;
	return true;
}

bool Entity::attack(){

	if (Victim == NULL)
		return false;
	

	// Don't attack dead or hurt people
	if (Victim->Action == CHAR_DIE || Victim->Action == CHAR_HURT)
		return false;

	// Set attacker and victim
	Victim->Attacker = this;
	this->Victim = Victim;
	notify(*this, EVENT_ATTACK);

	// Return if hit missed
	if ((rand() % 1000) > getToHit(Victim)) {
		
		std::string miss_msg = getEntityType().c_str() + std::string(" missed!");
		log_message->setString(miss_msg);
		log_message->setColor(sf::Color::Yellow);
		addMessage(miss_msg.c_str(), 1000, sf::Color::Yellow);
		return false;
	}
	
	// Return if hit dodged
	if ((rand() % 1000) <= getAgility(Victim)) {
		std::string dodge_msg = getEntityType().c_str() + std::string(" dodged!");
		log_message->setString(dodge_msg);
		log_message->setColor(sf::Color::Yellow);
		addMessage(dodge_msg.c_str(), 1000, sf::Color::Yellow);
		return false;
	}

	// If this is asleep, randomly wake them up (50% chance)
	if (Victim->Ailments & AILMENT_SLEEP) {
		if ((rand() % 100) < 50)
			Victim->Ailments &= ~AILMENT_SLEEP;
	}

	// Attack landed, apply damage
	damage(Victim, true, getAttack(this), -1, -1);
	
	return true;

}

float Entity::getSpeed(Entity *Character){
	
	float Speed;

	// Error checking
	if (this == NULL)
		return 0.0f;

	// Calculate adjusted speed
	Speed = this->definition.Speed;

	if (this->Ailments & AILMENT_SLOW)
		Speed *= 0.5f;
	if (this->Ailments & AILMENT_FAST)
		Speed *= 1.5f;

	return Speed;
}

long Entity::getToHit(Entity* Character){

	long ToHit;

	// Calculate adjusted to hit
	ToHit = this->definition.ToHit;

	if (this->Ailments & AILMENT_BLIND)
		ToHit = (long)((float)ToHit * 0.75f);
	if (this->Ailments & AILMENT_HAWKEYE)
		ToHit = (long)((float)ToHit * 1.5f);

	return ToHit;
}

float Entity::getCharge(){
	
	float Charge;

	// Calculate adjusted charge
	Charge = this->definition.Charge;

	if (this->Ailments & AILMENT_SLOW)
		Charge = Charge * 0.75f;
	if (this->Ailments & AILMENT_FAST)
		Charge = Charge * 1.5f;

	return Charge;
}

float Entity::getChargeRate(){

	return definition.ChargeRate;
}


void Entity::setCharge(float value){

	definition.Charge = value;
}

Entity* Entity::getAttacker(){

	return Attacker;
}


long  Entity::getAgility(Entity* Character){

	long Agility;

	// Error checking
	if (this == NULL)
		return 0;

	// Calculate adjusted agility
	Agility = this->definition.Agility;

	if (this->Ailments & AILMENT_CLUMSY)
		Agility = (long)((float)Agility * 0.75f);
	if (this->Ailments & AILMENT_SUREFOOTED)
		Agility = (long)((float)Agility * 1.5f);

	return Agility;
}

long Entity::getAttack(Entity* Character){

	long Attack;

	// Calculate adjusted attack
	Attack = this->definition.Attack;

	// Adjust attack based on item value (in %(Value/100)+1)
	if (this->definition.Weapon != -1 && m_MIL != NULL) {

		Attack = (long)((float)Attack *  (((float)m_MIL[definition.Weapon].Value /100.0f) + 1.0f));
	}

	if (this->Ailments & AILMENT_WEAK)
		Attack = (long)((float)Attack * 0.5f);
	if (this->Ailments & AILMENT_STRONG)
		Attack = (long)((float)Attack * 1.5f);

	return Attack;


}

bool Entity::damage(Entity *Victim, bool PhysicalAttack, long Amount, long DmgClass, long CureClass){

	char Text[128];
	float Resist;
	float Range;
	long  DmgAmount;

	// Error checking
	if (Victim == NULL)
		return false;

	// Can't attack if already dead or being hurt (or not enabled)
	if ( Victim->Action == CHAR_DIE ||	Victim->Action == CHAR_HURT)
		return false;

	// Adjust for definition if physical attack
	if (PhysicalAttack == true) {

		// Random value for less/more damage (-+20%)
		Range = (float)((rand() % 20) + 90) / 100.0f;
		DmgAmount = (long)((float)Amount * Range);

		// Subtract for defense of victim (allow -20% difference)
		Range = (float)((rand() % 20) + 80) / 100.0f;
		DmgAmount -= (long)((float)getDefense(Victim) * Range);
	}
	else {
		// Adjust for magical attack
		Resist = 1.0f - ((float)getResistance(Victim) / 100.0f);
		DmgAmount = (long)((float)Amount * Resist);
	}

	// Bounds check value
	if (DmgAmount < 0)
		DmgAmount = 0;

	// Check for double damage
	if (Victim->definition.Class == DmgClass)
		DmgAmount *= 2;

	// Check for cure damage
	if (Victim->definition.Class == CureClass)
		DmgAmount = -(labs(DmgAmount) / 2);

	// If no physical damage is dealt then randomly deal 
	// 10-20% of damage from the original amount.
	if (!DmgAmount && PhysicalAttack == true) {
		Range = (float)((rand() % 10) + 10) / 100.0f;
		DmgAmount = (long)((float)Amount * Range);
	}

	// Subtract damage amount
	Victim->current_health -=  DmgAmount;

	// Set hurt status and display message
	if (DmgAmount > 0) {
		

		sprintf_s(Text, "-%lu HP", DmgAmount);
		std::string msg = Victim->getEntityType() + " loss " + std::to_string(DmgAmount) + " HP";
		log_message->setString(msg);
		log_message->setColor(sf::Color::Red);
		Victim->addMessage(Text, 1000, sf::Color::Red);

		// Only set hurt if any damage (and idle or moving)
		if (DmgAmount) {
			if (Victim->Action == CHAR_MOVE || Victim->Action == CHAR_IDLE)
				setAction( CHAR_HURT);
				notify(*Victim, EVENT_HURT);

		}
	}

	// Display cure amount
	if (DmgAmount < 0) {

		sprintf_s(Text, "+%lu HP", -DmgAmount);
		std::string msg = getEntityType() + " gained " +  std::to_string(DmgAmount) + " HP" ;
		log_message->setString(msg);
		log_message->setColor(sf::Color::Green);
		addMessage(Text, 1000, sf::Color::Green);
	}

	return true;

}
bool Entity::setEnable(long IDNum, bool enable){

	this->Enabled = enable;
	return true;
}



bool Entity::pCTeleport(Entity *Character, sSpell *Spell){
	
	return true;

}



long Entity::getDefense(Entity* Character){//TODO see if this should be another enemy or moved to main game class

	long Defense;

	// Error checking
	if (this == NULL)
		return 0;

	// Calculate adjusted defense
	Defense = this->definition.Defense;

	if (this->definition.Armor != -1 && m_MIL != NULL)
		Defense = (long)((float)Defense * (((float)m_MIL[this->definition.Armor].Value / 100.0f) + 1.0f));

	if (this->definition.Shield != -1 && m_MIL != NULL)
		Defense = (long)((float)Defense *                         \
		(((float)m_MIL[this->definition.Shield].Value / \
		100.0f) + 1.0f));

	if (this->Ailments & AILMENT_WEAK)
		Defense = (long)((float)Defense * 0.5f);
	if (this->Ailments & AILMENT_STRONG)
		Defense = (long)((float)Defense * 1.5f);

	// Bounds check value
	if (Defense < 0)
		Defense = 0;

	return Defense;
}

long Entity::getResistance(Entity* thisCharacter){

	long Resistance;

	// Error checking
	if (this == NULL)
		return 0;

	// Calculate adjusted resistance
	Resistance = this->definition.Resistance;

	if (this->Ailments & AILMENT_ENCHANTED)
		Resistance = (long)((float)Resistance * 0.5f);
	if (this->Ailments & AILMENT_BARRIER)
		Resistance = (long)((float)Resistance * 1.5f);

	return Resistance;

}


long Entity::getMental(Entity *Character){
	long Mental;

	// Error checking
	if (this == NULL)
		return 0;

	// Calculate adjusted mental
	Mental = this->definition.Mental;

	if (this->Ailments & AILMENT_DUMBFOUNDED)
		Mental = (long)((float)Mental * 0.5f);

	return Mental;
}



bool Entity::setActionTimer(long Timer){

	// Set new value
	this->ActionTimer = Timer;
	return true;
}

bool Entity::setAction(long Action, long AddTime){
	long MeshNum;

	// Make sure attack, spell, and item has supporting charge
	if (Action == CHAR_ATTACK || Action == CHAR_SPELL || Action == CHAR_ITEM) {

		if (this->getCharge() < 100.0f)
			return false;
	}

	// Set action
	this->Action = Action;

	// Play sound effect
	//ActionSound(this);

	// Get mesh number
	MeshNum = this->definition.MeshNum;
	// Set action time (or set to 1 is addtime = -1)
	if (AddTime == -1){
		this->ActionTimer = 1;
	}
	else{
		this->ActionTimer = AddTime; //+ m_Meshes[MeshNum].Animation.GetLength(m_Animations[Action].Name) * 30;
	}

	return true;

}


long Entity::getMessageTimer(){

	return messageTimer;
}

void Entity::setMessageTimer(long value){

	messageTimer = value;
}

sf::Text& Entity::getMessage(){

	return current_message.getMessage();
}

sf::Text* Entity::getLogMessage(){

	return log_message;
}


bool Entity::getNextMessage(){

	if (!messages.empty()){

		MessageWindow msg = messages.front();
		current_message.setMessage(msg.getMessage().getString(), msg.getMessageTimer(), msg.getMessageColor());
		messages.pop_front();
	}
	else{

		current_message.setMessage("", 0, sf::Color::Yellow);
	}

	return true;
}


bool Entity::addMessage(const char *Text, long Timer, sf::Color color){

	MessageWindow message_window;
	message_window.setMessage(Text, Timer, color);
	messages.push_back(message_window);
	return true;
}

bool  Entity::setBounds(float MinX, float MinY, float MinZ, float MaxX, float MaxY, float MaxZ){

	this->MinX = MinX;
	this->MinY = MinY;
	this->MaxX = MaxX;
	this->MaxY = MaxY;

	return true;
	
}

void Entity::setSpeed(float new_speed){

	this->definition.Speed = new_speed;
}

bool Entity::getBounds(float *MinX, float *MinY, float *MinZ, float *MaxX, float *MaxY, float *MaxZ){

	MinX = new float(this->MinX);
	MinY = new float(this->MinY);
	MaxX = new float(this->MaxX);
	MaxY = new float(this->MaxY);

	return true;

}

void Entity::incrementKillCount(){

	kills++;
	//Every time an enemy is killed, 
	//Check to see if we reached an achievment
	notify(*this, EVENT_ENEMY_KILLED);

}

int Entity::getKillCount(){

	return kills;
}


long Entity::getHealth(){

	return current_health;
}

void Entity::setHealth(long value){

	current_health = value;

}

std::string Entity::getEntityType(){

	return entity_type_text.getString();
}


void Entity::setEntityTypeText(std::string text){

	entity_type_text.setString( text );

}

void Entity::setEntityTypeTextColor(sf::Color color){

	entity_type_text.setColor(color);
}



long Entity::getAilments(){

	return Ailments;
}

void Entity::setAilments(long value){

	Ailments = value;
}

bool Entity::setAI(long value){

	AI = value;
	return true;
}

long Entity::getType(){

	return Type;

}

bool Entity::setType(long value){

	Type = value;
	return true;

}


LocalMapState* Entity::getLocalMap(){


	Observer* o = findObserver(0);
	if (o){

		return (LocalMapState*)(o);
	}

	return NULL;
}


/*
*@param col - The column of the wanted sprite set in the sprite sheet (offset by one,  starting at zero)
*@param row - The row of the wanted sprite set in the sprite sheet (offset by one, starting at zero)
*
*/
void Entity::selectSpriteSet(int row, int col){

	//Calculate which set of sprite sheet images to show
	int sprite_set_width = sprite.getTexture()->getSize().x / NUM_SPRITE_SETS_ROW_COUNT;//The single sprite sets width
	selected_sprite_set_in_row = (sprite_set_width * col);

	int sprite_set_height = sprite.getTexture()->getSize().y / NUM_SPRITE_SETS_COL_COUNT;//The single sprite sets height
	selected_sprite_set_in_col = sprite_set_height * row;

}


void Entity::simulateAi(){}//Virtual/abstract function

/**
* Calculates this Entitys' distance away from an another
*/
sf::Vector2f Entity::calculateDistance(sf::Sprite*opponent) {

	sf::Vector2f distance_away;

	float goal_pos_x = opponent->getPosition().x;
	float goal_pos_y = opponent->getPosition().y;

	//Distance formula. The distance between the Sprites
	distance_away.x = goal_pos_x - sprite.getPosition().x;
	distance_away.y = goal_pos_y - sprite.getPosition().y;
	return distance_away;
}


bool Entity::isInViewingDistance(sf::Sprite opponent) {


	sf::Vector2f position = opponent.getPosition();
	sf::FloatRect bounds = opponent.getLocalBounds();
	const sf::Rect<float> opponents_rect(position.x, position.y, 32, 32);
	return false;
	//return perimeter.intersects(opponents_rect);

}

bool Entity::contains(sf::Vector2f pos){

	return sprite.getGlobalBounds().contains(pos);
}
void Entity::setPosition(float x, float y){

	sprite.setPosition(x, y);
}
sf::Vector2f Entity::getPosition(){

	return sprite.getPosition();
}
int Entity::getNumRoutePoints(){


	return NumPoints;
}


void Entity::CalculateFollowMovement( float CharXPos, float CharZPos, // Coordinate of this
	float WalkSpeed, // Walking speed of char.
	float FollowXPos, float FollowZPos, // Coords of followed char.
	float FollowDistance, // Distance to follow at
	float *MoveX, float *MoveZ) // Variables for movement
{
	// Fix for faster distance checking
	FollowDistance *= FollowDistance;
	
	// Get distance between thiss
	float XDiff = (float)fabs(FollowXPos - CharXPos);
	float ZDiff = (float)fabs(FollowZPos - CharZPos);
	float Length = XDiff*XDiff + ZDiff*ZDiff;
	// If distance between thiss is less than allowed,
	// then just stand still.
	if (Length < FollowDistance) {
		*MoveX = *MoveZ = 0.0f;
		return;
	}
	// Calculate rate to move based on this walking speed
	Length = sqrt(Length);
	*MoveX = (CharXPos - FollowXPos) / Length * WalkSpeed;
	*MoveZ = (CharZPos - FollowZPos) / Length * WalkSpeed;
}

void Entity::CalculateEvadeMovement(
	float CharXPos, float CharZPos, // Coordinate of this
	float WalkSpeed, // Walking speed of char.
	float FollowXPos, float FollowZPos, // Coords of evaded char
	float EvadeDistance, // Distance to evade
	float *MoveX, float *MoveZ) // Variables for movement
{
	// Fix for faster distance checking
	//FollowDistance *= FollowDistance;
	// Get distance between thiss
	float XDiff = (float)fabs(FollowXPos - CharXPos);
	float ZDiff = (float)fabs(FollowZPos - CharZPos);
	float Length = XDiff*XDiff + ZDiff*ZDiff;
	// If distance between thiss is more than allowed,
	// then just stand still.
	if (Length > EvadeDistance) {
		*MoveX = *MoveZ = 0.0f;
		return;
	}
	// Calculate rate to move based on this walking speed
	Length = sqrt(Length);
	*MoveX = -((CharXPos - FollowXPos) / Length * WalkSpeed);
	*MoveZ = -((CharZPos - FollowZPos) / Length * WalkSpeed);
}


std::string Entity::getEntitySound(int index){
	if (index < 0 || index >= MAX_SOUNDS)
		return "";

	return entity_sound[index];

}

void Entity::setEntitySound(int index, std::string sound){
	
	if (index < 0 || index >= MAX_SOUNDS)
		return;

	this->entity_sound[index] = sound;

}
