#include "Capitalist.h"
#include "R.h"
using namespace sf;

Capitalist::Capitalist()
{
	gravity = 0.4905f;
	jumpSpeed = 25.0f;
	speedY = 0.0f;
	speed = 3.0f;
	health = 0.0f;
	boosting = false;
	onFire = false;
	texture = R::LoadTexture("sprite");
	sprite.setTexture(*texture);
	sprite.setScale(Vector2f(0.12f, 0.12f));
}

Capitalist::~Capitalist()
{
}