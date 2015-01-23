#include "GameObject.h"


GameObject::GameObject()
{
	//texture = new sf::Texture;
}


GameObject::~GameObject()
{
	//delete texture;
}

void GameObject::setTexture(std::string _imageName)
{
	texture.loadFromFile("Resources/Textures/"+_imageName);
	sprite.setTexture(texture);
}
