#pragma once
#include "GameObject.h"
class Obstacle :
	public GameObject
{
public:
	Obstacle(){}
	Obstacle(int _hp, int _dmg);
	~Obstacle();
	void takeDamage(int _dmg);

	bool isDead;
	bool onFire;
	int HP;
	int damage;
};