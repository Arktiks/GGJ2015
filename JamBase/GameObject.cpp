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
		int tempSpriteWidth = texture->getSize().x / frames;
		int tempSpriteHeight = texture->getSize().y;
		sprite.setTextureRect(IntRect(frameCount * tempSpriteWidth, 0, tempSpriteWidth, tempSpriteHeight));
		animationTimer = 0.0f;

		if (animationRepeat)
			frameCount++;
		else if (!animationBacktrack && !animationRepeat)
			frameCount++;

		if (frameCount > frames && animationRepeat)
			frameCount = 0;
		else if (animationBacktrack && frameCount < frames)
		{
			if (frameCount < 0)
			{
				frameCount = 0;
				animationBacktrack = false;
			}
			else
				frameCount--;
		}
		else if (frameCount > frames && !animationRepeat && !animationBacktrack)
		{
			frameCount -= 2;
			animationBacktrack = true;
		}
	}
}