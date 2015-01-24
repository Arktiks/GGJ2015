#include "MoneyInterface.h"
#include <iostream>
#include "SFML\System\Vector2.hpp"
#include "Base\R.h"
#include "Gameboard.h"
using namespace sf;

MoneyInterface::MoneyInterface() : moneyMeter(Vector2f(0.0f, 20.0f))
{
	moneyMeter.setFillColor(Color::Red);
	//characterName.setString(name);
	//characterName.setColor(Color::White);
	//characterName.setFont(*R::LoadFont("arial"));
}

void MoneyInterface::Draw(sf::RenderWindow &window)
{
	window.draw(moneyMeter);
	//window.draw(characterName);
}

void MoneyInterface::Update(float deltaTime, Event &events)
{
	moneyMeter.setSize(Vector2f(100.0f * (float)Gameboard::moneyAmount, 20.0f));
	moneyMeter.setPosition(Vector2f(Gameboard::gameLocation.x - 600.0f,
		Gameboard::gameLocation.y - 380.0f));

	//characterName.setPosition(Vector2f(Gameboard::gameLocation.x + 450.0f,
		//Gameboard::gameLocation.y + 350.0f));
}