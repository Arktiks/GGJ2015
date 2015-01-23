#include <SFML\Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include <iostream>

//#include "Gameboard.h"
#include "Base\SceneSys.h"
#include "Game1.h"

int main()
{
	// Jos ikkunan koko tulee olemaan muutettava, t‰ll‰ saattaa olla v‰li‰.
	/*Gameboard gameboard;
	gameboard.SetWindowSize(sf::Vector2i(1280, 800));
	sf::RenderWindow window(sf::VideoMode(gameboard.GetWindowSize().x, gameboard.GetWindowSize().y),
		"Game Window", sf::Style::Close | sf::Style::Titlebar); // Window that can serve as a target for 2D drawing.*/
	
	sf::RenderWindow window(sf::VideoMode(1280, 800), "Game Window", sf::Style::Close | sf::Style::Titlebar); // Window that can serve as a target for 2D drawing.
	sf::Event event;				// Defines a system event and its parameters.
	float deltaTime = 0.0f;			// Elapsed time since the game last updated.
	sf::Time deltaConverter;		// Represents a time value.
	sf::Clock deltaClock;			// Lightweight class for measuring time.
	srand((int)time(NULL));			// Alustetaan RNG seed.
	window.setFramerateLimit(60);	// Limit the framerate to a maximum fixed frequency.

	Game1 *game = new Game1;
	SceneSys::ChangeScene(game);

	while(window.isOpen())
	{
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				window.close();
				break;
			}
		}
		deltaConverter = deltaClock.restart(); // Kellosta saadaan aika sf::Time muodossa.
		deltaTime = deltaConverter.asSeconds(); // Muutetaan sf::Time muoto floattiin.

		SceneSys::Update(deltaTime, event); // P‰ivitet‰‰n avatut scenet.
		SceneSys::Draw(window); // Piirret‰‰n scenet.
	}

	SceneSys::CleanScenes(); // Poistetaan scenet ennen sulkemista.
	return 0;
}