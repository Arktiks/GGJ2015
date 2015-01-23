#pragma once
#include <SFML\Graphics.hpp>
class GameObject
{
public:
	GameObject();
	void setTexture(std::string _imageName);
	~GameObject();

	sf::Sprite sprite;
private:
	sf::Texture texture;
};