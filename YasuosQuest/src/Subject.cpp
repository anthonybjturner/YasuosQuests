#include "../headers/stdafx.h"
#include "../headers/Subject.h"
#include "../headers/Observer.h"
#include "../headers/Entity.h"
#include "../headers/Event.h"

Subject::Subject(){
}


Subject::~Subject(){


	for (std::vector<Observer*>::iterator it = observers_list.begin(); it != observers_list.end(); it++){
	
		delete (*it);
	}

}

void Subject::notify(Entity& entity, Event event){

	//Traverse all observers and call its notify function
	for (std::vector<Observer*>::iterator it = observers_list.begin(); it != observers_list.end(); it++){

		(*it)->onNotify(entity, event);
	}
}


void Subject::addObserver(Observer* observer){
	// Add to array...
	observers_list.push_back(observer);
	
}

Observer* Subject::findObserver(int id){

	int size = observers_list.capacity();
	
	for (int i = 0; i < size; i++){
	
		Observer* o = observers_list.at(i);
		if (o->getId() == id)
			return o;
	}

	return NULL;
}

void Subject::removeObserver(Observer* observer){

	observers_list.erase(std::remove(observers_list.begin(), observers_list.end(), observer));	
}
