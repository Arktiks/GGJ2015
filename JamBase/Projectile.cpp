#include "Projectile.h"


Projectile::Projectile(projectileType projectileType)
{
	type = projectileType;
	if (type == BULLET)
	{
		speedX = 100;
		speedY = 0;
		texture = R::LoadTexture("JP");
		sprite.setTexture(*texture);
		sprite.setScale(0.25f, 0.25f);
	}
}



Projectile::~Projectile()
{
}
void Projectile::Update()
{
	
}