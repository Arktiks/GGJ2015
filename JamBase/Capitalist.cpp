#include "Capitalist.h"
#include "R.h"
using namespace sf;

Capitalist::Capitalist()
{
	gravity = 0.6f;
	jumpSpeed = 16.5;
	speedY = 0.0f;
	speed = 10.0f;
	health = 0.0f;
	boosting = false;
	onFire = false;
	texture = R::LoadTexture("Fireman_run");
	texture->setRepeated(true);
	sprite.setTexture(*texture);
	sprite.setScale(Vector2f(1.5f, 1.5f));

	frames = 5;
	frameCount = 0;
	animationTimer = 0.0f;
	animationSmoothnes = 0.02f;
}