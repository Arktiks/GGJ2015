#include "Capitalist.h"
#include "R.h"
using namespace sf;

Capitalist::Capitalist()
{
	gravity = 0.5f;
	jumpSpeed = 15.5;
	speedY = 0.0f;
	speed = 15.0f;
	health = 0.0f;
	boosting = false;
	onFire = false;
	texture = R::LoadTexture("Fireman_run");
	texture->setRepeated(true);
	sprite.setTexture(*texture);
	sprite.setScale(Vector2f(2.5f, 2.5f));

	frames = 5;
	frameCount = 0;
	animationTimer = 0.0f;
	animationSmoothnes = 0.02f;
}