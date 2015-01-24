#include "WalkingEnemy.h"
#include "R.h"

WalkingEnemy::WalkingEnemy()
{
	isDead = false;
	onFire = false;
	HP = 9999;
	damage = 1;
	texture = R::LoadTexture("slime_sheet");
	sprite.setTexture(*texture);

	frames = 7;
	frameCount = 0;
	animationTimer = 0.0f;
	animationSmoothnes = 0.02f;

	speed = 3.0f;
}