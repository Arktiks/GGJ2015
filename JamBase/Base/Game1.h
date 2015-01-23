#pragma once
#include <SFML\Graphics.hpp>
#include "SceneParent.h"

class Game1 :
	public SceneParent
{
public:
	Game1();
	void Draw(sf::RenderWindow &window);
	void Update(float deltaTime, sf::RenderWindow &window, sf::Event &events);
	~Game1();

private:
	sf::CircleShape circle;
	sf::RectangleShape rectangle;
};