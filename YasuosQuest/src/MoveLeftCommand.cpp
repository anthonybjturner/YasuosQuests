#include "../headers/stdafx.h"
#include "../headers/MoveLeftCommand.h"
#include "../headers/Entity.h"
#include "../headers/Player.h"

MoveLeftCommand::MoveLeftCommand(){
}


MoveLeftCommand::~MoveLeftCommand(){

}

void MoveLeftCommand::execute(Entity* entity, long elapsed) {
	//entity->moveLeft();
}

void MoveLeftCommand::execute(Player* player, long elapsed) {
	
	//player->moveLeft(elapsed);
	player->setIsMovingLeft(true);
}
