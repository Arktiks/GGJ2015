#pragma once
#include "Gameobject.h"
#include "R.h"

enum projectileType
{
	BULLET,
	BLADE,
	BOOMERANG
};

class Projectile : public GameObject
{
public:
	Projectile(projectileType projectileType);
	~Projectile();
	float speedX, speedY;
	bool isDead;
	void Update();
	projectileType type;
private:
};

