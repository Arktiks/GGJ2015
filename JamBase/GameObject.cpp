#include "GameObject.h"
#include "R.h"
using namespace sf;

void GameObject::SetTexture(std::string imageName)
{
	texture = R::LoadTexture(imageName);
	texture->setRepeated(true);
	sprite.setTexture(*texture);
}

void GameObject::UpdateSprite(float deltaTime)
{
	animationTimer += deltaTime;
	if (frames > 0 && animationTimer >= animationSmoothnes)
	{
		int tempSpriteWidth = texture->getSize().x / (frames+1);
		int tempSpriteHeight = texture->getSize().y;
		sprite.setTextureRect(IntRect(frameCount * tempSpriteWidth, 0, tempSpriteWidth, tempSpriteHeight));
		animationTimer = 0.0f;

		frameCount++;
		if (frameCount > frames)
			frameCount = 0;
	}
}