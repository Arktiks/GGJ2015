#include "Item.h"


Item::Item(itemType item)
{
	this->item = item;
	isDead = false;
	if (item == ITEMCANNON)
	{
		sprite.setTexture(*R::LoadTexture("cannon"));
	}
	if (item == ITEMSWORD)
	{
		sprite.setTexture(*R::LoadTexture("sword"));
	}
	if (item == ITEMBOOMERANG)
	{
		sprite.setTexture(*R::LoadTexture("bomerang"));
	}
	if (item == ITEMFIRE)
	{
		sprite.setTexture(*R::LoadTexture("cannonBall"));
		sprite.setScale(2.0f, 2.0f);
	}
}


Item::~Item()
{
}
