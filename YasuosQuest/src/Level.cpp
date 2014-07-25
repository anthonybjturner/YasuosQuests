#include "../headers/stdafx.h"
#include "../headers/Level.h"

#include "../headers/Enemy.h"
#include "../headers/LocalMapState.h"
#include "../headers/GraphicsFwd.h"
#include "../headers/Route.h"

Level::Level(LocalMapState* local_map_state, int level, sf::Font* font) {

	if (loadTileTextures()){
		
		//Set paths
		std::string current_map_path = MAP_PATH + std::to_string(level) + std::string(FILE_EXTENTION);
		std::string current_entity_path = MAP_PATH + std::to_string(level) + "_entities" + std::string(FILE_EXTENTION);

		this->level = level;
		loadEntityTextures(level);
		loadLevel(current_map_path);
		createEntities(local_map_state, current_entity_path, level, font);
		
	}
	else
		std::cout << "Error loading textures" << std::endl;

}

bool Level::loadTileTextures(){

	//load the location for each texture image

	sf::Texture* texture = new sf::Texture();
	if (texture->loadFromFile(TILE_GRASS_TEXTURE)){

		grass_terrain.addTexture(texture);
		grass_terrain.setMovementCost(1);
		grass_terrain.setIsWater(false);
		grass_terrain.setIsWalkable(true);

	}
	else{

		std::cout << "could not load grass\n";
	}

	texture = new sf::Texture();
	if (texture->loadFromFile(TILE_STONE_TEXTURE)){

		hill_terrain.addTexture(texture);
		hill_terrain.setMovementCost(3);
		hill_terrain.setIsWater(false);
		hill_terrain.setIsWalkable(false);

	}
	else{ std::cout << "could not load stone\n"; }

	texture = new sf::Texture();

	if (texture->loadFromFile(TILE_WATER_TEXTURE)){

		river_terrain.addTexture(texture);
		river_terrain.setMovementCost(2);
		river_terrain.setIsWater(true);
		river_terrain.setIsWalkable(false);
	}
	else{	std::cout << "could not load water\n";	}

	texture = new sf::Texture();

	if (texture->loadFromFile(TILE_EXIT_TEXTURE)){

		exit_terrain.addTexture(texture);
		exit_terrain.setMovementCost(1);
		exit_terrain.setIsWater(false);
		exit_terrain.setIsExit(true);

	}else{	std::cout << "could not load exit\n";	}

	texture = new sf::Texture();

	if (texture->loadFromFile(TILE_DIRT_TEXTURE)){

		dirt_terrain.addTexture(texture);
		dirt_terrain.setMovementCost(2);
		dirt_terrain.setIsWater(false);
		dirt_terrain.setIsWalkable(true);
	}
	else{	std::cout << "could not load water\n"; }

	texture = NULL;

	return true;
}


bool Level::loadEntityTextures(int num_level){

	//load the location for each entity texture image
	const int size = 2;
	std::string textures_list[size];

	textures_list[0] = { NPC_SPRITE_SHEET };
	textures_list[1] = { ENEMY_SPRITE_SHEET};

	//Using one texture reference to load all textures.
	sf::Texture texture;
	std::string sprite_sheet_name;
	std::string image_location = "";
	//Load all textures
	for (int i = 0; i < size; i++){

		sprite_sheet_name = textures_list[i]; //Get the name of the sprite sheet (represented by its location)
		image_location = sprite_sheet_name + std::to_string(num_level) + std::string(".png");//Select sprite sheet based on the level
		
		if (!texture.loadFromFile(image_location, sf::Rect<int>(0, 0, 0, 0))){
			std::cout << " could not load entity texture " << image_location << std::endl;
			return false;
		}
		else{
			//Use the sprite sheet name as the key for the texture
			texture_map_list.insert(std::pair<std::string, sf::Texture>(sprite_sheet_name, texture));
		}
	}

	return true;
}

std::vector<Entity*>&Level::getEntities(){


	return entities_list;
}


//Create tiles
void Level::loadLevel(std::string path) {

	std::ifstream map_ifstream;
	map_ifstream.open(path);
	std::string line;
	
	int len = 0;
	
	for (int y = 0; y< MAX_TERRAINS_COL; y++){//Height going from top to bottom

		std::getline(map_ifstream, line);

		for (int x = 0; x < MAX_TERRAINS_ROW; x++){//Width going across from left to right

			char c = line[x];

			switch (c){

			case 'e': //Exit
				addTerrain(x, y, exit_terrain);
				//tiles_[x][y] = &exit_terrain;
				break;

			case 'w': //Wall
				//addTerrain(row, col, &hill_terrain);
				addTerrain(x, y, hill_terrain);
				break;

			case 'g': //Grass

				addTerrain(x, y, grass_terrain);
				break;

			case 'l': //Water
				addTerrain(x, y, river_terrain);
				break;

			case 'd': //Dirt
				addTerrain(x, y, dirt_terrain);
				break;

				default://When the file does not match the game's number of terrains, then we draw a default grass terrain.
					addTerrain(x, y, grass_terrain);
					break;

			}//End switch
		}
	}

}

//Create the entities based on the given map
//Map defines the entities
void Level::createEntities(LocalMapState* local_map_state, std::string path, int num_level, sf::Font* font){

	std::ifstream map_ifstream;
	map_ifstream.open(path);
	std::string line;
	int MAX_ITEMS = 1;
	int MAX_SPELLS = 1;

	for (int y = 0; y < MAX_TERRAINS_COL; y++){

		if (std::getline(map_ifstream, line)){

			for (int x = 0; x < MAX_TERRAINS_ROW; x++){

				char c = line[x];

				Entity* e = NULL;
				switch (c){

					case 'e': //Enemy

						e = new Enemy(texture_map_list.at(ENEMY_SPRITE_SHEET), this, rand() % 2, rand() % 4);
						break;

					case 'n': //NPC

						e = new Npc(texture_map_list.at(NPC_SPRITE_SHEET), this, rand() % 2, rand() % 4);
						break;

				}//End switch

				if (e != NULL){
					e->initAttributes(num_level);
					sSpell* spells = new sSpell[MAX_SPELLS];
					sItem* items = new sItem[MAX_ITEMS];

					for (int i = 0; i < MAX_ITEMS; i++){

						items->Category = ItemCategories::WEAPON;
						items->Flags = 0;
						strcpy_s(items->Name, "Sword");
						strcpy_s(items->Description, "A short weak weapon");
						items->Price = 1;
						items->Size = 0.3f;
						items->Usage = 0;
						items->Value = 5;
						items->Weight = 1.0;
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

					items--;
					spells--;

					e->addObserver(local_map_state);
					e->init(font, items, spells, 0, 0);

					e->setPosition((float)(x*Terrain::TILE_WIDTH), (float)(y*Terrain::TILE_HEIGHT));
					e->setList(&entities_list);
					e->setID(y%MAX_TERRAINS_COL);
				
					addEntity(e);
				}
			}
		}
	}
}

int Level::getHeight() {
	return MAX_TERRAINS_COL;
}

int Level::getWidth() {
	return MAX_TERRAINS_ROW;
}

void Level::addTerrain(int x, int y, Terrain& terrain) {
	tiles_[x][y] = &terrain;
}

/*
*Gets a Terrain in the level.
*@param x the x coordinate of the terrain
*@param y the y coordinate of the terrain
*@return A pointer to the Terrain at the given coordinates 
*or a NULL pointer if none exists at the coordinates
*/
Terrain* Level::getTerrain(int x, int y){
	if (x < 0 || x > MAX_TERRAINS_ROW || y < 0 || y > MAX_TERRAINS_COL)
		return NULL;

	return tiles_[x][y];
}


bool Level::addEntity(Entity* entity){

	if (entity == NULL)
		return false;

	entities_list.push_back(entity);
	return true;
}

Entity* Level::getEntity(std::size_t index){

	if (index < 0 || index > entities_list.size())
		return NULL;

	return entities_list.at(index);

}

bool Level::removeEntity(Entity* e){
	
	entities_list.erase(std::remove(entities_list.begin(), entities_list.end(), e), entities_list.end());
	return true;

}

void Level::setRoute(Entity*e){

	e->setAI(CHAR_ROUTE);

	int num_points = 5;
	Route* routes = new Route[num_points];

	Route s0, s1, s2, s3, s4;

	s0.XPos = (float)(rand() % MAX_TERRAINS_ROW * Terrain::TILE_WIDTH);
	s0.YPos = (float)(rand() % MAX_TERRAINS_COL * Terrain::TILE_HEIGHT);

	s1.XPos = (float)(rand() % MAX_TERRAINS_ROW * Terrain::TILE_WIDTH);
	s1.YPos = (float)(rand() % MAX_TERRAINS_COL * Terrain::TILE_HEIGHT);

	s2.XPos = (float)(rand() % MAX_TERRAINS_ROW * Terrain::TILE_WIDTH);
	s2.YPos = (float)(rand() % MAX_TERRAINS_COL * Terrain::TILE_HEIGHT);

	s3.XPos = (float)(rand() % MAX_TERRAINS_ROW * Terrain::TILE_WIDTH);
	s3.YPos = (float)(rand() % MAX_TERRAINS_COL * Terrain::TILE_HEIGHT);

	s4.XPos = (float)(rand() % MAX_TERRAINS_ROW * Terrain::TILE_WIDTH);
	s4.YPos = (float)(rand() % MAX_TERRAINS_COL * Terrain::TILE_HEIGHT);


	routes[0] = s0;
	routes[1] = s1;
	routes[2] = s2;
	routes[3] = s3;
	routes[4] = s4;

	e->setRoutes(e->getID(), num_points, routes);
}


std::size_t Level::getEntityCount(){

	return entities_list.size();
}

//Convert pixels to a tile coordinate
sf::Vector2i Level::pixelsToTileCoordinate(int x, int y){

	return sf::Vector2i(x / Terrain::TILE_WIDTH, y / Terrain::TILE_HEIGHT);

}

//Convert a tile to a pixel position
sf::Vector2i Level::tileCoordinateToPixels(int tileX, int tileY){

	return sf::Vector2i(tileX*Terrain::TILE_WIDTH, tileY*Terrain::TILE_HEIGHT);

}

void Level::drawLevel(sf::RenderWindow* window) {


	for (int y = 0; y < MAX_TERRAINS_COL; y++) {

		for (int x = 0; x < MAX_TERRAINS_ROW; x++) {

			Terrain* terrain = tiles_[x][y];
			
			if (terrain){
			
				terrain->setPosition((float)(x * Terrain::TILE_WIDTH), (float)(y * Terrain::TILE_HEIGHT));
				window->draw(*terrain);
			}
			else{

				std::cout << " No terrain\n";
			}
		}
	}
}

int Level::getLevelNum(){

	return level;
}

Level::~Level() {


	for (int y = 0; y < MAX_TERRAINS_COL; y++) {

		for (int x = 0; x < MAX_TERRAINS_ROW; x++) {

			delete tiles_[x][y];
		}
	}
	delete []tiles_;
}
