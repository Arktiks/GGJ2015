#pragma once
#include <SFML\Graphics.hpp>
#include "SceneParent.h"
#include "Character.h"
#include "Platform.h"

class GameScene :
	public SceneParent
{
public:
	GameScene();
	void Draw(sf::RenderWindow &window);
	void Update(float deltaTime, sf::Event &events);
	
	~GameScene();

private:
	Character character; // Peli-hahmo
	//sf::RectangleShape character; // Testihahmo.

	sf::Vector2f screenSize; // Ruudun koko kova koodattu lel.
	float jumpTimer, jumpModifier, gravitation; // Spagetti timereita, korjataan Character classin my�t�.
	float jumpTicks;
	bool jumpCheck, touchGround, windowCheck, touchPlatform; // Korjataan Character classin my�t�.
	
	sf::View view; // Ikkunan scrollaus.
	std::vector<sf::RectangleShape> groundVector;
	std::vector<Platform> platformVector; // platformit
	//std::vector<enemies> enemyVector; viholliset

	void StartPiece();
	void Piece1();
	void PlatformSpawn();
	void PlatformUpdate();
};