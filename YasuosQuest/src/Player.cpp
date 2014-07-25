#include "../headers/stdafx.h"
#include "../headers/Player.h"

Player::Player(sf::Texture& texture, Level* level, int row, int col) : Entity(texture, level, row, col){
	
	setType(CHAR_PC);
	setEntityTypeText("Player");
	setEntityTypeTextColor(sf::Color::Green);
	isAutoAttacking = true;
}

Player::~Player(){

}

void Player::pcUpdate(long elapsed, float *XMove, float *YMove){
	
	float Speed = (float)elapsed / 1000.0f * getSpeed(this);

	if ( isMovingLeft){

		*XMove = -1.0f *Speed;
		*YMove = 0.0f;
		isMovingLeft = false;
		//moveLeft(elapsed, XMove, YMove);
		setDirection(4.0);
		this->setAction(CHAR_MOVE);

	}

	if (isMovingUp){
		*XMove = 0.0f;
		*YMove = -1.0f * Speed;
		isMovingUp = false;
		//moveUp(elapsed, XMove, YMove);
		setDirection(2.5);
		this->setAction(CHAR_MOVE);

	}

	if (isMovingDown){

		*XMove = 0.0f;
		*YMove = 1.0f * Speed;
		isMovingDown = false;
		//moveDown(elapsed, XMove, YMove);
		setDirection(0.0f);
		this->setAction(CHAR_MOVE);
	}

	if (isMovingRight){
		*XMove = 1.0f *Speed;
		*YMove = 0.0f;
		isMovingRight = false;
		//moveRight(elapsed, XMove, YMove);
		setDirection(1.0f);
		this->setAction(CHAR_MOVE);

	}

	if ( isAutoAttacking )
		autoAttack();
}

void Player::autoAttack(){


	//Search for entity that the player has selected
	for (std::vector<Entity*>::iterator it = list->begin(); it != list->end(); it++){

		Entity* entity = (*it);
		if (entity->hasSelectedFocus()){//If an entity was selected, check to see if they are in-range to attack

			float move_x, move_y;
			this->checkAttack(CHAR_PC, CHAR_MONSTER, 0.0f, 0.0f, 0.0f, 0.0f, move_x, move_y);
			break;
		}

	}
}

void Player::moveUp(long elapsed, float *XMove, float *YMove){

	setDirection(2.5);
	move(elapsed, *XMove, *YMove);
}

void Player::moveDown(long elapsed, float *XMove, float *YMove){

	setDirection(0.0);
	move(elapsed, *XMove, *YMove);
}

void Player::moveLeft(long elapsed, float *XMove, float *YMove){

	setDirection(4.0);
	move(elapsed, *XMove, *YMove);
}

void Player::moveRight(long elapsed, float *XMove, float *YMove){

	setDirection(1.0);
	move(elapsed, *XMove, *YMove);
}

void Player::setIsMovingLeft(bool state){

	isMovingLeft = state;
}

void Player::setIsMovingUp(bool state){

	isMovingUp = state;

}

void Player::setIsMovingDown(bool state){

	isMovingDown = state;

}

void Player::setIsMovingRight(bool state){

	isMovingRight = state;

}


