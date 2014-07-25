#include "../headers/stdafx.h"
#include "../headers/Command.h"
#include "../headers/Entity.h"
#include "../headers/Player.h"

Command::Command(){
	
	//Coordinates for where a command was triggered within the game world.
	coordinates.x = 0;
	coordinates.y = 0;

}


Command::~Command(){
}

void Command::execute(Entity* entity, long elapsed){


}

void Command::execute(Player* entity, long elapsed){


}


void Command::setPosition(sf::Vector2i pos){

	coordinates = pos;
}


sf::Vector2i& Command::getPosition(){

	return coordinates;

}
