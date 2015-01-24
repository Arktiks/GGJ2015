#include "Capitalist.h"
#include "R.h"
using namespace sf;

Capitalist::Capitalist()
{
	weight = 12.0f;
	jumpPower = 35.0f;
	jumpThrust = 0.0f;
	jumpFloat = 0.25f;
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