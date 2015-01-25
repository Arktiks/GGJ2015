#include "Projectile.h"
#include "RNG.h"
#include "Gameboard.h"

Projectile::Projectile(projectileType projectileType)
{
	isDead = false;
	type = projectileType;
	if (type == BULLET)
	{
		speedX = RNG::Between(15,30);
		speedY = RNG::Between(20,80);
		speedY = speedY / 15;
		texture = R::LoadTexture("cannonBall");
		sprite.setTexture(*texture);
		sprite.setScale(0.50f, 0.50f);
	}
	if (type == BLADE)
	{
		sprite.setTexture(*R::LoadTexture("sword"));
		sprite.setOrigin(16, 120);
		speedX = 0;
		speedY = 0;
	}
	if (type == BOMERANG)
	{
		sprite.setTexture(*R::LoadTexture("bomerang"));
		sprite.setOrigin(32, 32);
		sprite.setScale(0.5, 0.5);
		speedX = RNG::Between(20, 40);
		speedY = -5;
	}
}



Projectile::~Projectile()
{
}
void Projectile::Update()
{
	if (type == BOMERANG)
	{
		if (sprite.getPosition().x < Gameboard::playerLocation.x)
			speedX += 0.2;
		else
		{
			speedX -= 0.2;
		}
		if (sprite.getPosition().y < Gameboard::playerLocation.y)
			speedY += 0.4;
		else
		{
			speedY -= 0.2;
		}
	}
}