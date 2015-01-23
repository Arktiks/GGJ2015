#include "GameScene.h"
#include <iostream>
#include "SFML\System\Vector2.hpp"
#include "SFML\Window\Keyboard.hpp"
#include "Base\RNG.h"

using namespace sf; 

GameScene::GameScene() : jumpCheck(false), jumpTimer(0.0f), touchGround(false), jumpModifier(1.0f),
	gravitation(1.2f), windowCheck(false)
{
	Vector2f tempScreenSize(1280.0f, 800.0f);

	ground.setSize(Vector2f(tempScreenSize.x, 50.0f)); // Alustetaan maaper‰.
	ground.setPosition(0, (tempScreenSize.y - ground.getSize().y));
	ground.setFillColor(Color::Red);

	character.setSize(Vector2f(10.0f, 50.0f)); // Testihahmo.
	character.setPosition(10.0f, 500.0f);
	character.setFillColor(Color::Green);

	testChar = Character(10, 1, sf::FloatRect(0, 0, 0, 0));
	testChar.setTexture("JP.png");

	view.reset(FloatRect(0.0f, 0.0f, 1280.0f, 800.0f));
	view.rotate(0.0f);

	testobj.setTexture("JP.png");
	testobj.sprite.setPosition(400, 400);


}

void GameScene::Draw(sf::RenderWindow &window)
{
	window.draw(ground);
	window.draw(character);
	window.setView(view);
	window.draw(testChar.sprite);
	window.draw(testobj.sprite);
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

	if (ground.getGlobalBounds().intersects(character.getGlobalBounds())) // Pusketaan hahmoa ylˆs jos koskee maahan.
	{
		character.setPosition(Vector2f((character.getPosition().x),
			character.getPosition().y - 1.0f));
		touchGround = true;
		jumpCheck = false;
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
	if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			testChar.sprite.setPosition(testChar.sprite.getPosition().x - 5.0f, testChar.sprite.getPosition().y - 5.0f);
			testobj.sprite.setPosition(testobj.sprite.getPosition().x + 10.0f, testobj.sprite.getPosition().y + 10.0f);
		}



	// R‰tin‰‰
	//if (RNG::Chance(50))
	//	view.setRotation((float)RNG::Random(1));
	//else
	//	view.setRotation(0.0f - (float)RNG::Random(1));

	//view.setCenter(Vector2f(view.getCenter().x + 2.0f, view.getCenter().y));
}

GameScene::~GameScene()
{
}