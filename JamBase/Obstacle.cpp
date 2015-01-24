#include "Obstacle.h"

void Obstacle::TakeDamage(int dmg)
{
	HP -= dmg;
	if (HP <= 0)
		isDead = true;
}