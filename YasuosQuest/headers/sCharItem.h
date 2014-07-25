#pragma once
#include <iostream>
class sCharItem{


public:

	sCharItem();
	~sCharItem();

	// Load, save, and free a list of items
	bool Load(char *Filename);
	bool Save(char *Filename);
	bool Free();

	// Add and remove an item
	bool Add(long ItemNum, long Quantity,
		sCharItem *OwnerItem = NULL);
	bool Remove(sCharItem *Item);

	// Retrieve # items or parent linked list object
	long      GetNumItems();
	sCharItem *GetParentItem();
	sCharItem *GetItem(long Num);

	// Re-ordering functions
	bool Arrange();
	bool MoveUp(sCharItem *Item);
	bool MoveDown(sCharItem *Item);

	long      ItemNum;          // MIL item number
	long      Quantity;         // Quantity of item (ie coins)

	sCharItem  *Prev, *Next;    // linked list pointers

	long       Index;           // This items index #
	long       Owner;           // Owner index #
	sCharItem  *Parent;         // Parent of a contained item


private:
	long      m_NumItems;     // # items in inventory
	sCharItem *m_ItemParent;  // Linked list parent item

	// Functions to read in next long or float # in file
	long  GetNextLong(FILE *fp);
	float GetNextFloat(FILE *fp);

};
