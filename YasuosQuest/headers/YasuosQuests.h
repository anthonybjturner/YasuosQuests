#ifndef YASUOS_QUESTS_H
#define YASUOS_QUESTS_H

//#define GAME_WINDOW_WIDTH 1920
//#define GAME_WINDOW_HEIGHT 1080
#define GAME_WINDOW_WIDTH 1366
#define GAME_WINDOW_HEIGHT 768
#define GAME_WINDOW_TITLE "Yasuos Quest"
#define GAME_FRAMES_PER_SECOND 33

#include "SFML\Graphics.hpp"

//Forward declarations
class StateMachine;

class YasuosQuests{

public:

	YasuosQuests();
	~YasuosQuests();

	void start();
	void update(long);
	void updateFPS(long elapsed);

	void render();
	void handleEvents(long elapsed);
	void handleInput(long);
private:
	//Graphics
	sf::RenderWindow* window;
	StateMachine* state_machine;

	sf::Text current_fps_text;	
	sf::Font game_font;

};

#endif // !YASUOS_QUESTS_H