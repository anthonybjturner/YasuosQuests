#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "GameState.h"

#define MENU_BUTTON_SIZE 100


class MainMenuState : public GameState{

public:
	MainMenuState(StateMachine* s_machine);
	~MainMenuState();
	
	void update(long elapsedTime);
	void render();
	void onEnter();
	void onExit();
	void handleEvents(long elapsed);

	void handleKeyPresses();
	void handleMousePresses();
	void handleInput(long elapsed);

	void moveDown();
	void moveLeft();
	void moveRight();
	void moveUp();

	void loadTextures();

	bool playSound(std::string);
	bool playMusic(std::string);

private:

	sf::Texture bg_texture;
	sf::Texture texture;
	sf::Texture cursor_texture;
	sf::Texture new_game_texture;
	sf::Texture exit_game_texture;
	
	sf::Font font;
		
	sf::RectangleShape cursor_sprite;
	sf::RectangleShape new_game_button;
	sf::RectangleShape quit_game_button;
	sf::RectangleShape* current_selected_button;
	sf::RectangleShape background;
	sf::RectangleShape menu_background;
	sf::RectangleShape game_logo;
	
	sf::Vector2f window_size;
	sf::Text menu_text;
	
	sf::Sound sound;
	sf::SoundBuffer buffer;
	sf::Music music;
};

#endif