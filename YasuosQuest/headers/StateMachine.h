#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "SFML\Graphics.hpp"
//#include <map> May not need this

#define MAIN_MENU_STATE "mainmenu"
#define EMPTY_STATE "emptystate"
#define LOCAL_MAP_STATE "localmap"

class StateI;

class StateMachine{

public:
	StateMachine(sf::RenderWindow*);
	~StateMachine();

	void update(long elapsedTime);
	void render();
	void change(std::string stateName);
	void add(std::string name, StateI* state);
	void handleEvents(long elapsed);
	void handleInput(long);
	sf::RenderWindow* getGraphics();
	StateI* getState();

private:
	std::map<std::string, StateI*> mStates;
	StateI* mCurrentState;
	sf::RenderWindow* graphics;
};

#endif