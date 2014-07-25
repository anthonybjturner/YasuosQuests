#ifndef COMMAND_H
#define COMMAND_H

#include "SFML\Graphics.hpp"

class Entity;
class Player;
class Command{//Using the Command Design Pattern

public:
	Command();
	virtual ~Command();
	virtual void execute(Entity* entity, long elapsed) = 0;
	virtual void execute(Player* entity, long elapsed) = 0;

	void setPosition(sf::Vector2i);
	sf::Vector2i& getPosition();

private: 
	sf::Vector2i coordinates;
};

#endif