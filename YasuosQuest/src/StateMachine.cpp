#include "../headers/stdafx.h"
#include "../headers/StateMachine.h"
#include "../headers/MainMenuState.h"
#include "../headers/LocalMapState.h"
#include "../headers/EmptyState.h"

/*
* StateMachine manages different states within this game.
* The actual behavior handling however is handled by the current state.
* By default an empty state is created.
* Precondition: A non-null state must be added
* Postcondition: The StateMachine is created with an active state.
*/
StateMachine::StateMachine(sf::RenderWindow* window_graphics){

	graphics = window_graphics;//Must be initialized first, other states depend on it.

	//Check assignment with out new keyword
	EmptyState* state = new EmptyState(this);
	mCurrentState = state;
	add(EMPTY_STATE, state);//Assumming the argument for state in the constructor is an EmptyState
	add(MAIN_MENU_STATE, new MainMenuState(this));
	add(LOCAL_MAP_STATE, new LocalMapState(this));
}


StateMachine::~StateMachine(){


	//Delete all pointers to states
	for (std::map<std::string, StateI*>::iterator it = mStates.begin(); it != mStates.end(); it++){

		delete it->second;

	}
	mCurrentState = NULL;
}

sf::RenderWindow* StateMachine::getGraphics(){

	return graphics;
}

//Update the current state
void StateMachine::update(long elapsedTime){

	mCurrentState->update(elapsedTime);
}
 
//Render the current state
void StateMachine::render(){

	mCurrentState->render();
}

/*
	Changes the current state to the requested state.
	Precondition: The given stateName string is not null, empty,
	and the StateMachine has the requested state. 
	eg. it has been previously added to the StateMachine
	Postcondition: The state has been changed to the specified state.
	@param stateName: The state to change to
*/
void StateMachine::change(std::string stateName){

	mCurrentState->onExit();
	mCurrentState = mStates[stateName];
	mCurrentState->onEnter();
}

void StateMachine::add(std::string name, StateI* state){

	mStates[name] = state;
}

void StateMachine::handleEvents(long elapsed){

	mCurrentState->handleEvents( elapsed);
}

void StateMachine::handleInput(long elapsed){

	mCurrentState->handleInput(elapsed);
}

StateI* StateMachine::getState(){

	return mCurrentState;

}
