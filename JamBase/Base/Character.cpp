#include "Character.h"


Character::Character()
{
	sf::Texture tempCharTex;
	if (!tempCharTex.loadFromFile("base\jp.png"))
	{
		std::cout << "Placeholder character texture cannot be loaded!" << std::endl;
	}
	sf::Sprite tempCharSprite;
	tempCharSprite.setTexture(tempCharTex);
	Character(
				0, // speed
				1, // health
				sf::FloatRect(400, 400, 10, 10), // hitbox
				tempCharSprite // sprite
		);
}

Character::Character(float tempSpeed, float tempHealth, sf::FloatRect tempHitBox, sf::Sprite tempCharacterSprite)
{
	speed = tempSpeed;
	health = tempHealth;
	hitBox = tempHitBox;
	characterSprite = tempCharacterSprite;
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

sf::Sprite Character::GetCharacterSprite()
{
	return characterSprite;
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

void  Character::SetCharacterSprite(sf::Sprite newSprite)
{
	characterSprite = newSprite;
}