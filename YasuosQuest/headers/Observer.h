#ifndef OBSERVER_H
#define OBSERVER_H

#include "Event.h"
/*
*Observer.h is an interface that other classes implement when they 
*want to observe(look) for behavior/actions to occur from other objects aka a Subject.
*Other objects notify this observer.
*This observer then decides what action(s) to take.
*/

class Entity;
class Observer{

public:
	virtual ~Observer() {}
	virtual void onNotify(Entity& entity, Event event) = 0;
	//virtual void onNotify(Entity entity, Event event) = 0;

	virtual int getId() = 0;

};

#endif