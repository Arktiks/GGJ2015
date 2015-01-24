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
	texture = R::LoadTexture("sprite");
	sprite.setTexture(*texture);
	sprite.setScale(Vector2f(0.12f, 0.12f));
}

Capitalist::~Capitalist()
{
}