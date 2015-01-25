#pragma once
#include "GameObject.h"
#include "R.h"
enum itemType
{
	ITEMCANNON,
	ITEMSWORD,
	ITEMBOOMERANG,
	ITEMFIRE
};
class Item : public GameObject
{
public:
	Item(itemType item);
	itemType item;
	bool isDead;
	~Item();
};

