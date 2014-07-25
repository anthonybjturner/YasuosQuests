#include "../headers/stdafx.h"
#include "../headers/GameState.h"
#include "../headers/StateMachine.h"

GameState::GameState(StateMachine* s_machine){

	//graphics_window = window;
	this->s_machine = s_machine;

}


GameState::~GameState(){

	//delete graphics_window;
	delete s_machine;
}

void GameState::update(long elapsedTime){

	//Empty function that inheriting classes implement
}

void GameState::render() {

	//Empty function that inheriting classes implement
}

void GameState::onEnter(){
	//Empty function that inheriting classes implement
}

void GameState::onExit(){

	//Empty function that inheriting classes implement
}


void GameState::handleEvents(long elapsed){

	//Empty function that inheriting classes implement

}

void GameState::handleInput(long elapsed){


}

StateMachine* GameState::getStateMachine(){

	return s_machine;
}
