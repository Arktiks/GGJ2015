#include "BackgroundScene.h"
#include <iostream>
#include "SFML\System\Vector2.hpp"
#include "Base\R.h"
#include "RNG.h"
#include "Gameboard.h"
using namespace sf;

BackgroundScene::BackgroundScene() : backSpeed(0.1f), platformTimer(0.0f)
{
	Texture *tempPointer = R::LoadTexture("parallax_back");
	back.setTexture(*tempPointer);
	back.setScale(1.68f, 1.68f);
	back.setPosition(-300.0f, 0.0f);
	back2 = back;
	back2.setPosition(back.getGlobalBounds().width - 300, 0.0f);
}

void BackgroundScene::Draw(sf::RenderWindow &window)
{
	window.draw(back);
	window.draw(back2);

	for (std::vector<GameObject>::iterator it = backPlatforms.begin(); it != backPlatforms.end(); it++)
		window.draw(it->sprite);
}

void BackgroundScene::Update(float deltaTime, Event &events)
{
	back.setPosition(back.getPosition().x + (5.0f * backSpeed), 0.0f);
	back2.setPosition(back2.getPosition().x + (5.0f * backSpeed), 0.0f);

	if (back.getGlobalBounds().left + back.getGlobalBounds().width < Gameboard::gameLocation.x - 700)
		back.setPosition(back2.getGlobalBounds().left + back2.getGlobalBounds().width, 0.0f);

	if (back2.getGlobalBounds().left + back2.getGlobalBounds().width < Gameboard::gameLocation.x - 700)
		back2.setPosition(back.getGlobalBounds().left + back.getGlobalBounds().width, 0.0f);

	for (std::vector<GameObject>::iterator it = backPlatforms.begin(); it != backPlatforms.end(); it++)
		it->UpdateSprite(deltaTime);

	platformTimer += deltaTime;
	if (platformTimer >= 1.0f)
	{
		GameObject tempPlatform;
		tempPlatform.frames = 5;
		tempPlatform.animationSmoothnes = 0.03f;
		tempPlatform.texture = R::LoadTexture("Flare");
		tempPlatform.sprite.setTexture(*tempPlatform.texture);
		tempPlatform.sprite.setScale(2.0f, 2.0f);
		tempPlatform.sprite.setPosition(Gameboard::playerLocation.x + (float)RNG::Between(1000, 1400),
			(float)RNG::Between(100, 700));
		backPlatforms.push_back(tempPlatform);
		platformTimer = 0.0f;
	}
}