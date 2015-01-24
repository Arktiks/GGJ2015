#pragma once
#include <SFML\Graphics.hpp>

class GameObject
{
public:
	GameObject();
	~GameObject();
	//void SetTexture(std::string imageName);
	sf::Sprite sprite;

protected:
	sf::Texture *texture;
};