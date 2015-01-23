#pragma once
#include "SFML\System\Vector2.hpp"

class Gameboard
{
public:
	Gameboard() {};
	void SetWindowSize(sf::Vector2i size);
	sf::Vector2i GetWindowSize();
	~Gameboard() {};

private:
	static sf::Vector2i windowSize;
};