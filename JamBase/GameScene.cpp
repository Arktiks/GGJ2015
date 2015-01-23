#include "GameScene.h"
#include <iostream>
#include "SFML\System\Vector2.hpp"
#include "SFML\Window\Keyboard.hpp"
#include "Base\RNG.h"
using namespace sf; 

GameScene::GameScene() : jumpCheck(false), jumpTimer(0.0f), touchGround(false), jumpModifier(1.0f),
gravitation(1.2f), windowCheck(false), screenSize(Vector2f(1280.0f, 800.0f))
{
	StartPiece();
	view.reset(FloatRect(0.0f, 0.0f, 1280.0f, 800.0f)); // Kameran alustus windowin mukaan.
	view.rotate(0.0f);
}

void GameScene::Draw(sf::RenderWindow &window)
{
	for (std::vector<RectangleShape>::iterator it = groundVector.begin(); it != groundVector.end(); it++)
		window.draw(*it); // Piirret‰‰n scenet j‰rjestyksess‰.

	window.draw(character);
	window.setView(view);
}

void GameScene::Update(float deltaTime, Event &events)
{
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		rectangle.setPosition((rectangle.getPosition() + sf::Vector2f(-5.0f, 0.0f)));
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		rectangle.setPosition((rectangle.getPosition() + sf::Vector2f(5.0f, 0.0f)));*/

	character.setPosition(Vector2f((character.getPosition().x + 3.0f),
		character.getPosition().y)); // Hahmon liike.

	if (!jumpCheck && !touchGround) // Hahmon putoamisliike.
	{
		character.setPosition(Vector2f((character.getPosition().x),
			character.getPosition().y + 3.0f * gravitation));
	}

	for (std::vector<RectangleShape>::iterator it = groundVector.begin(); it != groundVector.end(); it++)
	{
		if ((*it).getGlobalBounds().intersects(character.getGlobalBounds())) // Pusketaan hahmoa ylˆs jos koskee maahan.
		{
			character.setPosition(Vector2f((character.getPosition().x),
				character.getPosition().y - 1.0f));
			touchGround = true;
			jumpCheck = false;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Space) && !jumpCheck && touchGround) // Testihyppy.
	{
		jumpModifier = 20.0f;
		character.setPosition((character.getPosition() + Vector2f(0.0f, -3.0f - jumpModifier)));
		jumpCheck = true;
		touchGround = false;
		jumpTimer++;
	}

	if (jumpCheck) // Jos hahmo on hyppyanimaatiossa.
	{
		jumpModifier *= 0.88f;
		character.setPosition((character.getPosition() + Vector2f(0.0f, -3.0f - jumpModifier)));
		jumpTimer++;
		if (jumpTimer >= 10.0f)
		{
			jumpCheck = false;
			jumpModifier = 20.0f;
			jumpTimer = 0.0f;
		}
	}

	/*if (RNG::Chance(50)) // ES p‰risee
		view.setRotation((float)RNG::Random(1));
	else
		view.setRotation(0.0f - (float)RNG::Random(1));*/

	//view.setCenter(Vector2f(view.getCenter().x + 2.0f, view.getCenter().y)); // Kameran scrollaus.
	view.setCenter(Vector2f(character.getGlobalBounds().left + 200.0f, view.getCenter().y));

	if ((int)view.getCenter().x % 500 == 0)
	{
		Piece1();
	}
}

GameScene::~GameScene()
{
}

void GameScene::StartPiece()
{
	character.setSize(Vector2f(10.0f, 50.0f)); // Testihahmo.
	character.setPosition(200.0f, 500.0f);
	character.setFillColor(Color::Green);

	RectangleShape tempGround;
	tempGround.setSize(Vector2f(screenSize.x, 50.0f)); // Alustetaan maaper‰.
	tempGround.setPosition(0, (screenSize.y - tempGround.getSize().y));
	tempGround.setFillColor(Color::Red);
	groundVector.push_back(tempGround);
}

void GameScene::Piece1()
{
	RectangleShape tempGround(Vector2f(1280.0f, 50.0f));
	tempGround.setFillColor(Color::Blue);
	tempGround.setPosition(Vector2f(view.getCenter().x + 480.0f, screenSize.y - tempGround.getSize().y));
	groundVector.push_back(tempGround);

	CircleShape aurinko(10.0f, 30u);
	aurinko.setFillColor(Color::Magenta);
	aurinko.setPosition(Vector2f(view.getCenter().x, screenSize.y - 400.0f));
	//groundVector.push_back(aurinko);
}