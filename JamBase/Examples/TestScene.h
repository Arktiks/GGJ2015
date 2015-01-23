#pragma once
#include <SFML\Graphics.hpp>
#include "SceneParent.h"
#include "R.h"
#include "GameObject.h"

class TestScene :
	public SceneParent
{
public:
	TestScene();
	void Draw(sf::RenderWindow &window);
	void Update(float deltaTime, sf::RenderWindow &window, sf::Event &events);
	~TestScene();

private:
	GameObject gameObject;
	sf::CircleShape circle;
	sf::Text text;
	sf::Sprite sprite;
};