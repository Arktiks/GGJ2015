#pragma once
#include <SFML\Graphics.hpp>

class GameObject
{
public:
	GameObject()
		: texture(NULL), frames(0), frameCount(0),
		animationTimer(0.0f), animationSmoothnes(0.0f) {};
	
	virtual void SetTexture(std::string imageName); // Voi vaihdella luokittain.
	virtual void UpdateSprite(float deltaTime);
	virtual ~GameObject() {}; // Vaihtelee luokittain.

	sf::Sprite sprite; // Public ett� voi nopeasti checkata collisionit etc.

protected:
	sf::Texture *texture;
	int frames, frameCount;
	float animationTimer, animationSmoothnes;
};