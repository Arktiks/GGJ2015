#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>

class GameObject
{
protected:
	sf::Sprite *sprite;
	bool pressed;	// Est‰m‰‰n monta klikkausta per‰kk‰in kun hiiri pohjassa.
	bool checker;	// K‰ytet‰‰n varmistamaan doubleclick.
	float timer;	// K‰ytet‰‰n varmistamaan doubleclick.

public:
	GameObject(void);
	virtual void Draw(sf::RenderWindow &window); // Piirt‰‰ peli-objektin spriten ikkunaan.
	virtual void SetPosition(sf::Vector2<float> position); // Vaihtaa spriten positiota.
	virtual void SetSprite(sf::Sprite *sprite); // Poistetaan vanha sprite ja vaihdetaan uuteen.
	virtual bool Clicked(sf::Event &events); // Jos objektia painetaan returns true.
	virtual bool DoubleClick(sf::Event &events, float deltaTime); // Jos objektia tuplaklikataan returns true.
	virtual bool Hover(); // True jos hiiri on spriten p‰‰ll‰.
	virtual ~GameObject(void);
};