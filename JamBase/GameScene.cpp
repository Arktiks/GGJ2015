#include "GameScene.h"
#include <iostream>
#include "SFML\System\Vector2.hpp"
#include "SFML\Window\Keyboard.hpp"
#include "Base\RNG.h"
#include "R.h"
#include "Gameboard.h"
#include "Capitalist.h"
#include "WalkingEnemy.h"
#include "WalkingEnemy2.h"
#include "Rock.h"
using namespace sf; 

GameScene::GameScene() : touchSurface(false), protectionTimer(0.0f), startCheck(false),
windowCheck(false), screenSize(Vector2f(1280.0f, 800.0f)), zombieSpawner(0.0f), damageProtection(false)
{
	view.reset(FloatRect(0.0f, 0.0f, 1280.0f, 800.0f)); // Kameran alustus windowin mukaan.
	view.rotate(0.0f);
	Gameboard::loadSounds();
	PlatformSpawn();
	StartPiece();
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

	character.UpdateSprite(deltaTime);

	// P‰ivitet‰‰n Obstaclen "eteneminen".
	for (std::vector<Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); it++)
	{
		it->sprite.setPosition(Vector2f(it->sprite.getPosition().x - it->speed, it->sprite.getPosition().y));
		if (it->sprite.getGlobalBounds().intersects(character.sprite.getGlobalBounds())
			&& !damageProtection)
		{
			Gameboard::moneyAmount--;
			damageProtection = true;
		}
	}

	if (damageProtection)
	{
		//character.sprite.setColor(Color::Color(RNG::Between(50, 200), RNG::Between(50, 200), RNG::Between(50, 200), 200));
		protectionTimer += deltaTime;
		if (protectionTimer >= 1.0f)
		{
			//character.sprite.setColor(Color::Black);
			damageProtection = false;
		}
	}

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
		PlatformSpawn();

	zombieSpawner += deltaTime;
	if (zombieSpawner >= 0.3f)
	{
		WalkingEnemy2 tempEnemy;
		tempEnemy.sprite.setScale(2.0f, 2.0f);
		tempEnemy.sprite.setPosition(character.sprite.getGlobalBounds().left + 1300.0f, 730.0f);
		obstacles.push_back(tempEnemy);
		zombieSpawner = 0.0f;
		startCheck = true;
	}

	//if (Gameboard::moneyAmount == 0 || !view.getViewport().contains(character.sprite.getPosition()))
		//Gameboard::characterIsDead = true;

	if (Gameboard::moneyAmount == 0 || character.sprite.getPosition().y >= screenSize.y)
		Gameboard::characterIsDead = true;
}

void GameScene::StartPiece()
{
	Capitalist capitalist;
	character = capitalist;
	character.createSounds();
	character.sprite.setPosition(Vector2f(100.0f, 400.0f));

	RectangleShape tempGround;
	tempGround.setSize(Vector2f(screenSize.x * 2, 30.0f)); // Alustetaan maaper‰.
	tempGround.setPosition(-300, (screenSize.y - 25));
	tempGround.setTexture(R::LoadTexture("taso2"));
	groundVector.push_back(tempGround);
}

void GameScene::Piece1()
{
	RectangleShape tempGround(Vector2f(1280.0f, 50.0f));
	tempGround.setFillColor(Color::Blue);
	tempGround.setPosition(Vector2f(view.getCenter().x + 630.0f, screenSize.y - tempGround.getSize().y));
	groundVector.push_back(tempGround);
}

void GameScene::PlatformSpawn()
{
	int choice = RNG::Random(2);
	switch (choice)
	{
	case 0:
	{
		Platform tempPlat1;
		tempPlat1.SetTexture("taso2");
		tempPlat1.sprite.setTextureRect(sf::IntRect(0, 0, 300, 25));
		tempPlat1.sprite.setPosition(character.sprite.getPosition().x + 0 + 1280, 240);

		Platform tempPlat2;
		tempPlat2.SetTexture("taso2");
		tempPlat1.sprite.setTextureRect(sf::IntRect(0, 0, 448, 25));
		tempPlat2.sprite.setPosition(character.sprite.getPosition().x + 740 + 1280, 280);

		Platform tempPlat3;
		tempPlat3.SetTexture("taso2");
		tempPlat1.sprite.setTextureRect(sf::IntRect(0, 0, 140, 25));
		tempPlat3.sprite.setPosition(character.sprite.getPosition().x - 200 + 1280, 400);

		if (RNG::Chance(20))
		{
			Rock tempEnemy;
			tempEnemy.sprite.setPosition(tempPlat3.sprite.getGlobalBounds().left + 300, tempPlat3.sprite.getGlobalBounds().top - tempEnemy.sprite.getGlobalBounds().height + 10);
			obstacles.push_back(tempEnemy);
		}

		Platform tempPlat4;
		tempPlat4.SetTexture("taso2");
		tempPlat1.sprite.setTextureRect(sf::IntRect(0, 0, 440, 25));
		tempPlat4.sprite.setPosition(character.sprite.getPosition().x + 440 + 1280, 400);

		Platform tempPlat5;
		tempPlat5.SetTexture("taso2");
		tempPlat5.sprite.setTextureRect(sf::IntRect(0, 0, 340, 25));
		tempPlat5.sprite.setPosition(character.sprite.getPosition().x + 0 + 1280, 600);

		if (RNG::Chance(10))
		{
			WalkingEnemy tempEnemy;
			tempEnemy.sprite.setPosition(tempPlat5.sprite.getGlobalBounds().left + 1248, tempPlat5.sprite.getGlobalBounds().top - tempEnemy.sprite.getGlobalBounds().height + 4);
			obstacles.push_back(tempEnemy);
		}

		Platform tempPlat6;
		tempPlat6.SetTexture("taso2");
		tempPlat6.sprite.setTextureRect(sf::IntRect(0, 0, 290, 25));
		tempPlat6.sprite.setPosition(character.sprite.getPosition().x + 640 + 1280, 600);

		Platform tempPlat7;
		tempPlat7.SetTexture("taso2");
		tempPlat7.sprite.setTextureRect(sf::IntRect(0, 0, 150, 25));
		tempPlat7.sprite.setPosition(character.sprite.getPosition().x + 1030 + 1280, 600);

		platformVector.push_back(tempPlat1);
		platformVector.push_back(tempPlat2);
		platformVector.push_back(tempPlat3);
		platformVector.push_back(tempPlat4);
		platformVector.push_back(tempPlat5);
		platformVector.push_back(tempPlat6);
		platformVector.push_back(tempPlat7);
	}
	case 1:
	{
		Platform tempPlat1;
		tempPlat1.SetTexture("taso2");
		tempPlat1.sprite.setTextureRect(sf::IntRect(0, 0, 400, 25));
		tempPlat1.sprite.setPosition(character.sprite.getPosition().x + 0 + 1280, 240);

		Platform tempPlat2;
		tempPlat2.SetTexture("taso2");
		tempPlat1.sprite.setTextureRect(sf::IntRect(0, 0, 448, 25));
		tempPlat2.sprite.setPosition(character.sprite.getPosition().x + 800 + 1280, 300);

		Platform tempPlat3;
		tempPlat3.SetTexture("taso2");
		tempPlat1.sprite.setTextureRect(sf::IntRect(0, 0, 448, 25));
		tempPlat3.sprite.setPosition(character.sprite.getPosition().x + 200 + 1280, 500);

		if (RNG::Chance(20))
		{
			WalkingEnemy tempEnemy;
			tempEnemy.sprite.setPosition(tempPlat3.sprite.getGlobalBounds().left + 448, tempPlat3.sprite.getGlobalBounds().top - tempEnemy.sprite.getGlobalBounds().height + 4);
			obstacles.push_back(tempEnemy);
		}

		Platform tempPlat4;
		tempPlat4.SetTexture("taso2");
		tempPlat1.sprite.setTextureRect(sf::IntRect(0, 0, 200, 25));
		tempPlat4.sprite.setPosition(character.sprite.getPosition().x + 0 + 1280, 580);

		Platform tempPlat5;
		tempPlat5.SetTexture("taso2");
		tempPlat5.sprite.setTextureRect(sf::IntRect(0, 0, 400, 25));
		tempPlat5.sprite.setPosition(character.sprite.getPosition().x + 800 + 1280, 600);

		platformVector.push_back(tempPlat1);
		platformVector.push_back(tempPlat2);
		platformVector.push_back(tempPlat3);
		platformVector.push_back(tempPlat4);
		platformVector.push_back(tempPlat5);
		break;
	}
	case 2:
	{
		Platform tempPlat1;
		tempPlat1.SetTexture("taso2");
		tempPlat1.sprite.setTextureRect(sf::IntRect(0, 0, 448, 25));
		tempPlat1.sprite.setPosition(character.sprite.getPosition().x + 0 + 1280, 240);

		Platform tempPlat2;
		tempPlat2.SetTexture("taso2");
		tempPlat1.sprite.setTextureRect(sf::IntRect(0, 0, 200, 25));
		tempPlat2.sprite.setPosition(character.sprite.getPosition().x + 100 + 1280, 400);

		Platform tempPlat3;
		tempPlat3.SetTexture("taso2");
		tempPlat1.sprite.setTextureRect(sf::IntRect(0, 0, 448, 25));
		tempPlat3.sprite.setPosition(character.sprite.getPosition().x + 650 + 1280, 400);

		if (RNG::Chance(20))
		{
			WalkingEnemy tempEnemy;
			tempEnemy.sprite.setPosition(tempPlat3.sprite.getGlobalBounds().left + 648, tempPlat3.sprite.getGlobalBounds().top - tempEnemy.sprite.getGlobalBounds().height + 4);
			obstacles.push_back(tempEnemy);
		}

		Platform tempPlat4;
		tempPlat4.SetTexture("taso2");
		tempPlat1.sprite.setTextureRect(sf::IntRect(0, 0, 400, 25));
		tempPlat4.sprite.setPosition(character.sprite.getPosition().x - 100 + 1280, 300);

		Platform tempPlat5;
		tempPlat5.SetTexture("taso2");
		tempPlat5.sprite.setTextureRect(sf::IntRect(0, 0, 200, 25));
		tempPlat5.sprite.setPosition(character.sprite.getPosition().x + 500 + 1280, 480);

		Platform tempPlat6;
		tempPlat6.SetTexture("taso2");
		tempPlat6.sprite.setTextureRect(sf::IntRect(0, 0, 448, 25));
		tempPlat6.sprite.setPosition(character.sprite.getPosition().x + 1000 + 1280, 150);

		if (RNG::Chance(10))
		{
			Rock tempEnemy;
			tempEnemy.sprite.setPosition(tempPlat6.sprite.getGlobalBounds().left + 200, tempPlat6.sprite.getGlobalBounds().top - tempEnemy.sprite.getGlobalBounds().height + 10);
			obstacles.push_back(tempEnemy);
		}

		platformVector.push_back(tempPlat1);
		platformVector.push_back(tempPlat2);
		platformVector.push_back(tempPlat3);
		platformVector.push_back(tempPlat4);
		platformVector.push_back(tempPlat5);
		platformVector.push_back(tempPlat6);
		break;
	}
	default:
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

void GameScene::UpdateProjectiles()
{
	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i].type == BULLET)
		{
			projectiles[i].sprite.setPosition(projectiles[i].sprite.getPosition().x + 2,
				projectiles[i].sprite.getPosition().y);
		}
		for (int j = 0; j < obstacles.size(); j++)
		{
			if (obstacles[j].sprite.getGlobalBounds().intersects(projectiles[i].sprite.getGlobalBounds()));
			{
				obstacles[j].isDead = true;
				projectiles[i].isDead = true;
			}
		}

		if (projectiles[i].sprite.getPosition().x > character.sprite.getPosition().x + 1200)
		{
			//delete
		}

	}
}