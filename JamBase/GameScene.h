#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "SceneParent.h"
#include "Character.h"
#include "Platform.h"
#include "Obstacle.h"
#include "SoundMaster.h"
#include "Projectile.h"
#include "Item.h"



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
	float gravitation, zombieSpawner, protectionTimer; // Spagetti timereita, korjataan Character classin my�t�.
	bool windowCheck, touchSurface; // Korjataan Character classin my�t�.
	bool damageProtection, startCheck;
	
	sf::View view; // Ikkunan scrollaus.
	std::vector<sf::RectangleShape> groundVector;
	std::vector<Platform> platformVector; // platformit
	std::vector<Obstacle> obstacles;
	std::vector<Projectile> projectiles;
	std::vector<Item> items;
	sf::Sprite gunSprite;
	Obstacle* bladeTargetObstacle;
	void UpdateProjectiles();
	void StartPiece();
	void Piece1();
	void PlatformSpawn();
	void PlatformUpdate();
	bool CheckPlatformCollision();
	bool CheckGroundCollision();
	void DeleteDead();
};