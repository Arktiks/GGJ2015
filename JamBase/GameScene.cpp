#include "GameScene.h"
#include <iostream>
#include "SFML\System\Vector2.hpp"
#include "SFML\Window\Keyboard.hpp"
#include "Base\RNG.h"
#include "Gameboard.h"
#include "Capitalist.h"
using namespace sf; 

GameScene::GameScene() : touchSurface(false), gravitation(1.2f), 
windowCheck(false), screenSize(Vector2f(1280.0f, 800.0f))
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
	for (std::vector<Platform>::iterator it = platformVector.begin(); it != platformVector.end(); it++)
		window.draw(it->sprite);
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
		character.sprite.getPosition().y + character.GetSpeedY()));

	// Hahmon putoamisliike.
	if (!touchSurface)
	{
		character.SetSpeedY(character.GetSpeedY() + character.gravity);
	}
	else
		character.SetSpeedY(0.f);

	// Pusketaan hahmoa ylös jos koskee platformiin.
	// Pusketaan hahmoa ylös jos koskee maahan.
	if (CheckPlatformCollision() || CheckGroundCollision())
		touchSurface = true;
	else
		touchSurface = false;
	
	// Hyppäämislogiikka.
	if (Keyboard::isKeyPressed(Keyboard::Space) && touchSurface)
	{
		character.Jump();
		touchSurface = false;
	}

	// ES pärisee
	// pärinää vahennetty
	else if (RNG::Chance(50));
	// view.setRotation(view.getRotation() + 1);
	//else
		//view.setRotation(0.0f - (float)RNG::Random(1));

	// Kameran scrollaus.
	view.setCenter(Vector2f(character.sprite.getGlobalBounds().left + 200.0f, view.getCenter().y));

	if ((int)view.getCenter().x % 500 == 0)
	{
		Piece1();
	}
	std::cout <<"X: "<< character.sprite.getPosition().x <<"Y: " << character.sprite.getPosition().y<<std::endl;
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

	PlatformSpawn();
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

	std::cout << character.sprite.getPosition().x << std::endl;
}

void GameScene::PlatformSpawn()
{
	for (int i = 0; i < 3; i++)
	{
		Platform tempPlatta = Platform(0, false);
		tempPlatta.SetTexture("JP");
		tempPlatta.sprite.setTextureRect(sf::IntRect(100, 33, 60, 17));
		tempPlatta.sprite.setPosition(500 + 200 * i, 500 + 100 * i);
		platformVector.push_back(tempPlatta);
	}
}
bool GameScene::CheckPlatformCollision()
{
	bool temp = false;
	for (std::vector<Platform>::iterator it = platformVector.begin(); it != platformVector.end(); it++)
	{
		if ((*it).sprite.getGlobalBounds().intersects(character.sprite.getGlobalBounds()))
		{
			character.sprite.setPosition(Vector2f((character.sprite.getPosition().x),
				(*it).sprite.getGlobalBounds().top - character.sprite.getGlobalBounds().height));

			temp = true;
		}
	}
	return temp;
}

bool GameScene::CheckGroundCollision()
{
	bool temp = false;
	for (std::vector<RectangleShape>::iterator it = groundVector.begin(); it != groundVector.end(); it++)
	{
		if ((*it).getGlobalBounds().intersects(character.sprite.getGlobalBounds()))
		{
			character.sprite.setPosition(Vector2f((character.sprite.getPosition().x),
				(*it).getGlobalBounds().top - character.sprite.getGlobalBounds().height));
			temp = true;
		}
	}
	return temp;
}