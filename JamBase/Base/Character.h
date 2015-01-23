#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

class Character
{
public:

	Character();
	Character(float speed, float health, sf::FloatRect hitBox, sf::Sprite characterSprite);

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

	sf::Sprite characterSprite;

private:

	float speed, health;

	bool boosting, onFire;

	sf::FloatRect hitBox;



};

