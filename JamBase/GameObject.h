#pragma once
#include <SFML\Graphics.hpp>

class GameObject
{
public:
	GameObject() : texture(NULL) {};
	
	virtual void SetTexture(std::string imageName); // Voi vaihdella luokittain.
	virtual ~GameObject() {}; // Vaihtelee luokittain.

	sf::Sprite sprite; // Public että voi nopeasti checkata collisionit etc.

protected:
	sf::Texture *texture;
};