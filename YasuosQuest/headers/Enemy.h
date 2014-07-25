#pragma once
#include "Npc.h"

class Enemy : public Npc{

public:
	Enemy(sf::Texture& texture, Level* level, int, int);
	~Enemy();

	void simulateAi();
	void update();
};

