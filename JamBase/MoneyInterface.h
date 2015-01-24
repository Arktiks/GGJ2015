#pragma once
#include <SFML\Graphics.hpp>
#include "SceneParent.h"

class MoneyInterface : public SceneParent
{
public:
	MoneyInterface();
	void Draw(sf::RenderWindow &window);
	void Update(float deltaTime, sf::Event &events);
	~MoneyInterface() {};

private:
	sf::RectangleShape moneyMeter;
};