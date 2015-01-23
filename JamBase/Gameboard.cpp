#include "Gameboard.h"
sf::Vector2i Gameboard::windowSize = sf::Vector2i(0, 0);

void Gameboard::SetWindowSize(sf::Vector2i size)
{
	windowSize = size;
}

sf::Vector2i Gameboard::GetWindowSize()
{
	return windowSize;
}