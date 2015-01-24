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

	frames = 0;
	frameCount = 0;
	animationTimer = 0.0f;
	animationSmoothnes = 0.00f;

	speed = 0.0f;
}