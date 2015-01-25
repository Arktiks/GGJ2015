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
<<<<<<< HEAD
	int moneyAmount;
	int lastKill;
	int lastTop;
	int fontSize;

	sf::RectangleShape moneyMeter;
	sf::Text characterName;
	//const sf::String name = "money dude";
=======
	sf::RectangleShape moneyMeter;
>>>>>>> origin/master
};