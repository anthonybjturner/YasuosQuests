#pragma once
#include "Command.h"
class MoveUpCommand : public Command{

public:
	MoveUpCommand();
	~MoveUpCommand();

	void execute(Entity*, long elapsed);
	void execute(Player*, long elapsed);
};

