#pragma once
#include <SFML\Graphics.hpp>
#include "SceneParent.h"
#include "SFML\System\String.hpp"

class MoneyInterface :
	public SceneParent
{
public:
	MoneyInterface();
	void Draw(sf::RenderWindow &window);
	void Update(float deltaTime, sf::Event &events);
	~MoneyInterface() {};

private:
	//int moneyAmount;
	sf::RectangleShape moneyMeter;
	//sf::Text characterName;
	//const sf::String name = "money dude";
};