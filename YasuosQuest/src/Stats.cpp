#include "../headers/stdafx.h"
#include "../headers/Stats.h"


Stats::Stats(){

	Definition = 0;         // Set to definition #0
	ID = -1;                // Set to no ID
	Type = CHAR_NPC;        // Set to NPC character
	Enabled = false;        // Set to not enabled

	Ailments = 0;           // Set no ailments
	Charge = 0.0f;          // Set no charge

	// Clear definition
	//	ZeroMemory(&Def, sizeof(sCharacterDefinition));
	//CharICS = NULL;         // Set no ICS

	//	ScriptFilename[0] = 0;  // Set no script

	Action = CHAR_IDLE;     // Set default animation
	LastAnim = -1;          // Reset animation

	Locked = false;         // Set no lock
	ActionTimer = 0;        // Set no action timer

	Attacker = NULL;        // Set no attacker
	Victim = NULL;          // Set no victim

	ItemNum = 0;            // Set no item to use
	//CharItem = NULL;        // Set no item to decrease

	Distance = 0.0f;        // Set distance
	TargetChar = NULL;      // Set no target character

	// Clear bounding box (for limiting movement)
	MinX = MinY = MinZ = MaxX = MaxY = MaxZ = 0.0f;

	NumPoints = 0;          // Set no route points
	Route = NULL;           // Set no route

	Message[0] = 0;         // Clear message
	MessageTimer = 0;       // Set no message timer

	Prev = Next = NULL;     // Clear linked list pointers

}


Stats::~Stats(){

		//	if (CharICS != NULL) {  // Release character ICS
		//	CharICS->Free();
		//	delete CharICS;
		//	}

		delete[] Route;       // Release route

		//	WeaponObject.Free();   // Release weapon object
		//	WeaponMesh.Free();     // Release weapon mesh
		//	Object.Free();         // Release character object

		delete Next;           // Delete next character in list

}
