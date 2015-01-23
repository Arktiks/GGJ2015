#pragma once
#include <SFML\Graphics.hpp>
class GameObject
{
public:

	GameObject();
	~GameObject();

	void setTexture(std::string _imageName);

	sf::Sprite sprite;

private:

	sf::Texture texture;

};