#pragma once
#include "Entity.h"
class Npc :	public Entity
{
public:
	Npc(sf::Texture& texture, Level *level, int, int);
	~Npc();


	virtual void simulateAi();
};

