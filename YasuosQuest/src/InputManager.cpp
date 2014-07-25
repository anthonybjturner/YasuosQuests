#include "../headers/stdafx.h"
#include "../headers/InputManager.h"
#include "../headers/StateMachine.h"
#include "../headers/MoveLeftCommand.h"
#include "../headers/MoveRightCommand.h"
#include "../headers/MoveUpCommand.h"
#include "../headers/MoveDownCommand.h"
#include "../headers/AttackCommand.h"
#include "MenuCommand.h"

InputManager::InputManager(StateMachine& s_machine){

	this->s_machine = &s_machine;
	//Configure buttons
	//This can be changed to allow the user to set button configs.
	button_left = new MoveLeftCommand();
	button_right = new MoveRightCommand();
	button_up = new MoveUpCommand();
	button_down = new MoveDownCommand();

	button_a = button_left;
	button_d = button_right;
	button_w = button_up;
	button_s = button_down;

	button_esc = new MenuCommand();
	button_space = new AttackCommand();
}


InputManager::~InputManager(){

}

/*
*Handles key presses
*Postcondition: the key pressed is returned or NULL
*/
Command* InputManager::handleKeyPresses(){

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){

		return button_left;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){

		return button_right;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		
		return button_up;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){

		return button_down;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){

		return button_w;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		return button_a;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){

		return button_s;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){

		return button_d;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){

		return button_space;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){	//Pressing escape key toggles showing menu

		//s_machine->change(MAIN_MENU_STATE);
		return button_esc;
	}

	return NULL;

}

/*
*Handles mouse presses
*Postcondition: the mouse pressed is returned or NULL
*/
Command* InputManager::handleMousePresses(){

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){

		button_space->setPosition(sf::Mouse::getPosition(*s_machine->getGraphics()));
		return button_space;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){

		return button_right;
	}

	return NULL;
}
