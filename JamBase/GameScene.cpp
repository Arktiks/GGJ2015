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
#include "R.h"
using namespace sf; 


GameScene::GameScene() : touchSurface(false), protectionTimer(0.0f), startCheck(false),
windowCheck(false), screenSize(Vector2f(1280.0f, 800.0f)), zombieSpawner(0.0f), damageProtection(false)
{
	view.reset(FloatRect(0.0f, 0.0f, 1280.0f, 800.0f)); // Kameran alustus windowin mukaan.
	view.rotate(0.0f);
	Gameboard::loadSounds();
	PlatformSpawn();
	StartPiece();
	gunSprite.setTexture(*R::LoadTexture("cannon"));
	gunSprite.setScale(0.9f, 0.9f);

}

void GameScene::Draw(sf::RenderWindow &window)
{
	for (std::vector<RectangleShape>::iterator it = groundVector.begin(); it != groundVector.end(); it++)
		window.draw(*it); // Piirretään scenet järjestyksessä.

	for (std::vector<Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); it++)
		window.draw(it->sprite);

	window.draw(character.sprite);
	if (Gameboard::weapon == CANNON && Gameboard::chargeAmount > 0)
	{
		gunSprite.setRotation(20);
		gunSprite.setPosition(character.sprite.getPosition().x -RNG::Between(10,15), character.sprite.getPosition().y -RNG::Between(25,20));
		window.draw(gunSprite);
	}
	window.setView(view);
	for (std::vector<Platform>::iterator it = platformVector.begin(); it != platformVector.end(); it++)
		window.draw(it->sprite);
	for (size_t i = 0; i < projectiles.size(); i++)
	{
		
		if (projectiles[i].type == BLADE)
		{
			projectiles[i].sprite.rotate(8);
		}
		if (projectiles[i].type == BOMERANG)
		{
			projectiles[i].sprite.rotate(10);
		}
		window.draw(projectiles[i].sprite);
	}
	for (int i = 0; i < items.size(); i++)
	{
		window.draw(items[i].sprite);
	}
}

void GameScene::Update(float deltaTime, Event &events)
{
	// Päivitetään jumala-luokkaa.
	Gameboard::playerLocation = Vector2f(character.sprite.getGlobalBounds().left, character.sprite.getGlobalBounds().top);
	Gameboard::gameLocation = Vector2f(view.getCenter().x, view.getCenter().y);

	// Päivitetään obstacle animaatiot.
	for (std::vector<Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); it++)
		it->UpdateSprite(deltaTime);

	character.UpdateSprite(deltaTime);

	// Päivitetään Obstaclen "eteneminen".
	for (std::vector<Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); it++)
	{
		it->speedY = 7 ;
		it->sprite.setPosition(Vector2f(it->sprite.getPosition().x - it->speed, it->sprite.getPosition().y + it->speedY));
		if (it->sprite.getGlobalBounds().intersects(character.sprite.getGlobalBounds())
			&& !damageProtection)
		{
			if (Gameboard::weapon != FIRE)
			{
				Gameboard::moneyAmount--;
				damageProtection = true;
			}
			else
			{
				it->isDead = true;
				Gameboard::soundMaster.PlaySound("flameBurst");
				Gameboard::moneyAmount++;

			}
		}

		bool temp = false;
		for (std::vector<Platform>::iterator atj = platformVector.begin(); atj != platformVector.end(); atj++)
		{
			if ((*atj).sprite.getGlobalBounds().contains(sf::Vector2f(it->sprite.getPosition().x, it->sprite.getPosition().y + it->sprite.getGlobalBounds().height))
				|| (*atj).sprite.getGlobalBounds().contains(sf::Vector2f(it->sprite.getPosition().x + it->sprite.getGlobalBounds().width, it->sprite.getPosition().y + it->sprite.getGlobalBounds().height))
				&& !(it->speedY < 0.f))
			{
				it->sprite.setPosition(Vector2f((it->sprite.getPosition().x),
					(*atj).sprite.getGlobalBounds().top - it->sprite.getGlobalBounds().height));
				temp = true;
			}
		}



		if (it->sprite.getPosition().x < Gameboard::playerLocation.x - 1000)
		{
			it->isDead = true;
		}
		if (it->sprite.getPosition().y > 1000)
		{
			it->isDead = true;
		}
	}
	// Päivitetään itemit
	for (int i = 0; i < items.size(); i++)
	{
		if (character.sprite.getGlobalBounds().intersects(items[i].sprite.getGlobalBounds()))
		{
			Gameboard::soundMaster.PlaySound("itemPickup");
			items[i].isDead = true;
			Gameboard::chargeAmount = 5;
			
			if (items[i].item == ITEMSWORD)
			{
				Gameboard::weapon = SWORD;
			}
			else if(items[i].item == ITEMCANNON)
			{
				Gameboard::weapon = CANNON;
			}
			else if (items[i].item == ITEMBOOMERANG)
			{
				Gameboard::weapon = BOMERANG;
			}
			else if (items[i].item == ITEMFIRE)
			{
				Gameboard::weapon = FIRE;
			}
		}
	}


	if (damageProtection)
	{
		protectionTimer += deltaTime;
		if (protectionTimer >= 1.0f)
			damageProtection = false;
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

	// Pusketaan hahmoa ylös jos koskee platformiin.
	// Pusketaan hahmoa ylös jos koskee maahan.
	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		Gameboard::dropDownTimer = 0;
	}
	if (Gameboard::dropDownTimer < 0.1)
	{
		touchSurface = false;
	}
	else
	{
		if (CheckPlatformCollision() || CheckGroundCollision())
			touchSurface = true;
		else
			touchSurface = false;
	}
	// Hyppäämislogiikka.
	if (Keyboard::isKeyPressed(Keyboard::Space) && touchSurface)
	{
		character.Jump();
		touchSurface = false;
	}
	if (Keyboard::isKeyPressed(Keyboard::Z) && Gameboard::chargeAmount > 0 && Gameboard::weaponTimer > 1.0f)
	{
		Gameboard::weaponTimer = 0;
		Gameboard::chargeAmount--;
		if (Gameboard::weapon == CANNON)
		{
			Gameboard::soundMaster.PlaySound("cannon");
			for (int i = 0; i < 10; i++)
			{
				Projectile projectile(BULLET);
				projectile.sprite.setPosition(character.sprite.getGlobalBounds().left, character.sprite.getGlobalBounds().top);
				projectiles.push_back(projectile);
			}
		}
		else if (Gameboard::weapon == SWORD)
		{
			Projectile projectile(BLADE);
			if (obstacles.size() == 0)
			{
				//Do not push on vector
				Gameboard::soundMaster.PlaySound("magic1");
			}
			else
			{
				bladeTargetObstacle = &obstacles[obstacles.size() - 1];

				projectile.sprite.setPosition(character.sprite.getGlobalBounds().left, character.sprite.getGlobalBounds().top);
				projectiles.push_back(projectile);
			}

		}
		else if (Gameboard::weapon == BOMERANG)
		{
			Gameboard::swordTimer = 0;
			Projectile projectile(BOOMERANG);
			projectile.sprite.setPosition(character.sprite.getGlobalBounds().left, character.sprite.getGlobalBounds().top);
			projectiles.push_back(projectile);
			Gameboard::soundMaster.FindSound("magicFly")->setPitch(0.8);
			Gameboard::soundMaster.FindSound("magicFly")->setVolume(50);
			Gameboard::soundMaster.PlaySound("magicFly");
		}
	}

	// Kameran scrollaus.
	view.setCenter(Vector2f(character.sprite.getGlobalBounds().left + 200.0f, view.getCenter().y));

	if ((int)view.getCenter().x % 900 == 0)
		PlatformSpawn();

	zombieSpawner += deltaTime;
	
	if (RNG::Chance(zombieSpawner*8))
	{
		WalkingEnemy2 tempEnemy;
		tempEnemy.sprite.setScale(2.0f, 2.0f);
		tempEnemy.sprite.setPosition(character.sprite.getGlobalBounds().left + 1300.0f, RNG::Between(0,400));
		obstacles.push_back(tempEnemy);
		zombieSpawner = 0.0f;
		startCheck = true;
	}


	UpdateProjectiles();
	Gameboard::dropDownTimer += deltaTime;
	Gameboard::weaponTimer += deltaTime;
	Gameboard::swordTimer += deltaTime;
	Gameboard::textTimer += deltaTime;

	if (Gameboard::moneyAmount == 0 || character.sprite.getPosition().y >= screenSize.y)
		Gameboard::characterIsDead = true;
	DeleteDead();

}

void GameScene::StartPiece()
{
	Capitalist capitalist;
	character = capitalist;
	character.createSounds();
	character.sprite.setPosition(Vector2f(100.0f, 400.0f));

	RectangleShape tempGround;
	tempGround.setSize(Vector2f(screenSize.x * 2, 30.0f)); // Alustetaan maaperä.
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
		Platform ground;
		ground.SetTexture("taso2");
		ground.sprite.setTextureRect(sf::IntRect(0, 0, screenSize.x, 50));
		ground.sprite.setPosition(character.sprite.getPosition().x + 0 + 1280, screenSize.y - 50);

		Platform tempPlat1;
		tempPlat1.SetTexture("taso2");
		tempPlat1.sprite.setTextureRect(sf::IntRect(0, 0, 300, 50));
		tempPlat1.sprite.setPosition(character.sprite.getPosition().x + 0 + 1280, 240);

		Platform tempPlat2;
		tempPlat2.SetTexture("taso2");
		tempPlat1.sprite.setTextureRect(sf::IntRect(0, 0, 448, 50));
		tempPlat2.sprite.setPosition(character.sprite.getPosition().x + 740 + 1280, 280);

		Platform tempPlat3;
		tempPlat3.SetTexture("taso2");
		tempPlat1.sprite.setTextureRect(sf::IntRect(0, 0, 140, 50));
		tempPlat3.sprite.setPosition(character.sprite.getPosition().x - 200 + 1280, 500);

		if (RNG::Chance(20))
		{
			Rock tempEnemy;
			tempEnemy.sprite.setPosition(tempPlat3.sprite.getGlobalBounds().left + 300, tempPlat3.sprite.getGlobalBounds().top - tempEnemy.sprite.getGlobalBounds().height + 10);
			obstacles.push_back(tempEnemy);
		}

		Platform tempPlat4;
		tempPlat4.SetTexture("taso2");
		tempPlat1.sprite.setTextureRect(sf::IntRect(0, 0, 440, 50));
		tempPlat4.sprite.setPosition(character.sprite.getPosition().x + 440 + 1280, 400);

		Platform tempPlat5;
		tempPlat5.SetTexture("taso2");
		tempPlat5.sprite.setTextureRect(sf::IntRect(0, 0, 340, 50));
		tempPlat5.sprite.setPosition(character.sprite.getPosition().x + 0 + 1280, 600);

		if (RNG::Chance(10))
		{
			WalkingEnemy tempEnemy;
			tempEnemy.sprite.setPosition(tempPlat5.sprite.getGlobalBounds().left + 1248, tempPlat5.sprite.getGlobalBounds().top - tempEnemy.sprite.getGlobalBounds().height + 4);
			obstacles.push_back(tempEnemy);
		}
		if (RNG::Chance(30))
		{
			int result = RNG::Random(3);
			if (result == 0)
			{
				Item item(ITEMCANNON);
				item.sprite.setPosition(Gameboard::playerLocation.x + 700, Gameboard::playerLocation.y + RNG::Between(-200, 200));
				items.push_back(item);
			}
			else if (result == 1)
			{
				Item item(ITEMSWORD);
				item.sprite.setPosition(Gameboard::playerLocation.x + 700, Gameboard::playerLocation.y + RNG::Between(-200, 200));
				items.push_back(item);
			}
			else if (result == 2)
			{
				Item item(ITEMBOOMERANG);
				item.sprite.setPosition(Gameboard::playerLocation.x + 700, Gameboard::playerLocation.y + RNG::Between(-200, 200));
				items.push_back(item);
			}
			else if (result == 3)
			{
				Item item(ITEMFIRE);
				item.sprite.setPosition(Gameboard::playerLocation.x + 700, Gameboard::playerLocation.y + RNG::Between(-200, 200));
				items.push_back(item);
			}
	
		}

		Platform tempPlat6;
		tempPlat6.SetTexture("taso2");
		tempPlat6.sprite.setTextureRect(sf::IntRect(0, 0, 290, 50));
		tempPlat6.sprite.setPosition(character.sprite.getPosition().x + 640 + 1280, 600);

		Platform tempPlat7;
		tempPlat7.SetTexture("taso2");
		tempPlat7.sprite.setTextureRect(sf::IntRect(0, 0, 150, 50));
		tempPlat7.sprite.setPosition(character.sprite.getPosition().x + 1030 + 1280, 600);

		platformVector.push_back(ground);
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
		tempPlat1.sprite.setTextureRect(sf::IntRect(0, 0, 400, 50));
		tempPlat1.sprite.setPosition(character.sprite.getPosition().x + 0 + 1280, 240);

		Platform tempPlat2;
		tempPlat2.SetTexture("taso2");
		tempPlat1.sprite.setTextureRect(sf::IntRect(0, 0, 448, 50));
		tempPlat2.sprite.setPosition(character.sprite.getPosition().x + 800 + 1280, 300);

		Platform tempPlat3;
		tempPlat3.SetTexture("taso2");
		tempPlat1.sprite.setTextureRect(sf::IntRect(0, 0, 448, 50));
		tempPlat3.sprite.setPosition(character.sprite.getPosition().x + 200 + 1280, 500);

		if (RNG::Chance(20))
		{
			WalkingEnemy tempEnemy;
			tempEnemy.sprite.setPosition(tempPlat3.sprite.getGlobalBounds().left + 448, tempPlat3.sprite.getGlobalBounds().top - tempEnemy.sprite.getGlobalBounds().height + 4);
			obstacles.push_back(tempEnemy);
		}

		Platform tempPlat4;
		tempPlat4.SetTexture("taso2");
		tempPlat1.sprite.setTextureRect(sf::IntRect(0, 0, 200, 50));
		tempPlat4.sprite.setPosition(character.sprite.getPosition().x + 0 + 1280, 580);

		Platform tempPlat5;
		tempPlat5.SetTexture("taso2");
		tempPlat5.sprite.setTextureRect(sf::IntRect(0, 0, 400, 50));
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
		Platform ground;
		ground.SetTexture("taso2");
		ground.sprite.setTextureRect(sf::IntRect(0, 0, screenSize.x, 50));
		ground.sprite.setPosition(character.sprite.getPosition().x + 0 + 1280, screenSize.y/2 - 50);

		Platform tempPlat1;
		tempPlat1.SetTexture("taso2");
		tempPlat1.sprite.setTextureRect(sf::IntRect(0, 0, 448, 50));
		tempPlat1.sprite.setPosition(character.sprite.getPosition().x + 0 + 1280, 240);

		Platform tempPlat2;
		tempPlat2.SetTexture("taso2");
		tempPlat1.sprite.setTextureRect(sf::IntRect(0, 0, 200, 50));
		tempPlat2.sprite.setPosition(character.sprite.getPosition().x + 100 + 1280, 400);

		Platform tempPlat3;
		tempPlat3.SetTexture("taso2");
		tempPlat1.sprite.setTextureRect(sf::IntRect(0, 0, 448, 50));
		tempPlat3.sprite.setPosition(character.sprite.getPosition().x + 650 + 1280, 400);

		if (RNG::Chance(20))
		{
			WalkingEnemy tempEnemy;
			tempEnemy.sprite.setPosition(tempPlat3.sprite.getGlobalBounds().left + 648, tempPlat3.sprite.getGlobalBounds().top - tempEnemy.sprite.getGlobalBounds().height + 4);
			obstacles.push_back(tempEnemy);
		}

		Platform tempPlat4;
		tempPlat4.SetTexture("taso2");
		tempPlat1.sprite.setTextureRect(sf::IntRect(0, 0, 400, 50));
		tempPlat4.sprite.setPosition(character.sprite.getPosition().x - 100 + 1280, 300);

		Platform tempPlat5;
		tempPlat5.SetTexture("taso2");
		tempPlat5.sprite.setTextureRect(sf::IntRect(0, 0, 200,50));
		tempPlat5.sprite.setPosition(character.sprite.getPosition().x + 500 + 1280, 480);

		Platform tempPlat6;
		tempPlat6.SetTexture("taso2");
		tempPlat6.sprite.setTextureRect(sf::IntRect(0, 0, 448, 50));
		tempPlat6.sprite.setPosition(character.sprite.getPosition().x + 1000 + 1280, 150);

		if (RNG::Chance(10))
		{
			Rock tempEnemy;
			tempEnemy.sprite.setPosition(tempPlat6.sprite.getGlobalBounds().left + 200, tempPlat6.sprite.getGlobalBounds().top - tempEnemy.sprite.getGlobalBounds().height + 10);
			obstacles.push_back(tempEnemy);
		}

		platformVector.push_back(ground);
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
		if (it->sprite.getPosition().x <= character.sprite.getPosition().x - 3000)
		{
			it = platformVector.erase(it);
		}
		else
			it++;	
	}
}

void GameScene::UpdateProjectiles()
{
	for (size_t i = 0; i < projectiles.size(); i++)
	{
		projectiles[i].Update();
		projectiles[i].sprite.setPosition(projectiles[i].sprite.getPosition().x + projectiles[i].speedX,
			projectiles[i].sprite.getPosition().y + projectiles[i].speedY);
		if (projectiles[i].type == BOMERANG)
		{
			for (size_t j = 0; j < obstacles.size(); j++)
			{
				if (obstacles[j].sprite.getGlobalBounds().intersects(projectiles[i].sprite.getGlobalBounds()))
				{
					obstacles[j].speed = obstacles[j].speed + float(RNG::Between(-200, 200))/200 * projectiles[i].speedX/2;
					obstacles[j].speedY = obstacles[j].speedY + float(RNG::Between(-200, 200))/200 * projectiles[i].speedY/2;
					obstacles[j].HP -= 1;
				}
				if (character.sprite.getGlobalBounds().intersects(projectiles[i].sprite.getGlobalBounds()) && Gameboard::swordTimer > 1)
				{
					projectiles[i].isDead = true;
				}
			}
		}
		if (projectiles[i].type == BULLET)
		{
			projectiles[i].sprite.setPosition(projectiles[i].sprite.getPosition().x + projectiles[i].speedX,
				projectiles[i].sprite.getPosition().y+projectiles[i].speedY);
		
			for (size_t j = 0; j < obstacles.size(); j++)
			{
				if (obstacles[j].sprite.getGlobalBounds().intersects(projectiles[i].sprite.getGlobalBounds()))
				{
					obstacles[j].isDead = true;
					projectiles[i].isDead = true;
				}
			}
		}

		if (projectiles[i].type == BLADE && projectiles[i].isDead == false)
		{
			
		
			// otetaan uusi kohde
		
				// ei oteta kohdetta jos kaikki kuolleet.
				if (obstacles.size() == 0)
				{
					projectiles[i].isDead = true;
	
					if (Gameboard::swordCounter > 20)
					{
	
						Gameboard::soundMaster.FindSound("epic")->setVolume(80);
						Gameboard::soundMaster.FindSound("epic")->setPitch(0.85);

						Gameboard::soundMaster.PlaySound("epic");

						Gameboard::soundMaster.FindSound("explosion")->setPitch(0.7);
						Gameboard::soundMaster.FindSound("explosion")->setVolume(25);
						Gameboard::soundMaster.PlaySound("explosion");

					}
					else if (Gameboard::swordCounter > 15)
					{

						
						Gameboard::soundMaster.FindSound("epic")->setVolume(64);
						Gameboard::soundMaster.FindSound("epic")->setPitch(1);

						Gameboard::soundMaster.PlaySound("epic");
						Gameboard::soundMaster.FindSound("magicRock")->setVolume(50);
						Gameboard::soundMaster.PlaySound("magicRock");
						
					}
					else if (Gameboard::swordCounter > 10)
					{

						Gameboard::soundMaster.FindSound("magicRock")->setVolume(30);
						Gameboard::soundMaster.PlaySound("magicRock");
					}
					else
					{

						Gameboard::soundMaster.FindSound("magicHealth")->setVolume(20);
						Gameboard::soundMaster.PlaySound("magicHealth");
					}
					Gameboard::swordCounter = -1;
				}


				else
				{
					bladeTargetObstacle = &obstacles[RNG::Random(obstacles.size()-1)];

				}
			
			if (Gameboard::swordTimer> 0.14f)
			{
				projectiles[i].sprite.setPosition(bladeTargetObstacle->sprite.getPosition().x + 7, bladeTargetObstacle->sprite.getPosition().y+60);
				Gameboard::swordTimer = 0;
				projectiles[i].sprite.setRotation(0);
		
			}
			//törmääkö kohteeseen

			if (projectiles[i].sprite.getGlobalBounds().intersects(bladeTargetObstacle->sprite.getGlobalBounds()))
			{
				Gameboard::soundMaster.PlaySound("fireProjectile");
				Gameboard::soundMaster.PlaySound("swordStrike");
				Gameboard::swordCounter++;
				bladeTargetObstacle->isDead = true;

			}
		}

		if (projectiles[i].sprite.getPosition().x > character.sprite.getPosition().x + 3200)
		{
			projectiles[i].isDead = true;
		}

	}
}
void GameScene::DeleteDead()
{
	for (std::vector<Projectile>::iterator it = projectiles.begin(); it != projectiles.end();)
	{
		if (it->isDead)
		{
			it = projectiles.erase(it);
		}
		else
		{
			it++;
		}
	}

	for (std::vector<Obstacle>::iterator it = obstacles.begin(); it != obstacles.end();)
	{
		if (it->isDead)
		{
			it = obstacles.erase(it);
		}
		else
		{
			it++;
		}
	}
	for (std::vector<Item>::iterator it = items.begin(); it != items.end();)
	{
		if (it->isDead)
		{
			it = items.erase(it);
		}
		else
		{
<<<<<<< HEAD
			it++;
=======
			// Delete, release.
>>>>>>> origin/master
		}
	}
}