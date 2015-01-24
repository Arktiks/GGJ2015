#include "GameObject.h"
#include "R.h"

void GameObject::SetTexture(std::string imageName)
{
	texture = R::LoadTexture(imageName);
	texture->setRepeated(true);
	sprite.setTexture(*texture);
}