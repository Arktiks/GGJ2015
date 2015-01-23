#include "TestScene.h"
#include "RNG.h"
#include "SFML\System\Vector2.hpp"

TestScene::TestScene()
{
	circle.setRadius(100.0f);
	circle.setPosition(100.0f, 100.0f);
	circle.setFillColor(sf::Color::Green);
	text.setString("aspdajsdpasdjo");
	text.setColor(sf::Color::White);
	text.setFont(*R::LoadFont("arial"));
	sprite.setTexture(*R::LoadTexture("test"));
	sprite.setPosition(300.0f, 300.0f);
}

void TestScene::Draw(sf::RenderWindow &window)
{
	window.draw(circle);
	window.draw(text);
	window.draw(sprite);
	gameObject.Draw(window);
}

void TestScene::Update(float deltaTime, sf::RenderWindow &window, sf::Event &events)
{
	if(RNG::Chance(1))
		gameObject.SetPosition(sf::Vector2f((float)RNG::Random(500),
		(float)RNG::Random(500)));

	gameObject.Clicked(events);
	gameObject.DoubleClick(events, deltaTime);
}

TestScene::~TestScene()
{
	R::DeleteFont("arial");
	R::DeleteTexture("test");
}