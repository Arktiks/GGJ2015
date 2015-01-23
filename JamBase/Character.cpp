#include "Character.h"


Character::Character()
{
}

Character::Character(float tempSpeed, float tempHealth, sf::FloatRect tempHitBox) : GameObject()
{
	speed = tempSpeed;
	health = tempHealth;
	hitBox = tempHitBox;
	onFire = false;
	boosting = false;
}

Character::~Character()
{

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