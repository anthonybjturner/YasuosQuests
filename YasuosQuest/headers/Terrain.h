#ifndef TERRAIN_H
#define TERRAIN_H
/*
*File: Terrain.h
*Description: Terrain represents one location in a map/level which represents a texture
*Textures are images such as grass, wall, dirt, water, etc.
*/

#include "SFML\Graphics.hpp"

#define TILE_WALL_TEXTURE "images/wall_two_32.jpg"
#define TILE_GRASS_TWO_TEXTURE "images/grass_two.png"
#define TILE_BUSH_TEXTURE "images/bush_32.bmp"
#define TILE_CLAY_TEXTURE "images/clay.png"
#define TILE_WATER_TEXTURE ("images/water_32.png")
#define TILE_GRASS_TEXTURE "images/grass_32.bmp"
#define TILE_DIRT_TEXTURE "images/dirt_32.bmp"
#define TILE_STONE_TEXTURE "images/stone_32.bmp"
#define TILE_EXIT_TEXTURE "images/exit.jpg"

class Terrain : public sf::Sprite{

public:
	Terrain();
	Terrain(int movementCost, bool isWater);
	~Terrain();

	static const int TILE_WIDTH = 32;
	static const int TILE_HEIGHT = 32;

	const int getMovementCost();

	void addTexture(sf::Texture*);

	const bool isWater();
	const bool isExit();
	const bool isWalkable();

	void setMovementCost(int cost);
	void setIsWater(bool);
	void setIsExit(bool);
	void setIsWalkable(bool);

	void draw(sf::RenderWindow*);

private:
	int movementCost_;
	bool isWater_;
	bool isExit_;
	bool isWalkable_;
	sf::Texture* terrain_texture;
	
};

#endif