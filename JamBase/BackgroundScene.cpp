#include "BackgroundScene.h"
#include <iostream>
#include "SFML\System\Vector2.hpp"
#include "Base\R.h"
using namespace sf;

BackgroundScene::BackgroundScene() : backSpeed(0.3f)
{
	Texture *tempPointer = R::LoadTexture("parallax_back");
	back.setTexture(*tempPointer);
	back.setScale(1.68f, 1.68f);
	back.setPosition(0.0f, 0.0f);
	back2 = back;
	back2.setPosition(back.getGlobalBounds().width, 0.0f);
}

void BackgroundScene::Draw(sf::RenderWindow &window)
{
	window.draw(back);
	window.draw(back2);
}

void BackgroundScene::Update(float deltaTime, Event &events)
{
	back.setPosition(back.getPosition().x + (5.0f * backSpeed), 0.0f);
	back2.setPosition(back2.getPosition().x + (5.0f * backSpeed), 0.0f);
}

BackgroundScene::~BackgroundScene()
{
}