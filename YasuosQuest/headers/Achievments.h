#ifndef ACHIEVMENTS_H
#define ACHIEVMENTS_H

#include "Observer.h"
#include "Achievment.h"
#include <list>
/*
*Achievments.h observes(looks) for achievements to occur.
*It monitors behavior/actions from objects that notify this observer.
*This observer then decides if the action triggers an achievement
*/

class Achievments : public Observer{

public:
	Achievments();
	Achievments(int);
	~Achievments();

	virtual void onNotify(Entity& entity, Event event);//Called by classes implementing subject
	virtual int getId();

private:

	void unlock(Achievment achievment, Entity&);
	
	bool goal_reach_killed_five_enemies;
	std::list<int>goal_kills;

protected:
	int id;
};

#endif