#include "../headers/stdafx.h"
#include "../headers/MoveUpCommand.h"
#include "../headers/Entity.h"
#include "../headers/Player.h"

MoveUpCommand::MoveUpCommand(){
}


MoveUpCommand::~MoveUpCommand()
{
}

void MoveUpCommand::execute(Player* player, long elapsed) {
	player->setIsMovingUp(true);
}

void MoveUpCommand::execute(Entity* entity, long elapsed) {
	
}

