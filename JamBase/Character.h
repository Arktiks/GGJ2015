#pragma once
#include "GameObject.h"

class Character : public GameObject
{
public:
	Character();
	Character(float speed, float health, sf::FloatRect hitBox);
	~Character();

	float GetSpeed();
	float GetHealth();
	bool GetBoosting();
	bool GetOnFire();

	sf::FloatRect GetHitBox();

	void SetSpeed(float newSpeed);
	void SetHealth(float newSpeed);
	void SetBoosting(bool);
	void SetOnFire(bool);
	void SetHitBox(sf::FloatRect);

	float weight, jumpPower, jumpThrust, jumpFloat;

protected:
	float speed, health;
	bool boosting, onFire;
	sf::FloatRect hitBox;
};