#include "MoneyInterface.h"
#include <iostream>
#include "SFML\System\Vector2.hpp"
#include "Base\R.h"
#include "Gameboard.h"
#include <sstream>
#include "RNG.h"

using namespace sf;

MoneyInterface::MoneyInterface() : moneyMeter(Vector2f(0.0f, 20.0f))
{
moneyMeter.setFillColor(Color::Red);
	fontSize = 128;
	characterName.setCharacterSize(fontSize);
	characterName.setOrigin(75, 75);
	characterName.setString("asd ");
	characterName.setColor(Color::White);
	characterName.setFont(*R::LoadFont("DamagedSataLight"));
}

void MoneyInterface::Draw(sf::RenderWindow &window)
{
	window.draw(moneyMeter);
	
	

	characterName.setCharacterSize(fontSize);
	if (lastKill > 3)
	{
		if (lastKill > 20)
			characterName.setColor(sf::Color(10 * lastKill,  2*lastKill-15, 2*lastKill-15));
		else if (lastKill > 15)
			characterName.setColor(sf::Color(6 * lastKill, 3 * lastKill, 10 * lastKill));
		else if (lastKill > 10)
			characterName.setColor(sf::Color(3 * lastKill, 6 * lastKill, 6 * lastKill));
		else
			characterName.setColor(sf::Color(0, 10 * lastKill, 3 * lastKill));
		fontSize = 120;
		characterName.setOrigin(75, 75);

		window.draw(characterName);
	}
	
	else if (lastTop > 3 && Gameboard::textTimer < 1)
	{
		if (lastTop > 19)
		{
			characterName.setOrigin(100, 150);
			fontSize += RNG::Between(-8, 18);
		}
		else if (lastTop > 14)
		{
			fontSize += RNG::Between(-6, 12);
		}
		
		window.draw(characterName);
	}

}

void MoneyInterface::Update(float deltaTime, Event &events)
{
	moneyMeter.setSize(Vector2f(100.0f * (float)Gameboard::moneyAmount, 20.0f));
	moneyMeter.setPosition(Vector2f(Gameboard::gameLocation.x - 600.0f,
		Gameboard::gameLocation.y - 380.0f));
	std::string Result;   
	int number;// string which will contain the result
	if (lastKill > Gameboard::swordCounter)
	{
		lastTop = lastKill;
		Gameboard::textTimer = 0;
	}
	lastKill = Gameboard::swordCounter;
	if (lastKill > 3)
	{
		number = lastKill;
	}
	else
	{
		number = lastTop;
	}
		std::ostringstream convert;   // stream used for the conversion
		 
		convert << number;      // insert the textual representation of 'Number' in the characters in the stream
		Result = convert.str();
		characterName.setString(Result);
		characterName.setPosition(Vector2f(Gameboard::gameLocation.x + 0.0f,
		Gameboard::gameLocation.y + 0.0f));
}