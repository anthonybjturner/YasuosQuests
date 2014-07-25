#pragma once
#include "Command.h"
class MoveDownCommand :
	public Command
{
public:
	MoveDownCommand();
	~MoveDownCommand();

	void execute(Entity*, long elapsed);
	void execute(Player*, long elapsed);
};

