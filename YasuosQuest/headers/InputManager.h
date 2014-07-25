#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "Command.h"

/*
*InputManager manages keyboard and mouse input
*It uses the Command design pattern to assign and return key commands.
*/
class StateMachine;

class InputManager{

public:
	InputManager(StateMachine& s_machine);
	~InputManager();

	Command* handleKeyPresses();
	Command* handleMousePresses();
	
private:

	StateMachine* s_machine;

	Command* button_left;
	Command* button_right;
	Command* button_up;
	Command* button_down;

	//WASD buttons
	Command* button_w;
	Command* button_a;
	Command* button_s;
	Command* button_d;

	Command* button_space;
	Command* button_esc;
};

#endif