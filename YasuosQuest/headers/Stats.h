#pragma once
#include "Entity.h"

class Stats{

public:
	Stats();
	~Stats();

		long  Definition;         // Character definition #
		long  ID;                 // ID # of character

		long  Type;               // PC, NPC, or MONSTER
		long  AI;                 // STAND, WANDER, etc

		bool  Enabled;            // Enabled flag (for updates)

		//sCharacterDefinition Def; // Loaded definition
		//cCharICS *CharICS;        // PC character's ICS

		//char ScriptFilename[MAX_PATH]; // Associated script

		long  HealthPoints;       // Current health points
		long  ManaPoints;         // Current mana points
		long  Ailments;           // Ailments against character
		float Charge;             // Attack charge

		long  Action;             // Current action
		float XPos, YPos, ZPos;   // Current coordinates
		float Direction;          // Angle character is facing
		long  LastAnim;           // Last animation
		long  LastAnimTime;       // Last animation time

		bool  Locked;             // Specific action lock
		long  ActionTimer;        // Lock action countdown timer

		Entity *Attacker;     // Attacking character (if any)
		Entity *Victim;       // Character to attack

		long  SpellNum;           // Spell to cast when ready
		long  SpellTarget;        // Target type of spell
		float TargetX, TargetY, TargetZ; // Spell target coords

		long ItemNum;             // Item to use when ready
		//	sCharItem *CharItem;      // Item to remove from inventory

		float Distance;           // Follow/Evade distance
		Entity *TargetChar;   // Character to follow
		float MinX, MinY, MinZ;   // Min bounding coordinates
		float MaxX, MaxY, MaxZ;   // Max bounding coordiantes

		// Path/Route structure
		typedef struct {
			float XPos, YPos, ZPos;   // Target position
		} sRoutePoint;

		long  NumPoints;          // # points in route
		long  CurrentPoint;       // Current route point
		sRoutePoint *Route;       // Route points

		char  Message[128];       // Text message
		long  MessageTimer;       // Text message timer
		sf::Color MessageColor;    // Color of text message

		//cObject Object;           // Character object class
		//cMesh   WeaponMesh;       // Weapon mesh
		//cObject WeaponObject;     // Weapon object

		Entity *Prev, *Next;  // Linked list of characters		
	
};

