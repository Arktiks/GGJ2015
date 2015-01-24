#include "Gameboard.h"
sf::Vector2f Gameboard::playerLocation = sf::Vector2f(0.0f, 0.0f);
sf::Vector2f Gameboard::gameLocation = sf::Vector2f(0.0f, 0.0f);
sf::Vector2i Gameboard::windowSize = sf::Vector2i(1280, 800);
int Gameboard::moneyAmount = 10;

/*sf::Vector2i Gameboard::windowSize = sf::Vector2i(0, 0);
void Gameboard::SetWindowSize(sf::Vector2i size)
{
	windowSize = size;
}
sf::Vector2i Gameboard::GetWindowSize()
{
	return windowSize;
}*/