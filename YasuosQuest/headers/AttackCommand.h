#pragma once
#include "Command.h"

class AttackCommand :	public Command{

public:
	AttackCommand();
	~AttackCommand();


	void execute(Entity*, long elapsed);
	void execute(Player*, long elapsed);
};

