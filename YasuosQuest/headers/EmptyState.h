#ifndef EMPTY_STATE_H
#define EMPTY_STATE_H
#include "GameState.h"

class EmptyState : public GameState{

public:

	EmptyState(StateMachine*);
	~EmptyState();

	virtual void update(long elapsedTime);
	virtual void render();
	virtual void onEnter();
	virtual void onExit();
	virtual void handleEvents(long elapsed);
};
#endif