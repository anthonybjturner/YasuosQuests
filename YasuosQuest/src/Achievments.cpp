#include "../headers/stdafx.h"
#include "../headers/Achievments.h"
#include "../headers/LocalMapState.h"
#include "../headers/Entity.h"

Achievments::Achievments(){

	this->id = 1;
	goal_reach_killed_five_enemies = false;
	
	goal_kills.push_back(10);
	goal_kills.push_back(100);
	goal_kills.push_back(1000);
	goal_kills.push_back(10000);
	goal_kills.push_back(100000);
}


Achievments::Achievments(int id){
	this->id = id;
	goal_reach_killed_five_enemies = false;

}

int Achievments::getId(){

	return id;
}


void Achievments::onNotify(Entity& entity, Event event){
	
	switch (event){

			case EVENT_ENEMY_KILLED:
				
				if ( !goal_kills.empty() ){

					if (entity.getKillCount() == goal_kills.front()){

						goal_kills.pop_back();
						unlock(ACHIEVMENT_REACHED_GOAL_KILLED_ENEMIES, entity);
						break;
					}
				}
				break;
			// Handle other events, and update heroIsOnBridge_...
		}
	
}


void Achievments::unlock(Achievment achievment, Entity& entity){//Enum Achievment

	LocalMapState* o = entity.getLocalMap();
	// Unlock if not already unlocked...
	switch (achievment){

		case ACHIEVMENT_REACHED_GOAL_KILLED_ENEMIES:

			long kills = entity.getKillCount();
			char TEXT[128];//Storage buffer for text and number concatenation
			long XP = kills * 3;
			sprintf_s(TEXT, "You killed %lu enemies!\n Rewarded %lu XP", kills, XP);
			std::string text = TEXT;
			
			o->setNotification(text, 2000, sf::Color::Yellow);//Show a game notification about reaching goal
			o->experience(&entity, XP);

			goal_reach_killed_five_enemies = true;
			break;
		}
}


Achievments::~Achievments(){}
