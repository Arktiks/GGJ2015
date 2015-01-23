#include <SFML\Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "Base\SceneSys.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 640), "Game Window", sf::Style::Close | sf::Style::Titlebar); // Window that can serve as a target for 2D drawing.
	sf::Event event;				// Defines a system event and its parameters.
	float deltaTime = 0.0f;			// Elapsed time since the game last updated.
	sf::Time deltaConverter;		// Represents a time value.
	sf::Clock deltaClock;			// Lightweight class for measuring time.
	srand((int)time(NULL));			// Alustetaan RNG seed.
	window.setFramerateLimit(60);	// Limit the framerate to a maximum fixed frequency.

	//TestScene *test = new TestScene;
	//SceneSys::ChangeScene(test);

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