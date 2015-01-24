#pragma once
#include <SFML\Graphics.hpp>

class GameObject
{
public:
	GameObject()
		: texture(NULL), frames(0), animationRepeat(true), frameCount(0),
		animationTimer(0.0f), animationSmoothnes(0.0f), animationBacktrack(false) {};
	
	virtual void SetTexture(std::string imageName); // Voi vaihdella luokittain.
	virtual void UpdateSprite(float deltaTime);
	virtual ~GameObject() {}; // Vaihtelee luokittain.

	sf::Sprite sprite; // Public että voi nopeasti checkata collisionit etc.

protected:
	sf::Texture *texture;
	int frames, frameCount;
	float animationTimer, animationSmoothnes;
	bool animationRepeat, animationBacktrack;
};