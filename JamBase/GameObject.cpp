#include "GameObject.h"


GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::setTexture(std::string _imageName)
{
	texture.loadFromFile("Resources/Textures/"+_imageName);
	sprite.setTexture(texture);
}
