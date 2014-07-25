#include "../headers/stdafx.h"
#include "../headers/Terrain.h"
#include "../headers/GraphicsFwd.h"


Terrain::Terrain(){

	isExit_ = false;
	isWalkable_ = true;
}


Terrain::~Terrain(){

}

Terrain::Terrain(int movementCost, bool isWater){

	movementCost_ = (movementCost);
	isWater_ = (isWater);
	isExit_ = false;
	isWalkable_ = true;

}

void Terrain::draw(sf::RenderWindow* window){

	//window->draw(sf::Sprite(texture_));

}

void Terrain::addTexture(sf::Texture* texture){

	terrain_texture = texture;
	setTexture(*terrain_texture);
}

const int  Terrain::getMovementCost() {

	return movementCost_;
}

const bool Terrain::isWater()  {
	
	return isWater_; 
}

const bool Terrain::isExit(){

	return isExit_;
}

const bool Terrain::isWalkable(){

	return isWalkable_;
}


void Terrain::setIsWater(bool iswater){

	isWater_ = iswater;
}

void Terrain::setIsWalkable(bool iswalkable){

	isWalkable_ = iswalkable;

}

void Terrain::setIsExit(bool isexit){

	isExit_ = isexit;
}

void Terrain::setMovementCost(int cost){

	movementCost_ = cost;
}
