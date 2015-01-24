#pragma once
#include <SFML\Audio.hpp>
#include "GameObject.h"
#include "Gameboard.h"
class Character : public GameObject
{
public:
	Character();
	Character(float speed, float health, sf::FloatRect hitBox);
	~Character();

	float GetSpeed();
	float GetSpeedY(){ return speedY; }
	float GetHealth();
	bool GetBoosting();
	bool GetOnFire();

	sf::FloatRect GetHitBox();

	void SetSpeed(float newSpeed);
	void SetSpeedY(float newSpeed){ speedY = newSpeed; }
	void SetHealth(float newSpeed);
	void SetBoosting(bool);
	void SetOnFire(bool);
	void SetHitBox(sf::FloatRect);
  	void Jump(){ speedY = -jumpSpeed; jumpSound.play(); }
	void createSounds();
	sf::Sound jumpSound;
	float gravity, jumpSpeed;

protected:
	float speed, speedY, health;
	bool boosting, onFire;
	sf::FloatRect hitBox;
};