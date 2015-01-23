#include "GameObject.h"


GameObject::GameObject()
{
	//texture = new sf::Texture;
}


GameObject::~GameObject()
{
	//delete texture;
}

void GameObject::setTexture(std::string imageName)
{
	texture.loadFromFile("Resources/Textures/"+imageName);
	sprite.setTexture(texture);
}
