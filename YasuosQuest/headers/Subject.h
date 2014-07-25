#ifndef SUBJECT_H
#define SUBJECT_H
#include "Event.h"
#include <vector>
/*
*Subject.h is a concrete class that other classes implement (inherent from) when they
*want to send notifcations for behavior/actions to Observers.
*The Observer then decides what to do with those action(s).
*/

class Observer;
class Entity;

class Subject{
	

public:
	Subject();
	~Subject();
	
	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);
	Observer* findObserver(int id);


protected:
	void notify(Entity& t, Event event);
		
private:
	std::vector<Observer*>observers_list;
		

};

#endif