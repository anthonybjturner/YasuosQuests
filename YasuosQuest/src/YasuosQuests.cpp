// YasuosQuests.cpp : Defines the entry point for the application.
#include "../headers/stdafx.h"

#include "../headers/YasuosQuests.h"
#include "../headers/StateMachine.h"

#include <Windows.h>


YasuosQuests::YasuosQuests(){

	srand((int)time(0));
	window = new sf::RenderWindow(sf::VideoMode(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT), GAME_WINDOW_TITLE);
	//window->setFramerateLimit(30);

	if (game_font.loadFromFile("arial.ttf") ){

		current_fps_text.setFont(game_font);
		current_fps_text.setColor(sf::Color::Green);
		current_fps_text.setPosition(((float) window->getSize().x - current_fps_text.getCharacterSize()) - 48.0f, 32.0f);
	}
	// A state for each game mode
	state_machine = new StateMachine( window);

	//l_state->addObserver(state_machine);
	//gGameMode.add("worldmap", new WorldMapState(gGameMode));
	//gGameMode.add("battle", new BattleState(gGameMode));
	//gGameMode.add("ingamemenu", new InGameMenuState(gGameMode));
	state_machine->change(MAIN_MENU_STATE);
}

YasuosQuests::~YasuosQuests(){

	delete state_machine;
	delete window;
}

//Starts the game
void YasuosQuests::start(){

	long MS_PER_FRAME = 1000 / GAME_FRAMES_PER_SECOND;
	long last_time = timeGetTime(), current_time= 0, elapsed = 0;
	while ( window->isOpen() ){

		current_time = timeGetTime();
		//std::cout << "current time " << current_time << std::endl;
		//std::cout << "last_time  " << last_time << std::endl;
		elapsed = (current_time - last_time) ;//Gives about 60fps with a division of 10 (17ms/frame)
	//	std::cout << "Elapsed time " << elapsed << std::endl;

		if ( current_time > last_time + MS_PER_FRAME){

			update(elapsed);
			render();
			handleInput(elapsed);
			handleEvents(elapsed);
			last_time = current_time;
		}
	}
}

void YasuosQuests::updateFPS(long elapsed){

	float current_fps = (float)(1000.0f / elapsed);
	current_fps_text.setString(std::to_string(current_fps));
}


//Updates all game objects
void YasuosQuests::update(long elapsed){

	state_machine->update(elapsed);
	updateFPS(elapsed);

}

//Draws all game objects
void YasuosQuests::render(){

	window->clear();
	state_machine->render();

	window->draw(current_fps_text);
	window->display();




}

void YasuosQuests::handleInput(long elapsed){


	state_machine->handleInput(elapsed);
}

void YasuosQuests::handleEvents(long elapsed){

	sf::Event event;

	//Loop through and process all events 
	while (window->pollEvent(event)){

		//The user closed the window
		if (event.type == sf::Event::Closed){ window->close(); }

		state_machine->handleEvents(elapsed);
		
	}
}
