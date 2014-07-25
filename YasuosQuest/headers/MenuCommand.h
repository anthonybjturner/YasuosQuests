#pragma once
#include "Command.h"
class MenuCommand :	public Command{

public:
	MenuCommand();
	~MenuCommand();

	virtual void execute(Entity* entity, long elapsed);
	virtual void execute(Player* entity, long elapsed);
};

