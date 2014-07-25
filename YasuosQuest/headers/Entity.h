#ifndef ENTITY_H
#define ENTITY_H
#include "SFML\Graphics.hpp"
#include "MessageWindow.h"
#include <list>
#include "Subject.h"
#include "sCharItem.h"
#include "MCL.h"//Master Character list
#include "MIL.h"//Master Item list
#include "Msl.h"//Master Spell list
// Number of characters in file
#define NUM_CHARACTER_DEFINITIONS   256

// Character types
#define CHAR_PC          0
#define CHAR_NPC         1
#define CHAR_MONSTER     2

// AI types
#define CHAR_STAND       0
#define CHAR_WANDER      1
#define CHAR_ROUTE       2
#define CHAR_FOLLOW      3
#define CHAR_EVADE       4

// Action/Animation types
#define CHAR_IDLE        0
#define CHAR_MOVE        1
#define CHAR_ATTACK      2
#define CHAR_SPELL       3
#define CHAR_ITEM        4
#define CHAR_HURT        5
#define CHAR_DIE         6
#define CHAR_TALK        7

// Status ailments
#define AILMENT_POISON          1
#define AILMENT_SLEEP           2
#define AILMENT_PARALYZE        4
#define AILMENT_WEAK            8
#define AILMENT_STRONG         16
#define AILMENT_ENCHANTED      32
#define AILMENT_BARRIER        64
#define AILMENT_DUMBFOUNDED   128
#define AILMENT_CLUMSY        256
#define AILMENT_SUREFOOTED    512 
#define AILMENT_SLOW         1024
#define AILMENT_FAST         2048
#define AILMENT_BLIND        4096
#define AILMENT_HAWKEYE      8192
#define AILMENT_SILENCED    16384

#define NUM_SPRITES_IN_ROW 12
#define NUM_SPRITES_IN_COL 8
#define NUM_SPRITE_SETS_ROW_COUNT 4
#define NUM_SPRITE_SETS_COL_COUNT 2
#define MINIMUM_WALKING_DISTANCE 1000.0f
#define MAXIMUM_WALKING_DISTANCE_OFFSET 2000.0f

#define MAX_SOUNDS 3

class Level;
class LocalMapState;
class Route;

class Entity : public Subject{

public:

	Entity(sf::Texture& texture, Level* level, int row, int col);
	~Entity();


	// Animation info
	typedef struct {
		char Name[32];    // Name of animation
		bool Loop;        // To loop flag
	} sCharAnimationInfo;

	bool init(sf::Font* Font, sItem *MIL, sSpell *MSL, long NumAnimations, sCharAnimationInfo *Anims);
	void initAttributes(int);

	void draw(sf::RenderWindow* graphics);
	void drawStats(sf::RenderWindow* graphics);
	void drawHealth(sf::RenderWindow* graphics);
	void drawMessages(sf::RenderWindow* graphics);

	bool isValidLevelMove(int xpos, int ypos);
	bool isInViewingDistance(sf::Sprite opponent);
	bool isEnabled();
	bool isLocked();
	
	bool hasReachedGoal();
	bool hasSelectedFocus();
	bool hasMessageTimeExpired();

	bool move(long elapsed, float x, float y);

	bool update(long Elapsed, float *XMove, float *YMove);
	void updateMessage(long elapsed);
	virtual void simulateAi();

	void checkAttack(long, long, float, float, float, float, float &MoveX, float &MoveY);
	
	void incrementKillCount();
	
	bool addMessage(const char *Text, long Timer, sf::Color color);

	void addExperience(long);
	void removeExperience(long);
	long getExperience();

	void levelUp();

	void setLevel(Level*);
	void setGoal(sf::Sprite*);
	void setID(int);
	void setGoalReached(bool r);
	void setList(std::vector<Entity*>* list);
	void setAsFocusedEntity(bool);
	bool setBounds(float MinX, float MinY, float MinZ, float MaxX, float MaxY, float MaxZ);
	void setDirection(float dir);
	void setHealth(long);
	void setMessageTimer(long);
	void setMessage(char * text, long timer, sf::Color color);
	void setCharge(float);
	void setAilments(long);
	void setPosition(float, float);
	// Set lock and action timer
	bool setLock(long IDNum, bool State);
	bool setActionTimer(long Timer);
	
	void setSpeed(float);
	// Set evade/follow distance
	bool setDistance(long IDNum, float Distance);
	float setDistance(long IDNum);

	// Set route points
	bool setRoutes(long IDNum, long NumPoints, Route* Routes);
	// Set enable flags
	bool setEnable(long IDNum, bool enable);
	// Functions to Set/Get character type
	bool setType(long Type);
	// Functions to Set/Get character AI
	bool setAI(long Type);
	// Set a target character
	bool setTargetCharacter(long IDNum, long TargetNum);
	// Set text messages to float up from character
	bool getNextMessage();
	// Set action (w/timer)
	bool setAction(long Action, long AddTime = 0);
	bool contains(sf::Vector2f);

	MessageWindow& getMessageWindow();
	sf::Vector2f getPosition();
	int getKillCount();
	float getChargeRate();
	int getID();
	LocalMapState* getLocalMap();
	bool getBounds(float *MinX, float *MinY, float *MinZ, float *MaxX, float *MaxY, float *MaxZ);
	long getActionTimer();
	long getAction();
	long getMessageTimer();
	long getType();
	float getDirection();
	float getXYRadius(Entity *character);
	// Function to retrieve adjusted ability/other info
	float getSpeed(Entity*);
	float getCharge();
	long getHealth();
	long getMana();
	long getAilments();
	long  getAttack(Entity*);
	long  getDefense(Entity*);
	long  getAgility(Entity*);
	long  getResistance(Entity*);
	long  getMental(Entity*);
	long  getToHit(Entity*);
	long getAI();
	int getLevel();
	Entity* getAttacker();
	sf::Text& getMessage();
	std::string getEntityType();
	std::string getEntitySound(int);
	sf::Text* getLogMessage();
	bool isEnabled(long IDNum);
	

	// Functions to Set/Get character bounds
	float MinX, MinY, MinZ;   // Min bounding coordinates
	float MaxX, MaxY, MaxZ;   // Max bounding coordiantes

	void CalculateFollowMovement(float CharXPos, float CharZPos, float WalkSpeed,
		float FollowXPos, float FollowZPos, float FollowDistance,
		float *MoveX, float *MoveZ);

	void Entity::CalculateEvadeMovement(
		float CharXPos, float CharZPos, // Coordinate of character
		float WalkSpeed, // Walking speed of char.
		float FollowXPos, float FollowZPos, // Coords of evaded char
		float EvadeDistance, // Distance to evade
		float *MoveX, float *MoveZ);

	sf::Vector2f calculateDistance(sf::Sprite*opponent);
	void calculateDirection();


	// A mesh list
	typedef struct sCharacterMeshList {
		//char       Filename[MAX_PATH];  // Filename of mesh/anim
		long       Count;               // # characters using mesh
		//cMesh      Mesh;                // Mesh object
		//cAnimation Animation;           // Animation object

		sCharacterMeshList()  { Count = 0; }
		//~sCharacterMeshList() { Mesh.Free(); Animation.Free(); }
	} sCharacterMeshList;


	// Make sure there's a line of sight between characters
	virtual bool LineOfSight(\
		Entity *Source, Entity *Target, \
		float SourceX, float SourceY, float SourceZ, \
		float TargetX, float TargetY, float TargetZ)
	{
		return true;
	}
	// Get pointer to the character ICS
	//cCharICS *GetICS(long IDNum);

	
	Route* routes;
	// Set script 
	//bool setScript(long IDNum, char *ScriptFilename);
	//char *getScript(long IDNum);


	std::list<MessageWindow> messages;//Message to display for the entity
	sf::Text* log_message;
	MessageWindow current_message;

	// Process attack damage from spells and physical attacks
	bool damage(Entity *Victim, bool PhysicalAttack, long Amount, long DmgClass, long CureClass);

	// Resolve a physical attack from attacker to victim
	bool attack();

	// Process spell ailments when spell completed
	//bool spell(Enemy *Caster, sSpellTracker *SpellTracker, sSpell *Spells);

	// Apply spell effects
	//bool spellEffect(sCharacter *Caster, sCharacter *Target,	sSpell *Spell);

	// Process equipping/unequipping of item
	bool equip(long ItemNum, long Type, bool Equip);

	// Process item being used on character
	bool item(Entity *Owner, Entity *Target, long ItemNum, sCharItem *CharItem = NULL);

	// Process dropping an item
	bool drop(sCharItem *Item, long Quantity);

	// Process a PC teleport spell
	virtual bool pCTeleport(Entity *Character, sSpell *Spell);

	sCharacterDefinition definition; // Loaded definition
	void selectSpriteSet(int row, int col);
	long  LastAnim;           // Last animation
	long  LastAnimTime;       // Last animation time
	int sprite_set_width, sprite_set_height, selected_sprite_set_in_row, selected_sprite_set_in_col;

	sf::Vector2i source;//The x defines the animation frame and y defines the movement direction image to show (down, up, left, right)
	enum DIRECTIONS{ DOWN, LEFT, RIGHT, UP };//Movement directions

	
protected:

	int getNumRoutePoints();
	
	bool is_focused;
	sf::Text entity_type_text;


	void setEntitySound(int, std::string);
	void setEntityTypeText(std::string);
	void setEntityTypeTextColor(sf::Color);
	std::vector<Entity*>* list; //List of Entities on a level

private:

	sf::Font* m_Font;
	Level* current_level;//The current map level the Entity is on

	std::string* entity_sound;

	long  Definition;         // Character definition #
	long  ID;                 // ID # of character

	long  Type;               // PC, NPC, or MONSTER
	long  AI;                 // STAND, WANDER, etc

	bool  Enabled;            // Enabled flag (for updates)

	sCharItem *CharICS;        // PC character's ICS
	sItem      *m_MIL;                 // Master item list
	sSpell     *m_MSL;                 // Master spell list
	//char ScriptFilename[MAX_PATH]; // Associated script

	long  current_health;       // Current health points
	long  ManaPoints;         // Current mana points
	
	long  Ailments;           // Ailments against character

	long  Action;             // Current action
	float Direction;          // Angle character is facing
	

	bool  Locked;             // Specific action lock
	long  ActionTimer;        // Lock action countdown timer

	Entity *Attacker;     // Attacking character (if any)
	Entity *Victim;       // Character to attack

	long  SpellNum;           // Spell to cast when ready
	long  SpellTarget;        // Target type of spell
	float TargetX, TargetY; // Spell target coords

	long ItemNum;             // Item to use when ready
	sCharItem *CharItem;      // Item to remove from inventory

	float Distance;           // Follow/Evade distance
	Entity *TargetChar;   // Character to follow


	long  NumPoints;          // # points in route
	long  CurrentPoint;       // Current route point

	long  messageTimer;       // Text message timer
	sf::Color MessageColor;    // Color of text message

	//cObject Object;           // Character object class
	//cMesh   WeaponMesh;       // Weapon mesh
	//cObject WeaponObject;     // Weapon object	

	int kills;					//The amount of enemies killed
	sf::Sprite sprite;
};

#endif