#pragma once
#include "Command.h"

class MoveLeftCommand :	public Command{

public:
	MoveLeftCommand();
	~MoveLeftCommand();

	void execute(Entity*, long elapsed);
	void execute(Player*, long elapsed);

	
};

