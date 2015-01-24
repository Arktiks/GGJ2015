#pragma once
#include <SFML\Audio.hpp>
#include "GameObject.h"
#include "Gameboard.h"
class Character : public GameObject
{
public:
	Character() : speed(0.0f), health(0.0f), boosting(false), onFire(false) {};
	Character(float speed, float health, sf::FloatRect hitBox)
		: speed(speed), health(health), hitBox(hitBox), onFire(false), boosting(false) {};
	~Character() {};

	float GetSpeed();
	float GetHealth();
	bool GetBoosting();
	bool GetOnFire();
	sf::FloatRect GetHitBox();

	float GetSpeedY() { return speedY; }
	void SetSpeedY(float newSpeed) { speedY = newSpeed; }
	void Jump() { speedY = -jumpSpeed; jumpSound.play(); }

	void SetSpeed(float newSpeed);
	void SetHealth(float newSpeed);
	void SetBoosting(bool);
	void SetOnFire(bool);
	void SetHitBox(sf::FloatRect);
  	
	void createSounds();

	sf::Sound jumpSound;
	float gravity, jumpSpeed;

protected:
	float speed, speedY, health;
	bool boosting, onFire;
	sf::FloatRect hitBox;
};