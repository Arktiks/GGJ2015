#pragma once
#include <SFML\Graphics.hpp>
#include "SceneParent.h"
#include "Character.h"
#include "Platform.h"
#include "Obstacle.h"
#include "SoundMaster.h"
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
	float gravitation; // Spagetti timereita, korjataan Character classin myötä.
	bool windowCheck, touchSurface; // Korjataan Character classin myötä.
	
	sf::View view; // Ikkunan scrollaus.
	std::vector<sf::RectangleShape> groundVector;
	std::vector<Platform> platformVector; // platformit
	std::vector<Obstacle> obstacles;
	//std::vector<enemies> enemyVector; viholliset

	void StartPiece();
	void Piece1();
	void PlatformSpawn();
	void PlatformUpdate();
	bool CheckPlatformCollision();
	bool CheckGroundCollision();
};