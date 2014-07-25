#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "AttackCommand.h"

class Player : public Entity{

public:

	Player(sf::Texture& texture, Level* level, int, int);
	~Player();

	bool update(long Elapsed, float *XMove, float *YMove, float *ZMove);
	void moveDown(long elapsed, float *XMove, float *YMove);
	void moveLeft(long elapsed, float *XMove, float *YMove);
	void moveRight(long elapsed, float *XMove, float *YMove);
	void moveUp(long elapsed, float *XMove, float *YMove);
	void pcUpdate(long Elapsed, float *XMove, float *YMove);
	
	void autoAttack();

	void setIsMovingLeft(bool);
	void setIsMovingUp(bool);
	void setIsMovingDown(bool);
	void setIsMovingRight(bool);
private:
	float cameraYAngle;//Viewing angle of camera
	float direction; // Direction to move
	float distance; // How far to move
	float facing; // Direction character is facing

	bool isMovingLeft;
	bool isMovingUp;
	bool isMovingDown;
	bool isMovingRight;
	bool isAutoAttacking;

	AttackCommand a_cmd;
};

#endif