#include "Game1.h"
#include <iostream>
#include "SFML\System\Vector2.hpp"
#include "SFML\Window\Keyboard.hpp"

Game1::Game1() : circleUp(1.0f)
{
	//sf::Vector2i screenSize()

	circle.setRadius(10.0f);
	circle.setPosition(100.0f, 100.0f);
	circle.setFillColor(sf::Color::Green);

	rectangle.setSize(sf::Vector2f(50.0f, 5.0f));
	rectangle.setPosition(100.0f, 200.0f);
	rectangle.setFillColor(sf::Color::Red);

	rectangle2.setSize(sf::Vector2f(50.0f, 5.0f));
	rectangle2.setPosition(100.0f, 50.0f);
	rectangle2.setFillColor(sf::Color::Red);

	character = Character();

	bool characterOnScreen = false;
}

void Game1::Draw(sf::RenderWindow &window)
{
	window.draw(circle);
	window.draw(rectangle);
	window.draw(rectangle2);
	if (characterOnScreen)
		window.draw(character.characterSprite);
	
}

void Game1::Update(float deltaTime, sf::Event &events)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		rectangle.setPosition((rectangle.getPosition() + sf::Vector2f(-5.0f, 0.0f)));
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		rectangle.setPosition((rectangle.getPosition() + sf::Vector2f(5.0f, 0.0f)));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		rectangle2.setPosition((rectangle2.getPosition() + sf::Vector2f(-5.0f, 0.0f)));
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		rectangle2.setPosition((rectangle2.getPosition() + sf::Vector2f(5.0f, 0.0f)));

	circle.setPosition((circle.getPosition() + sf::Vector2f(0.0f, 1.0f * circleUp)));

	if (circle.getGlobalBounds().intersects(rectangle.getGlobalBounds()))
	{
		std::cout << "asda" << std::endl;
		circleUp = -1.0f;
		//circle.setPosition((circle.getPosition() + sf::Vector2f(0.0f, -1.0f)));
	}

	if (circle.getGlobalBounds().intersects(rectangle2.getGlobalBounds()))
	{
		std::cout << "asda" << std::endl;
		circleUp = 1.0f;
		//circle.setPosition((circle.getPosition() + sf::Vector2f(0.0f, -1.0f)));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		characterOnScreen = true;


}

Game1::~Game1()
{
}