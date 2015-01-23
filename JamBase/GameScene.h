#pragma once
#include <SFML\Graphics.hpp>
#include "SceneParent.h"
#include "Character.h"
#include "GameObject.h"

class GameScene : public SceneParent
{
public:
	GameScene();
	void Draw(sf::RenderWindow &window);
	void Update(float deltaTime, sf::Event &events);
	~GameScene();

private:
	sf::RectangleShape ground, character;
	float jumpTimer, jumpModifier, gravitation;
	bool jumpCheck, touchGround, windowCheck;

	sf::View view;
	Character testChar;
	GameObject testobj;
	//Character character;
};