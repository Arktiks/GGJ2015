#pragma once
#include <SFML\Graphics.hpp>
#include "SceneParent.h"
#include "Character.h"
#include "Platform.h"
#include "Obstacle.h"
#include "SoundMaster.h"
#include "Projectile.h"

class GameScene :
	public SceneParent
{
public:
	GameScene();
	void Draw(sf::RenderWindow &window);
	void Update(float deltaTime, sf::Event &events);
	~GameScene() {};

private:
	Character character; // Peli-hahmo
	sf::Vector2f screenSize; // Ruudun koko kova koodattu lel.
	float gravitation, zombieSpawner, protectionTimer; // Spagetti timereita, korjataan Character classin myötä.
	bool windowCheck, touchSurface; // Korjataan Character classin myötä.
	bool damageProtection;
	
	sf::View view; // Ikkunan scrollaus.
	std::vector<sf::RectangleShape> groundVector;
	std::vector<Platform> platformVector; // platformit
	std::vector<Obstacle> obstacles;
	std::vector<Projectile> projectiles;

	void UpdateProjectiles();
	void StartPiece();
	void Piece1();
	void PlatformSpawn();
	void PlatformUpdate();
	bool CheckPlatformCollision();
	bool CheckGroundCollision();
};