#pragma once
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Inputs
{
public:
	static void Update(sf::RenderWindow &window, sf::Event &events);

	static bool Mouse(enum sf::Mouse::Button mouseButton); // Onko hiiren oikeaa painettu.
	static bool Keyboard(enum sf::Keyboard::Key keyboardButton); // Onko SpaceBar painettu.
	static sf::Vector2<int> GetMousePosition();	// Palauttaa hiiren position.

private:
	static sf::Vector2<int> mousePosition;
	static sf::Event *events;
};