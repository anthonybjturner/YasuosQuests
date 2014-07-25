#include "../headers/stdafx.h"
#include "../headers/AttackCommand.h"
#include "../headers/Entity.h"
#include "../headers/Player.h"
#include "../headers/LocalMapState.h"

AttackCommand::AttackCommand(){
}


AttackCommand::~AttackCommand(){
}


void AttackCommand::execute(Player* entity, long elapsed) {

	//Just call the more generalized execute() function of type Entity
	execute((Entity*)entity, elapsed);
}

void AttackCommand::execute(Entity* current_entity, long elapsed) {
	
	//Get the current instance of AttackCommand, get the stored coordinates, and check if an entity is at those coordinates.
	LocalMapState* map = current_entity->getLocalMap();

	Entity* selected_entity = map->findEntityAtCoordinate(this->getPosition());

	//Clicking on an entity triggers selecting it
	if (selected_entity){//This call should maybe be somewhere else, such as the LocalMapState (Main game area)

		selected_entity->setAsFocusedEntity(true);
		map->resetAllEntitiesFocusExcept(selected_entity);

		
		if (selected_entity != current_entity){

			float move_x, move_y;
			current_entity->checkAttack(CHAR_PC, CHAR_MONSTER, 0, 0, 0, 0, move_x, move_y);

		}
			
	}
	else if (selected_entity == current_entity){

	}
	else{//Reset entities having focused if clicked off an entity onto a tile map

		map->resetAllEntitiesFocus();
	}

}
