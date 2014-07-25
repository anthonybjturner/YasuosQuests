#include "../headers/stdafx.h"
#include "../headers/MoveDownCommand.h"
#include "../headers/Entity.h"
#include "../headers/Player.h"

MoveDownCommand::MoveDownCommand()
{
}


MoveDownCommand::~MoveDownCommand()
{
}



void MoveDownCommand::execute(Player* player, long elapsed) {
	player->setIsMovingDown(true);

}

void MoveDownCommand::execute(Entity* entity, long elapsed) {

}

