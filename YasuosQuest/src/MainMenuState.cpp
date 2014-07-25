#include "../headers/stdafx.h"
#include "../headers/MainMenuState.h"
#include "../headers/StateMachine.h"

MainMenuState::MainMenuState(StateMachine* s_machine) : GameState(s_machine){
	
	window_size = s_machine->getGraphics()->getView().getSize();
	cursor_sprite.setSize(sf::Vector2f(32, 32));
	loadTextures();
	current_selected_button = &new_game_button;

}

MainMenuState::~MainMenuState(){

	delete current_selected_button;

}

void MainMenuState::loadTextures(){

	if (!cursor_texture.loadFromFile("images/cursor.png")){

		std::cout << "could not load cursor image" << std::endl;
	}
	else{
		cursor_sprite.setTexture(&cursor_texture);

	}

	if (!bg_texture.loadFromFile("images/bg.jpg")){

		std::cout << "texture for background main menu state not loaded" << std::endl;
	}
	else{

		//background.setFillColor(sf::Color(0, 0, 0, 255));
		background.setTexture(&bg_texture);
	}

	if (!texture.loadFromFile("images/grass_32.bmp")){

		std::cout << "texture for menu background main menu state not loaded" << std::endl;
	}
	else{

		menu_background.setFillColor(sf::Color(176, 176, 176, 224));
		//menu_background.setTexture(&texture);
	}

	if (!texture.loadFromFile("images/yasuosquests.png")){

		std::cout << "texture for menu background main menu state not loaded" << std::endl;
	}else{

		game_logo.setTexture(&texture);
		float logo_posx = (float)(window_size.x / 2 - texture.getSize().x / 2);//TODO may need to call the graphics object for size
		float logo_posy = 164;

		game_logo.setPosition(logo_posx, logo_posy);
		game_logo.setSize(sf::Vector2f((float)texture.getSize().x, (float)texture.getSize().y));
	}

	if (!new_game_texture.loadFromFile("images/new_game.png")){

		std::cout << "texture for new game button in main menu state not loaded" << std::endl;
	}
	else{
		new_game_button.setFillColor(sf::Color(0, 0, 0, 150));
		new_game_button.setTexture(&new_game_texture);
		new_game_button.setSize(sf::Vector2f(MENU_BUTTON_SIZE, 40));
	}

	if (!exit_game_texture.loadFromFile("images/quit.png")){

		std::cout << "texture for new game button in main menu state not loaded" << std::endl;

	}
	else{
		quit_game_button.setFillColor(sf::Color(0, 0, 0, 150));
		quit_game_button.setTexture(&exit_game_texture);
		quit_game_button.setSize(sf::Vector2f(MENU_BUTTON_SIZE, 40));
	}
}

bool MainMenuState::playMusic(std::string path){
	
	if (!music.openFromFile(path))
		return false; // error

	music.setLoop(true);
	music.play();
	return true;
}

bool MainMenuState::playSound(std::string clip){

	if (!buffer.loadFromFile(clip)){

		std::cout << "could not play MainMenuState clip \n";
		return false;
	}

	// load something into the sound buffer...
	sound.setBuffer(buffer);
	sound.play();
	return true;
}

void MainMenuState::update(long elapsedTime){


	background.setSize(sf::Vector2f(window_size.x, window_size.y));
	menu_background.setSize(sf::Vector2f(game_logo.getSize().x, (window_size.y / 3) -24));
	quit_game_button.setSize(sf::Vector2f(new_game_button.getSize().x, new_game_button.getSize().y));
	
	menu_background.setPosition(window_size.x / 4, (window_size.y / 2) - (menu_background.getSize().y/2 + 8));
	new_game_button.setPosition((menu_background.getPosition().x + menu_background.getSize().x / 2 - 64), (menu_background.getPosition().y + game_logo.getSize().y));
	quit_game_button.setPosition((new_game_button.getPosition().x), new_game_button.getPosition().y + 50);
	cursor_sprite.setPosition(current_selected_button->getPosition().x + current_selected_button->getSize().x, current_selected_button->getPosition().y);
	//menu_text.setPosition(menu_background.getPosition().x + (menu_background.getSize().x / 2) - 70, menu_background.getPosition().y + 5);

}

void MainMenuState::render(){
	sf::RenderWindow* graphics = getStateMachine()->getGraphics();
	graphics->draw(background);
	graphics->draw(menu_background);
	graphics->draw(new_game_button);
	graphics->draw(quit_game_button);
	graphics->draw(game_logo);
	graphics->draw(cursor_sprite);
}

void MainMenuState::onEnter(){

	if (!playMusic("audio/main_menu_audio.wav.ogg")){

		std::cout << "main menu background music can't be loaded\n";
	}
}

void MainMenuState::onExit(){

	music.stop();
}

void MainMenuState::handleKeyPresses(){

		
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){

		StateMachine* s_mach = getStateMachine();
		s_mach->change(LOCAL_MAP_STATE);
		//s_machine->change(LOCAL_MAP_STATE);
	}
}


void MainMenuState::handleMousePresses(){

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){

		moveLeft();
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){

		moveRight();
	}

}


void MainMenuState::moveUp(){


	if (current_selected_button == &quit_game_button){

		current_selected_button = &new_game_button;
	}
	
}

void MainMenuState::moveDown(){

	if (current_selected_button == &new_game_button){

		current_selected_button = &quit_game_button;
	}

}

void MainMenuState::moveLeft(){

//	float x = sprite->getPosition().x - 1;
	//float y = sprite->getPosition().y;
	//sprite->setPosition(x, y);

}

void MainMenuState::moveRight(){

	//float x = sprite->getPosition().x + 1;
	//float y = sprite->getPosition().y;
	//sprite->setPosition(x, y);

}

//Handles all game events eg. Mouse and Window click events.
void MainMenuState::handleEvents(long elapsed){


}

void MainMenuState::handleInput(long elapsed){

	handleKeyPresses();
	handleMousePresses();
}
