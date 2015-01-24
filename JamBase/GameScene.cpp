#include "GameScene.h"
#include <iostream>
#include "SFML\System\Vector2.hpp"
#include "SFML\Window\Keyboard.hpp"
#include "Base\RNG.h"
#include "Gameboard.h"
#include "Capitalist.h"
#include "WalkingEnemy.h"
#include "Rock.h"
using namespace sf; 

GameScene::GameScene() : touchSurface(false), gravitation(1.2f), 
windowCheck(false), screenSize(Vector2f(1280.0f, 800.0f))
{
	StartPiece();
	view.reset(FloatRect(0.0f, 0.0f, 1280.0f, 800.0f)); // Kameran alustus windowin mukaan.
	view.rotate(0.0f);
	PlatformSpawn();
}

void GameScene::Draw(sf::RenderWindow &window)
{
	for (std::vector<RectangleShape>::iterator it = groundVector.begin(); it != groundVector.end(); it++)
		window.draw(*it); // Piirret‰‰n scenet j‰rjestyksess‰.

	for (std::vector<Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); it++)
		window.draw(it->sprite);

	window.draw(character.sprite);
	window.setView(view);
	for (std::vector<Platform>::iterator it = platformVector.begin(); it != platformVector.end(); it++)
		window.draw(it->sprite);
}

void GameScene::Update(float deltaTime, Event &events)
{
	// P‰ivitet‰‰n jumala-luokkaa.
	Gameboard::playerLocation = Vector2f(character.sprite.getGlobalBounds().left, character.sprite.getGlobalBounds().top);
	Gameboard::gameLocation = Vector2f(view.getCenter().x, view.getCenter().y);

	// P‰ivitet‰‰n obstacle animaatiot.
	for (std::vector<Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); it++)
		it->UpdateSprite(deltaTime);

	// P‰ivitet‰‰n Obstaclen "eteneminen".
	for (std::vector<Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); it++)
		it->sprite.setPosition(Vector2f(it->sprite.getPosition().x - it->speed, it->sprite.getPosition().y));

	// Hahmon liike.
	character.sprite.setPosition(Vector2f((character.sprite.getPosition().x + character.GetSpeed()),
	character.sprite.getPosition().y + character.GetSpeedY()));

	// Hahmon putoamisliike.
	if (!touchSurface)
		character.SetSpeedY(character.GetSpeedY() + character.gravity);
	else
		character.SetSpeedY(0.f);

	PlatformUpdate();

	// Pusketaan hahmoa ylˆs jos koskee platformiin.
	// Pusketaan hahmoa ylˆs jos koskee maahan.
	if (CheckPlatformCollision() || CheckGroundCollision())
		touchSurface = true;
	else
		touchSurface = false;
	
	// Hypp‰‰mislogiikka.
	if (Keyboard::isKeyPressed(Keyboard::Space) && touchSurface)
	{
		character.Jump();
		touchSurface = false;
	}

	// Kameran scrollaus.
	view.setCenter(Vector2f(character.sprite.getGlobalBounds().left + 200.0f, view.getCenter().y));

	if ((int)view.getCenter().x % 500 == 0)
	{
		//Piece1();
		PlatformSpawn();
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

	/*WalkingEnemy tempEnemy;
	tempEnemy.sprite.setScale(0.3f, 0.3f);
	tempEnemy.sprite.setPosition(500.f, 500.0f);
	obstacles.push_back(tempEnemy);*/

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
	tempGround.setPosition(Vector2f(view.getCenter().x + 630.0f, screenSize.y - tempGround.getSize().y));
	groundVector.push_back(tempGround);

	CircleShape aurinko(10.0f, 30u);
	aurinko.setFillColor(Color::Magenta);
	aurinko.setPosition(Vector2f(view.getCenter().x, screenSize.y - 400.0f));
	//groundVector.push_back(aurinko);

	std::cout << character.sprite.getPosition().x << std::endl;
}

void GameScene::PlatformSpawn()
{
		int choice = RNG::Random(4);
		switch (choice)
		{
		case 0:
		{
			Platform tempPlatta1;
			tempPlatta1.SetTexture("JP");
			tempPlatta1.sprite.setColor(sf::Color::Cyan);
			tempPlatta1.sprite.setTextureRect(sf::IntRect(100, 33, 370, 40));
			tempPlatta1.sprite.setPosition(character.sprite.getPosition().x + 50 + 1280, 200);
			Platform tempPlatta2;
			tempPlatta2.SetTexture("JP");
			tempPlatta2.sprite.setColor(sf::Color::Cyan);
			tempPlatta2.sprite.setTextureRect(sf::IntRect(100, 33, 400, 40));
			tempPlatta2.sprite.setPosition(character.sprite.getPosition().x + 640 + 1280, 200);
			Platform tempPlatta3;
			tempPlatta3.SetTexture("JP");
			tempPlatta3.sprite.setColor(sf::Color::Cyan);
			tempPlatta3.sprite.setTextureRect(sf::IntRect(100, 33, 440, 40));
			tempPlatta3.sprite.setPosition(character.sprite.getPosition().x + 0 + 1280, 400);
			Platform tempPlatta4;
			tempPlatta4.SetTexture("JP");
			tempPlatta4.sprite.setColor(sf::Color::Cyan);
			tempPlatta4.sprite.setTextureRect(sf::IntRect(100, 33, 200, 40));
			tempPlatta4.sprite.setPosition(character.sprite.getPosition().x + 490 + 1280, 400);
			Platform tempPlatta5;
			tempPlatta5.SetTexture("JP");
			tempPlatta5.sprite.setColor(sf::Color::Cyan);
			tempPlatta5.sprite.setTextureRect(sf::IntRect(100, 33, 350, 40));
			tempPlatta5.sprite.setPosition(character.sprite.getPosition().x + 790 + 1280, 400);
			Platform tempPlatta6;
			tempPlatta6.SetTexture("JP");
			tempPlatta6.sprite.setColor(sf::Color::Cyan);
			tempPlatta6.sprite.setTextureRect(sf::IntRect(100, 33, 220, 40));
			tempPlatta6.sprite.setPosition(character.sprite.getPosition().x + 50 + 1280, 600);
			Platform tempPlatta7;
			tempPlatta7.SetTexture("JP");
			tempPlatta7.sprite.setColor(sf::Color::Cyan);
			tempPlatta7.sprite.setTextureRect(sf::IntRect(100, 33, 200, 40));
			tempPlatta7.sprite.setPosition(character.sprite.getPosition().x + 640 + 1280, 600);

			platformVector.push_back(tempPlatta1);
			platformVector.push_back(tempPlatta2);
			platformVector.push_back(tempPlatta3);
			platformVector.push_back(tempPlatta4);
			platformVector.push_back(tempPlatta5);
			platformVector.push_back(tempPlatta6);
			platformVector.push_back(tempPlatta7);
			break;
		}
		case 1:
		{
			if (RNG::Chance(50))
			{
				WalkingEnemy tempEnemy;
				tempEnemy.sprite.setScale(0.25f, 0.25f);
				tempEnemy.sprite.setPosition(character.sprite.getPosition().x + 2280.0f, 200.0f - tempEnemy.sprite.getGlobalBounds().height);
				obstacles.push_back(tempEnemy);
			}

			Platform tempPlatta1;
			tempPlatta1.SetTexture("JP");
			tempPlatta1.sprite.setColor(sf::Color::Cyan);
			tempPlatta1.sprite.setTextureRect(sf::IntRect(100, 33, 1000, 40));
			tempPlatta1.sprite.setPosition(character.sprite.getPosition().x + 50 + 1280, 200);
			Platform tempPlatta2;
			tempPlatta2.SetTexture("JP");
			tempPlatta2.sprite.setColor(sf::Color::Cyan);
			tempPlatta2.sprite.setTextureRect(sf::IntRect(100, 33, 100, 40));
			tempPlatta2.sprite.setPosition(character.sprite.getPosition().x + 100 + 1280, 600);
			Platform tempPlatta3;
			tempPlatta3.SetTexture("JP");
			tempPlatta3.sprite.setColor(sf::Color::Cyan);
			tempPlatta3.sprite.setTextureRect(sf::IntRect(100, 33, 100, 40));
			tempPlatta3.sprite.setPosition(character.sprite.getPosition().x + 300 + 1280, 500);
			Platform tempPlatta4;
			tempPlatta4.SetTexture("JP");
			tempPlatta4.sprite.setColor(sf::Color::Cyan);
			tempPlatta4.sprite.setTextureRect(sf::IntRect(100, 33, 200, 40));
			tempPlatta4.sprite.setPosition(character.sprite.getPosition().x + 500 + 1280, 600);
			Platform tempPlatta5;
			tempPlatta5.SetTexture("JP");
			tempPlatta5.sprite.setColor(sf::Color::Cyan);
			tempPlatta5.sprite.setTextureRect(sf::IntRect(100, 33, 100, 40));
			tempPlatta5.sprite.setPosition(character.sprite.getPosition().x + 800 + 1280, 500);
			Platform tempPlatta6;
			tempPlatta6.SetTexture("JP");
			tempPlatta6.sprite.setColor(sf::Color::Cyan);
			tempPlatta6.sprite.setTextureRect(sf::IntRect(100, 33, 100, 40));
			tempPlatta6.sprite.setPosition(character.sprite.getPosition().x + 1000 + 1280, 600);

			platformVector.push_back(tempPlatta1);
			platformVector.push_back(tempPlatta2);
			platformVector.push_back(tempPlatta3);
			platformVector.push_back(tempPlatta4);
			platformVector.push_back(tempPlatta5);
			platformVector.push_back(tempPlatta6);
			break;
		}
		case 2:
		{
			if (RNG::Chance(50))
			{
				Rock tempEnemy;
				tempEnemy.sprite.setScale(0.2, 0.2f);
				tempEnemy.sprite.setPosition(character.sprite.getPosition().x + 2280, 200.0f - tempEnemy.sprite.getGlobalBounds().height);
				obstacles.push_back(tempEnemy);
			}
			
			Platform tempPlatta1;
			tempPlatta1.SetTexture("JP");
			tempPlatta1.sprite.setColor(sf::Color::Cyan);
			tempPlatta1.sprite.setTextureRect(sf::IntRect(100, 33, 640, 40));
			tempPlatta1.sprite.setPosition(character.sprite.getPosition().x + 640 + 1280, 200);
			Platform tempPlatta2;
			tempPlatta2.SetTexture("JP");
			tempPlatta2.sprite.setColor(sf::Color::Cyan);
			tempPlatta2.sprite.setTextureRect(sf::IntRect(100, 33, 640, 40));
			tempPlatta2.sprite.setPosition(character.sprite.getPosition().x + 0 + 1280, 400);
			Platform tempPlatta3;
			tempPlatta3.SetTexture("JP");
			tempPlatta3.sprite.setColor(sf::Color::Cyan);
			tempPlatta3.sprite.setTextureRect(sf::IntRect(100, 33, 640, 40));
			tempPlatta3.sprite.setPosition(character.sprite.getPosition().x + 640 + 1280, 600);
		
			platformVector.push_back(tempPlatta1);
			platformVector.push_back(tempPlatta2);
			platformVector.push_back(tempPlatta3);
			break;
		}
		case 3:
		{
			Platform tempPlatta1;
			tempPlatta1.SetTexture("JP");
			tempPlatta1.sprite.setColor(sf::Color::Cyan);
			tempPlatta1.sprite.setTextureRect(sf::IntRect(100, 33, 300, 40));
			tempPlatta1.sprite.setPosition(character.sprite.getPosition().x + 0 + 1280, 400);
			Platform tempPlatta2;
			tempPlatta2.SetTexture("JP");
			tempPlatta2.sprite.setColor(sf::Color::Cyan);
			tempPlatta2.sprite.setTextureRect(sf::IntRect(100, 33, 100, 40));
			tempPlatta2.sprite.setPosition(character.sprite.getPosition().x + 500 + 1280, 400);
			Platform tempPlatta3;
			tempPlatta3.SetTexture("JP");
			tempPlatta3.sprite.setColor(sf::Color::Cyan);
			tempPlatta3.sprite.setTextureRect(sf::IntRect(100, 33, 200, 40));
			tempPlatta3.sprite.setPosition(character.sprite.getPosition().x + 690 + 1280, 400);
			Platform tempPlatta4;
			tempPlatta4.SetTexture("JP");
			tempPlatta4.sprite.setColor(sf::Color::Cyan);
			tempPlatta4.sprite.setTextureRect(sf::IntRect(100, 33, 300, 40));
			tempPlatta4.sprite.setPosition(character.sprite.getPosition().x + 890 + 1280, 400);
			Platform tempPlatta5;
			tempPlatta5.SetTexture("JP");
			tempPlatta5.sprite.setColor(sf::Color::Cyan);
			tempPlatta5.sprite.setTextureRect(sf::IntRect(100, 33, 500, 40));
			tempPlatta5.sprite.setPosition(character.sprite.getPosition().x + 340 + 1280, 600);

			platformVector.push_back(tempPlatta1);
			platformVector.push_back(tempPlatta2);
			platformVector.push_back(tempPlatta3);
			platformVector.push_back(tempPlatta4);
			platformVector.push_back(tempPlatta5);
			break;
		}
		case 4:
		{
			Platform tempPlatta1;
			tempPlatta1.SetTexture("JP");
			tempPlatta1.sprite.setColor(sf::Color::Cyan);
			tempPlatta1.sprite.setTextureRect(sf::IntRect(100, 33, 200, 40));
			tempPlatta1.sprite.setPosition(character.sprite.getPosition().x + 50 + 1280, 200);
			Platform tempPlatta2;
			tempPlatta2.SetTexture("JP");
			tempPlatta2.sprite.setColor(sf::Color::Cyan);
			tempPlatta2.sprite.setTextureRect(sf::IntRect(100, 33, 300, 40));
			tempPlatta2.sprite.setPosition(character.sprite.getPosition().x + 300 + 1280, 400);
			Platform tempPlatta3;
			tempPlatta3.SetTexture("JP");
			tempPlatta3.sprite.setColor(sf::Color::Cyan);
			tempPlatta3.sprite.setTextureRect(sf::IntRect(100, 33, 300, 40));
			tempPlatta3.sprite.setPosition(character.sprite.getPosition().x + 940 + 1280, 400);
			Platform tempPlatta4;
			tempPlatta4.SetTexture("JP");
			tempPlatta4.sprite.setColor(sf::Color::Cyan);
			tempPlatta4.sprite.setTextureRect(sf::IntRect(100, 33, 200, 40));
			tempPlatta4.sprite.setPosition(character.sprite.getPosition().x + 50 + 1280, 600);
			Platform tempPlatta5;
			tempPlatta5.SetTexture("JP");
			tempPlatta5.sprite.setColor(sf::Color::Cyan);
			tempPlatta5.sprite.setTextureRect(sf::IntRect(100, 33, 200, 40));
			tempPlatta5.sprite.setPosition(character.sprite.getPosition().x + 640 + 1280, 600);

			platformVector.push_back(tempPlatta1);
			platformVector.push_back(tempPlatta2);
			platformVector.push_back(tempPlatta3);
			platformVector.push_back(tempPlatta4);
			platformVector.push_back(tempPlatta5);
		}
		case 5:
		{




			break;
		}
		case 6:
		{




			break;
		}
		case 7:
		{




			break;
		}
	}

}

bool GameScene::CheckPlatformCollision()
{
	bool temp = false;
	for (std::vector<Platform>::iterator it = platformVector.begin(); it != platformVector.end(); it++)
	{
		if ((*it).sprite.getGlobalBounds().contains(sf::Vector2f(character.sprite.getPosition().x, character.sprite.getPosition().y + character.sprite.getGlobalBounds().height))
			|| (*it).sprite.getGlobalBounds().contains(sf::Vector2f(character.sprite.getPosition().x + character.sprite.getGlobalBounds().width, character.sprite.getPosition().y + character.sprite.getGlobalBounds().height))
			&& !(character.GetSpeedY() < 0.f))
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
		if ((*it).getGlobalBounds().contains(sf::Vector2f(character.sprite.getPosition().x, character.sprite.getPosition().y + character.sprite.getGlobalBounds().height))
			|| (*it).getGlobalBounds().contains(sf::Vector2f(character.sprite.getPosition().x + character.sprite.getGlobalBounds().width, character.sprite.getPosition().y + character.sprite.getGlobalBounds().height))
			&& !(character.GetSpeedY() < 0.f))
		{
			character.sprite.setPosition(Vector2f((character.sprite.getPosition().x),
				(*it).getGlobalBounds().top - character.sprite.getGlobalBounds().height));
			temp = true;
		}
	}
	return temp;
}

void GameScene::PlatformUpdate()
{
	for (std::vector<Platform>::iterator it = platformVector.begin(); it != platformVector.end();)
	{
		if (it->sprite.getPosition().x <= character.sprite.getPosition().x - 1400)
		{
			std::cout << "siit‰s sait" << std::endl;
			it = platformVector.erase(it);
		}
		else
			it++;
			
	}
}