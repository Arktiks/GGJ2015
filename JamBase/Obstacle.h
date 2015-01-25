#pragma once
#include "GameObject.h"

class Obstacle : public GameObject
{
public:
	Obstacle() : HP(10), damage(0), isDead(false), onFire(false), speed(0.0f), speedY(0.0f) {};
	Obstacle(int hp, int dmg) : HP(hp), damage(dmg), isDead(false), onFire(false), speed(0.0f), speedY(0.0f) {};

	virtual void TakeDamage(int dmg);
	virtual ~Obstacle() {};

	bool isDead;
	bool onFire;
	int HP;
	int damage;
	float speed;
	float speedY;
};