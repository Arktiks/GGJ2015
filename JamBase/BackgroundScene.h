#pragma once
#include <SFML\Graphics.hpp>
#include "SceneParent.h"
#include "GameObject.h"

class BackgroundScene :
	public SceneParent
{
public:
	BackgroundScene();
	void Draw(sf::RenderWindow &window);
	void Update(float deltaTime, sf::Event &events);
	~BackgroundScene() {};

private:
	sf::Sprite back, back2;
	float backSpeed;
	std::vector<GameObject> backPlatforms;
	float platformTimer;
};