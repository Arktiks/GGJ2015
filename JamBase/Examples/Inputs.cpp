#include "Inputs.h"
sf::Vector2<int> Inputs::mousePosition;
sf::Event *Inputs::events;

void Inputs::Update(sf::RenderWindow &window, sf::Event &event)
{
	events = &event;
	mousePosition = sf::Mouse::getPosition(window);
}

bool Inputs::Mouse(enum sf::Mouse::Button mouseButton)
{
	if(events->type == sf::Event::MouseButtonPressed &&
	   events->mouseButton.button == mouseButton)
		return true;
	else
		return false;
}

bool Inputs::Keyboard(enum sf::Keyboard::Key keyboardButton)
{
	if(events->type == sf::Event::KeyPressed &&
	   events->key.code == keyboardButton)
		return true;
	else
		return false;
}

sf::Vector2<int> Inputs::GetMousePosition()
{
	return mousePosition;
}