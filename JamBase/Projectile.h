#pragma once
#include "Gameobject.h"

enum projectileType
{
	BULLET
};

class Projectile : public GameObject
{
public:
	Projectile(projectileType projectileType);
	~Projectile();
	float speedX, speedY;
	bool isDead;
	projectileType type;
private:
};

