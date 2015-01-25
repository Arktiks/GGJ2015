#pragma once
#include "SFML\System\Vector2.hpp"
#include "SoundMaster.h"
enum chargeType
{
	CANNON,
	SWORD,
	BOMERANG,
	FIRE,
	NONE
};
class Gameboard
{

public:
	Gameboard();
	~Gameboard() {};

	static sf::Vector2f playerLocation;
	static sf::Vector2f gameLocation;
	static sf::Vector2i windowSize;

	static bool characterIsDead;

	// Kapitalisti
	static int moneyAmount;
	static int chargeAmount;
	static chargeType weapon;
	static SoundMaster soundMaster;
	static void loadSounds();
	static float weaponTimer;
	static float swordTimer;
	static int swordCounter;
	static float textTimer;
	static float dropDownTimer;

	//void SetWindowSize(sf::Vector2i size);
	//sf::Vector2i GetWindowSize();
};

