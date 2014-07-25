#include "../headers/stdafx.h"
#include "../headers/EmptyState.h"

EmptyState::EmptyState(StateMachine* s_machine) : GameState(s_machine){


}

EmptyState::~EmptyState(){


}



void EmptyState::update(long elapsedTime){

		// Nothing to update in the empty state.
}

void EmptyState::render(){

		// Nothing to render in the empty state
}

void EmptyState::onEnter(){

		// No action to take when the state is entered
}

void EmptyState::onExit(){

		// No action to take when the state is exited
}

void EmptyState::handleEvents( long elapsed){

}
