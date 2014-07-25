#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "StateI.h"
#include "SFML\Graphics.hpp"//TODO create class that includes this and use forward declaration of that class
#include "SFML\Audio.hpp"
/*
*GameState is a partial concrete state with some abstraction.
*The purpose of this class is to define data members for classes that inherit from this class. 
*Since the implemented interface (StateI) does not hold this data,
*and can't construct (pass in its constructor) the needed data.
*/

class InputManager;
class StateMachine;

class GameState : public StateI{

public:
	GameState(StateMachine* s_machine);
	~GameState();

	//Interface functions
	virtual void update(long elapsedTime);
	virtual void render();
	virtual void handleEvents(long elapsed);
	virtual void handleInput(long elapsed);
	StateMachine* getStateMachine();//Get the game's StateMachine for changing states.
	
protected:
	InputManager* i_manager;

	virtual void onEnter() = 0;
	virtual void onExit() = 0;
	

private:
	StateMachine* s_machine;

};

#endif