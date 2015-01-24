#include "Rock.h"
#include "R.h"

Rock::Rock()
{
	isDead = false;
	onFire = false;
	HP = 9999;
	damage = 1;
	texture = R::LoadTexture("rock");
	sprite.setTexture(*texture);
}