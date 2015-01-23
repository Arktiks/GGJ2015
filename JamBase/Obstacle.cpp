#include "Obstacle.h"


Obstacle::Obstacle(int _hp, int _dmg)
{
	HP = _hp;
	damage = _dmg;
	isDead = false;
}


Obstacle::~Obstacle()
{
}

void Obstacle::takeDamage(int _dmg)
{
	HP -= _dmg;

	if (HP <= 0)
		isDead = true;
}