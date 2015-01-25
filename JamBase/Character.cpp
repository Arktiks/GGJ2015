#include "Character.h"

void Character::createSounds()
{
	jumpSound =(*Gameboard::soundMaster.FindSound("jump"));
}

float Character::GetSpeed()
{
	return speed;
}
float Character::GetHealth()
{
	return health;
}

bool Character::GetBoosting()
{
	return boosting;
}

bool Character::GetOnFire()
{
	return onFire;
}

sf::FloatRect Character::GetHitBox()
{
	return hitBox;
}

void Character::SetSpeed(float newSpeed)
{
	speed = newSpeed;
}

void Character::SetHealth(float newHealth)
{
	health = newHealth;
}

void Character::SetBoosting(bool boost)
{
	boosting = boost;
}

void Character::SetOnFire(bool fire)
{
	onFire = fire;
}

void  Character::SetHitBox(sf::FloatRect newHitBox)
{
	hitBox = newHitBox;
}