#pragma once
#include "../GameObject.h"
#include <SFML\Graphics.hpp>
#include <iostream>

class Character : public GameObject
{
public:

	Character();
	Character(float speed, float health, sf::FloatRect hitBox, char* path);

	~Character();

	float GetSpeed();
	float GetHealth();

	bool GetBoosting();
	bool GetOnFire();

	sf::FloatRect GetHitBox();
	sf::Sprite GetCharacterSprite();

	void SetSpeed(float newSpeed);
	void SetHealth(float newSpeed);

	void SetBoosting(bool);
	void SetOnFire(bool);

	void SetHitBox(sf::FloatRect);
	void SetCharacterSprite(sf::Sprite);



private:

	float speed, health;

	bool boosting, onFire;

	sf::FloatRect hitBox;



};

