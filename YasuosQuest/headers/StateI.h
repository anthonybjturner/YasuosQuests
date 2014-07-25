#ifndef STATE_I_H
#define STATE_I_H

class StateI{//State interface

public:

	virtual void update(long elapsedTime)=0;
	virtual void render()=0;
	virtual void onEnter()=0;
	virtual void onExit()=0;
	virtual void handleEvents(long elapsed) = 0;
	virtual void handleInput(long elapsed) = 0;
};
#endif