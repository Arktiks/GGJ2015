#pragma once
#include <SFML\Graphics.hpp>
class GameObject
{
public:

	GameObject();
	~GameObject();

	void setTexture(std::string imageName);

	sf::Sprite sprite;

private:

	sf::Texture texture;

};