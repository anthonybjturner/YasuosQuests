#pragma once
#include "Command.h"

class MoveRightCommand :public Command{

public:
	MoveRightCommand();
	~MoveRightCommand();

	void execute(Entity*, long elapsed);
	void execute(Player*, long elapsed);
};

