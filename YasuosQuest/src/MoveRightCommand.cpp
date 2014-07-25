#include "../headers/stdafx.h"
#include "../headers/MoveRightCommand.h"
#include "../headers/Entity.h"
#include "../headers/Player.h"

MoveRightCommand::MoveRightCommand(){

}

MoveRightCommand::~MoveRightCommand(){

}


void MoveRightCommand::execute(Player* player, long elapsed) {
	player->setIsMovingRight(true);
	
}

void MoveRightCommand::execute(Entity* entity, long elapsed) {
	//entity->move()
}
