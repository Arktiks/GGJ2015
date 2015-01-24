#pragma once
#include "GameObject.h"

class Obstacle : public GameObject
{
public:
	Obstacle() : HP(0), damage(0), isDead(false), onFire(false) {};
	Obstacle(int hp, int dmg) : HP(hp), damage(dmg), isDead(false), onFire(false) {};

	virtual void TakeDamage(int dmg);
	virtual ~Obstacle() {};

	bool isDead;
	bool onFire;
	int HP;
	int damage;
};