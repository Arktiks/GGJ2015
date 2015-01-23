#include "GameObject.h"
#include "R.h"
#include "Inputs.h"
#include <iostream>

GameObject::GameObject(void)
{
	sprite = new sf::Sprite(*R::LoadTexture("test"));
	//sprite->setTexture(*R::LoadTexture("test"), true);
}

void GameObject::Draw(sf::RenderWindow &window)
{
	window.draw(*sprite);
}

void GameObject::SetPosition(sf::Vector2<float> position)
{
	sprite->setPosition(position);
}

void GameObject::SetSprite(sf::Sprite *sprite)
{
	delete sprite;
	(this->sprite) = sprite;
}

bool GameObject::Clicked(sf::Event &events)
{
	if(events.type == sf::Event::MouseButtonReleased)
		pressed=false;
	if(events.type == sf::Event::MouseButtonPressed && // Hiirt‰ painetaan.
		events.mouseButton.button == sf::Mouse::Left && // Painetaan hiiren vasenta.
		pressed == false &&
		sprite->getGlobalBounds().contains(Inputs::GetMousePosition())) // Kohdistin napin p‰‰ll‰.
	{
		std::cout << "Button click!" << std::endl;
		pressed = true;
		return true;
	}
	else
		return false;
}

bool GameObject::DoubleClick(sf::Event &events, float deltaTime)
{
	timer += deltaTime; // K‰ytet‰‰n hyˆdyksi deltaTimea tuplaklikkauksen varmistamiseksi.
	if(Clicked(events))
	{
		if(checker == true)
		{
			checker = false;
			std::cout << "Double-click!" << std::endl;
			return true;
		}
		else
			checker = true;
	}
	if(timer > 5.0f)
	{
		timer = 0;
		checker = false;
	}
	return false;
}

bool GameObject::Hover()
{
	if(sprite->getGlobalBounds().contains(Inputs::GetMousePosition()))
		return true;
	else
		return false;
}

GameObject::~GameObject()
{
	// Huomio: Tuhoaa spriten mutta ei sen tekstuuria.
	delete sprite;
}