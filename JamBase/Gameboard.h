#pragma once
#include "SFML\System\Vector2.hpp"
#include "SoundMaster.h"
class Gameboard
{
public:
	Gameboard() {};
	~Gameboard() {};

	static sf::Vector2f playerLocation;
	static sf::Vector2f gameLocation;
	static sf::Vector2i windowSize;

	// Kapitalisti
	static int moneyAmount;
	static SoundMaster soundMaster;
	static void loadSounds();
	//void SetWindowSize(sf::Vector2i size);
	//sf::Vector2i GetWindowSize();
};

