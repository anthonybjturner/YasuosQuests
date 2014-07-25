#include "../headers/stdafx.h"
#include "../headers/Npc.h"
#include "../headers/Route.h"
#include "../headers/FocusedAttributesWindow.h"

Npc::Npc(sf::Texture& texture, Level *level,int row, int col) : Entity(texture, level, row, col){

	setType(CHAR_NPC);
	setEntityTypeText("NPC");
	setEntityTypeTextColor(sf::Color::Yellow);
}


Npc::~Npc(){

}

void Npc::simulateAi(){

}
