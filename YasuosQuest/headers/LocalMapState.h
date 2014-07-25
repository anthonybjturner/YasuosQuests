#ifndef LOCAL_MAP_STATE_H
#define LOCAL_MAP_STATE_H

#include "GameState.h"
#include "Observer.h"
#include "HudWindow.h"
#include "LogMessageWindow.h"


#define FINAL_LEVEL 5

//Define images
#define PLAYER_SPRITE_SHEET "images/Actor1.png"
#define ERROR_LOADING_SPRITE_SHEET "Couldn't load sprite sheet"

//Define sounds
#define ATTACK_SOUND "audio/attack1.ogg"
#define HURT_SOUND "audio/hurt1.ogg"
#define DIE_SOUND "audio/die1.ogg"

#define LOCAL_MAP_MUSIC ("audio/local_map_music.ogg")


class Player;
class Level;
class MessageWindow;

class LocalMapState : public GameState, public Observer{

public:
	LocalMapState(StateMachine* s_machine);
	~LocalMapState();

	//Inherited implemented function
	void update(long elapsedTime);
	void render();
	void onEnter();
	void onExit();
	void handleEvents(long elapsed);
	void handleInput(long elapsed);

	void drawLevel();
	void drawEntity(sf::RenderWindow* graphics, Entity*);
	void drawHud(sf::RenderWindow* graphics);
	void drawNotifcation(sf::RenderWindow* graphics);
	void drawLogWindow(sf::RenderWindow* graphics);

	void loadImages();
	bool loadTextures();

	void createLoaders();
	void createLevel(int);
	void createPlayer();

	bool updateEntities(long);
	bool processUpdate(Entity *Character, long elapsed, float XMove, float YMove );

	void setNotification(std::string msg, long timer, sf::Color color);


	virtual void onNotify(Entity& entity, Event event);
	virtual int getId();
	sf::Vector2u getWindowGraphicSize();

	bool checkMove(Entity *Character, float *XMove, float *YMove);
	bool checkAilments(long);
	void checkLeveledUp(Entity*);

	bool playSound(sf::SoundBuffer&);
	bool playMusic(std::string);

	// Process death of an NPC/Monster
	bool death(Entity *Attacker, Entity *Victim);
	virtual bool pCDeath(Entity *Character);
	// Process death of a non-player character
	virtual bool nPCDeath(Entity *Character);

	// Process experience up
	virtual bool experience(Entity*, long Amount);
	Entity* findEntityAtCoordinate(sf::Vector2i position);
	void resetAllEntitiesFocusExcept(Entity*);
	void resetAllEntitiesFocus();
	bool hasLeveledUp(int);
private: 

	void updateMessages(Entity*, long elapsed);

	int num_level, fps_count, lastTime, id;

	Player* player;
	Level* currentLevel;

	std::map<std::string, sf::Texture> texture_map_list;
	
	//Graphics
	sf::Font font;
	sf::Sound sound;
	sf::SoundBuffer hurt_buffer;
	sf::SoundBuffer attack_buffer;
	sf::SoundBuffer die_buffer;

	sf::Music music;
	sf::Text notifications_text;
	
	MessageWindow* notifications_window;
	HudWindow hud_window;
	LogMessageWindow log_window;

	std::list<int>level_up_points;
};

#endif