#include "MoneyInterface.h"
#include "SFML\System\Vector2.hpp"
#include "Gameboard.h"
using namespace sf;

MoneyInterface::MoneyInterface() : moneyMeter(Vector2f(0.0f, 20.0f))
{
	moneyMeter.setFillColor(Color::Red);
}

void MoneyInterface::Draw(sf::RenderWindow &window)
{
	window.draw(moneyMeter);
}

void MoneyInterface::Update(float deltaTime, Event &events)
{
	moneyMeter.setSize(Vector2f(100.0f * (float)Gameboard::moneyAmount, 20.0f));
	moneyMeter.setPosition(Vector2f(Gameboard::gameLocation.x - 600.0f,
		Gameboard::gameLocation.y - 380.0f));
}