#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class SceneParent
{
public:
	SceneParent() : paused(false) {};
	virtual ~SceneParent() {}; // Deconstructor riippuu scenest‰.

	void SetPaused(bool Paused) { paused = Paused; }
	bool GetPaused() { return paused; }

	virtual void Update(float deltaTime, sf::Event &events) {}; // P‰ivitet‰‰n scene‰.
	virtual void Draw(sf::RenderWindow &window) {}; // Piirret‰‰n scene.

protected:
	bool paused; // Jos paused == true, scene‰ ei p‰ivitet‰.
};