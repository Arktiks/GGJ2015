#include "GameScene.h"
#include <iostream>
#include "SFML\System\Vector2.hpp"
#include "SFML\Window\Keyboard.hpp"
#include "Base\RNG.h"
#include "Gameboard.h"
#include "Capitalist.h"
using namespace sf; 

GameScene::GameScene() : jumpCheck(false), jumpTimer(0.0f), touchGround(false), jumpModifier(1.0f),
gravitation(1.2f), windowCheck(false), screenSize(Vector2f(1280.0f, 800.0f)), jumpTicks(0.0f)
{
	StartPiece();
	view.reset(FloatRect(0.0f, 0.0f, 1280.0f, 800.0f)); // Kameran alustus windowin mukaan.
	view.rotate(0.0f);
}

void GameScene::Draw(sf::RenderWindow &window)
{
	for (std::vector<RectangleShape>::iterator it = groundVector.begin(); it != groundVector.end(); it++)
		window.draw(*it); // Piirretään scenet järjestyksessä.

	window.draw(character.sprite);
	window.setView(view);
}

void GameScene::Update(float deltaTime, Event &events)
{
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		rectangle.setPosition((rectangle.getPosition() + sf::Vector2f(-5.0f, 0.0f)));
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		rectangle.setPosition((rectangle.getPosition() + sf::Vector2f(5.0f, 0.0f)));*/

	// Päivitetään jumala-luokkaa
	Gameboard::playerLocation = Vector2f(character.sprite.getGlobalBounds().left, character.sprite.getGlobalBounds().top);
	Gameboard::gameLocation = Vector2f(view.getCenter().x, view.getCenter().y);

	// Hahmon liike.
	character.sprite.setPosition(Vector2f((character.sprite.getPosition().x + character.GetSpeed()),
		character.sprite.getPosition().y));

	// Hahmon putoamisliike.
	if (!jumpCheck && !touchGround) 
	{
		character.sprite.setPosition(Vector2f((character.sprite.getPosition().x),
			character.sprite.getPosition().y + character.weight + jumpTicks * 0.5f));
	}

	// Pusketaan hahmoa ylös jos koskee maahan.
	for (std::vector<RectangleShape>::iterator it = groundVector.begin(); it != groundVector.end(); it++)
	{
		if ((*it).getGlobalBounds().intersects(character.sprite.getGlobalBounds())) 
		{
			character.sprite.setPosition(Vector2f((character.sprite.getPosition().x),
				character.sprite.getPosition().y - 1.0f));
			touchGround = true;
			jumpCheck = false;
			jumpTicks = 0.0f;
			jumpTimer = 0.0f;
		}
	}

	// Hyppäämislogiikka.
	if (Keyboard::isKeyPressed(Keyboard::Space) && !jumpCheck && touchGround)
	{
		jumpModifier = character.jumpPower;
		character.sprite.setPosition((character.sprite.getPosition() + Vector2f(character.jumpThrust, -3.0f - jumpModifier)));
		jumpCheck = true;
		touchGround = false;
		jumpTimer += deltaTime;
		jumpTicks++;
	}

	// Jos hahmo on hyppyanimaatiossa.
	if (jumpCheck) 
	{
		jumpModifier *= 1.05f;
		character.sprite.setPosition((character.sprite.getPosition() + Vector2f(character.jumpThrust, -3.0f - jumpModifier)));
		jumpTimer += deltaTime;
		jumpTicks++;
		if (jumpTimer >= (character.jumpFloat * 0.5f))
		{
			jumpCheck = false;
			jumpTimer = 0.0f;
		}
	}

	// ES pärisee
	if (RNG::Chance(50))
		view.setRotation((float)RNG::Random(1));
	else
		view.setRotation(0.0f - (float)RNG::Random(1));

	// Kameran scrollaus.
	view.setCenter(Vector2f(character.sprite.getGlobalBounds().left + 200.0f, view.getCenter().y));

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
	Capitalist capitalist;
	character = capitalist;
	character.sprite.setPosition(Vector2f(100.0f, 400.0f));

	RectangleShape tempGround;
	tempGround.setSize(Vector2f(screenSize.x, 50.0f)); // Alustetaan maaperä.
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