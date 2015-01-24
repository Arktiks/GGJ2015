#include "DubbelDash.h"
#include "R.h"

DubbelDash::DubbelDash()
{
	weight = 12.0f;
	jumpPower = 35.0f;
	jumpThrust = 0.0f;
	jumpFloat = 0.25f;
	speed = 15.0f;
	health = 0.0f;
	boosting = false;
	onFire = false;
	texture = R::LoadTexture("dubbeldash");
	sprite.setTexture(*texture);
	sprite.setScale(sf::Vector2f(0.12f, 0.12f));
}


DubbelDash::~DubbelDash()
{
}
