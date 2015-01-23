#pragma once
#include <SFML\Graphics.hpp>
#include "SceneParent.h"
#include "Character.h"

class GameScene :
	public SceneParent
{
public:
	GameScene();
	void Draw(sf::RenderWindow &window);
	void Update(float deltaTime, sf::Event &events);
	~GameScene();

private:
	//Character character; // Peli-hahmo
	sf::RectangleShape character; // Testihahmo.

	sf::Vector2f screenSize; // Ruudun koko kova koodattu lel.
	float jumpTimer, jumpModifier, gravitation; // Spagetti timereita, korjataan Character classin myötä.
	bool jumpCheck, touchGround, windowCheck; // Korjataan Character classin myötä.
	
	sf::View view; // Ikkunan scrollaus.
	std::vector<sf::RectangleShape> groundVector;
	//std::vector<enemies> enemyVector; viholliset

	void StartPiece();
	void Piece1();
};