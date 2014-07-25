#include "../headers/stdafx.h"
#include "../headers/sCharItem.h"


sCharItem::sCharItem(){

	Prev = Next = Parent = NULL;
	Index = 0; Owner = -1;
}

sCharItem::~sCharItem() { 
	
	delete Next; 

}


bool sCharItem::Add(long ItemNum, long Quantity, \
	sCharItem *OwnerItem)
{
	sCharItem *Item;

	// Create a new item structure
	Item = new sCharItem();

	// Insert into top of list
	Item->Next = m_ItemParent;
	if (m_ItemParent != NULL)
		m_ItemParent->Prev = Item;
	m_ItemParent = Item;

	// Fill the item structure
	Item->ItemNum = ItemNum;
	Item->Quantity = Quantity;
	Item->Parent = OwnerItem;

	// Increate # of items
	m_NumItems++;

	return true;
}

bool sCharItem::Remove(sCharItem *Item)
{
	sCharItem *ItemPtr, *NextItem;

	// Remove child objects first
	if ((ItemPtr = m_ItemParent) != NULL) {
		while (ItemPtr != NULL) {
			NextItem = ItemPtr->Next;
			if (ItemPtr->Parent == Item)
				Remove(ItemPtr);
			ItemPtr = NextItem;
		}
	}

	// Remove from linked list and reset root
	// if it's the current head of list.
	if (Item->Prev != NULL)
		Item->Prev->Next = Item->Next;
	else
		m_ItemParent = Item->Next;
	if (Item->Next != NULL)
		Item->Next->Prev = Item->Prev;

	// Clear link list
	Item->Prev = Item->Next = NULL;

	// Remove an item
	m_NumItems--;

	// Free memory
	delete Item;

	return true;
}

long sCharItem::GetNumItems()
{
	return m_NumItems;
}

sCharItem *sCharItem::GetParentItem()
{
	return m_ItemParent;
}

sCharItem *sCharItem::GetItem(long Num)
{
	sCharItem *Item;

	Item = m_ItemParent;
	while (Num--) {
		if (Item == NULL)
			return NULL;
		Item = Item->Next;
	}
	return Item;
}

bool sCharItem::Arrange()
{
	sCharItem *Item, *PrevItem;

	// Start at top of linked list and float
	// each item up that has a lesser ItemNum.
	// Break if past bottom of list
	Item = m_ItemParent;
	while (Item != NULL) {

		// Check previous item to float up
		if (Item->Prev != NULL) {

			// Keep floating up while prev item has
			// a lesser ItemNum value or until top
			// of list has been reached.
			while (Item->Prev != NULL) {
				PrevItem = Item->Prev;  // Get prev item pointer

				// Break if no more to float up
				if (Item->ItemNum >= PrevItem->ItemNum)
					break;

				// Swap 'em
				if ((PrevItem = Item->Prev) != NULL) {
					if (PrevItem->Prev != NULL)
						PrevItem->Prev->Next = Item;

					if ((PrevItem->Next = Item->Next) != NULL)
						Item->Next->Prev = PrevItem;

					if ((Item->Prev = PrevItem->Prev) == NULL)
						m_ItemParent = Item;

					PrevItem->Prev = Item;
					Item->Next = PrevItem;
				}
			}
		}

		// Go to next object
		Item = Item->Next;
	}

	return true;
}

bool sCharItem::MoveUp(sCharItem *Item)
{
	sCharItem *PrevItem;

	// Swap item and item before it
	if ((PrevItem = Item->Prev) != NULL) {
		if (PrevItem->Prev != NULL)
			PrevItem->Prev->Next = Item;

		if ((PrevItem->Next = Item->Next) != NULL)
			Item->Next->Prev = PrevItem;

		if ((Item->Prev = PrevItem->Prev) == NULL)
			m_ItemParent = Item;

		PrevItem->Prev = Item;
		Item->Next = PrevItem;
	}

	return true; // Return success
}

bool sCharItem::MoveDown(sCharItem *Item)
{
	sCharItem *NextItem;

	// Swap item and item after it
	if ((NextItem = Item->Next) != NULL) {
		if ((Item->Next = NextItem->Next) != NULL)
			NextItem->Next->Prev = Item;

		if ((NextItem->Prev = Item->Prev) != NULL)
			Item->Prev->Next = NextItem;
		else
			m_ItemParent = NextItem;

		NextItem->Next = Item;
		Item->Prev = NextItem;
	}

	return true; // Return success
}

long sCharItem::GetNextLong(FILE *fp)
{
	char Buf[1024];
	long Pos = 0;
	int c;

	// Read until EOF or EOL
	while (1) {
		if ((c = fgetc(fp)) == EOF)
			break;
		if (c == 0x0a)
			break;
		if ((c >= '0' && c <= '9') || c == '.' || c == '-')
			Buf[Pos++] = c;
	}
	if (!Pos)
		return -1;
	Buf[Pos] = 0;

	return atol(Buf);
}

float sCharItem::GetNextFloat(FILE *fp)
{
	char Buf[1024];
	long Pos = 0;
	int c;

	// Read until EOF or EOL
	while (1) {
		if ((c = fgetc(fp)) == EOF)
			break;
		if (c == 0x0a)
			break;
		if ((c >= '0' && c <= '9') || c == '.' || c == '-')
			Buf[Pos++] = c;
	}
	Buf[Pos] = 0;

	return (float)atof(Buf);
}
