#include "../headers/stdafx.h"
#include "../headers/Enemy.h"
#include "../headers/FocusedAttributesWindow.h"

Enemy::Enemy(sf::Texture& texture, Level* level, int row, int col) : Npc(texture, level, row, col){

	setType(CHAR_MONSTER);
	setEntityTypeText("Monster");
	setEntityTypeTextColor(sf::Color::Red);
	
}


Enemy::~Enemy(){}


void Enemy::update() {

}

void Enemy::simulateAi(){



}
