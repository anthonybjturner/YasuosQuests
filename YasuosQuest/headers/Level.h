#ifndef LEVEL_H
#define LEVEL_H

#include <map>
#include <vector>

#include "Terrain.h"

#define PLAYER_SPRITE_SHEET "images/Actor1.png"
#define NPC_SPRITE_SHEET "images/People"
#define ENEMY_SPRITE_SHEET "images/Enemy"

#define MAP_PATH ("maps\\level_")
#define FILE_EXTENTION (".map")

#define ERROR_LOADING_SPRITE_SHEET "Couldn't load sprite sheet"

#define MAX_TERRAINS_ROW 60
#define MAX_TERRAINS_COL 60

class Enemy;
class Entity;
class LocalMapState;


class Level {

public:

	Level(LocalMapState*, int level, sf::Font*);//graphics window, level, width, height of level
	~Level();

	//Functions
	sf::Vector2i pixelsToTileCoordinate(int x, int y);
	sf::Vector2i tileCoordinateToPixels(int tileX, int tileY);

	int getWidth();
	int getHeight();

	Terrain* getTerrain(int x, int y);
	Entity* getEntity(std::size_t index);
	std::size_t getEntityCount();
	std::vector<Entity*>&getEntities();
	int getLevelNum();

	void addTerrain(int x, int y, Terrain& t);
	bool addEntity(Entity* entity);
	void setRoute(Entity*e);
	
	void loadLevel(std::string);
	void drawLevel(sf::RenderWindow* window);
	
	bool removeEntity(Entity* e);


private:
	//Fields - Instance variables
	std::vector<Entity*> entities_list;
	std::map<std::string, sf::Texture> texture_map_list;

	Terrain* tiles_[MAX_TERRAINS_ROW][MAX_TERRAINS_COL]; //An array of Terrain tiles
	Terrain grass_terrain, hill_terrain, river_terrain, exit_terrain, dirt_terrain;

	//Functions
	bool loadTileTextures();
	bool loadEntityTextures(int);
	void createEntities(LocalMapState*, std::string, int, sf::Font*);
	int level;
	
};
#endif