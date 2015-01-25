#include "WalkingEnemy2.h"
#include "R.h"

WalkingEnemy2::WalkingEnemy2()
{
	isDead = false;
	onFire = false;
	HP = 3;
	damage = 1;
	texture = R::LoadTexture("Dude_just_run");
	sprite.setTexture(*texture);
	sprite.setScale(0.8f, 0.8f);

	frames = 8;
	frameCount = 0;
	animationTimer = 0.0f;
	animationSmoothnes = 0.13f;

	speed = -5.0f;
}