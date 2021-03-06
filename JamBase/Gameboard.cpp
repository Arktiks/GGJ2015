#include "Gameboard.h"
#include "RNG.h"
sf::Vector2f Gameboard::playerLocation = sf::Vector2f(0.0f, 0.0f);
sf::Vector2f Gameboard::gameLocation = sf::Vector2f(0.0f, 0.0f);
sf::Vector2i Gameboard::windowSize = sf::Vector2i(1280, 800);
int Gameboard::moneyAmount = 3;
int Gameboard::chargeAmount = 10;
chargeType Gameboard::weapon = NONE;
SoundMaster Gameboard::soundMaster = SoundMaster();
bool Gameboard::characterIsDead = false;
float Gameboard::weaponTimer = 0;
float Gameboard::swordTimer = 0;
float Gameboard::textTimer = 0;
int Gameboard::swordCounter = 0;
float Gameboard::dropDownTimer = 0;

Gameboard::Gameboard()
{

}
void Gameboard::loadSounds()
{
	soundMaster.LoadMusic("music1", "Sounds/music1.wav");
	soundMaster.LoadMusic("music2", "Sounds/music2.wav");
	soundMaster.LoadMusic("music3", "Sounds/music3.wav");

	//��net on niin t�rkeen pieni� ett� pidet��n muistissa kokoajan
	soundMaster.AddSound("coin", "Sounds/coin.wav");
	soundMaster.AddSound("collision", "Sounds/collision.wav");
	soundMaster.AddSound("epic", "Sounds/epic.wav");
	soundMaster.AddSound("explosion", "Sounds/explosion.wav");
	soundMaster.AddSound("fire", "Sounds/fire.wav");
	soundMaster.AddSound("fireMobDeath", "Sounds/fireMobDeath.wav");
	soundMaster.AddSound("fireProjectile", "Sounds/fireProjectile.wav");
	soundMaster.AddSound("flameBurst", "Sounds/flameBurst.wav");
	soundMaster.AddSound("cannon", "Sounds/gunShot.wav");
	soundMaster.AddSound("itemPickup", "Sounds/itempickup.wav");
	soundMaster.AddSound("jump", "Sounds/jump.wav");
	soundMaster.AddSound("itemPickup2", "Sounds/itempickup2.wav");
	soundMaster.AddSound("lava", "Sounds/lava.wav");
	soundMaster.AddSound("magic1", "Sounds/magic1.wav");
	soundMaster.AddSound("magic2", "Sounds/magic2.wav");
	soundMaster.AddSound("magicFly", "Sounds/magicFly.wav");
	soundMaster.AddSound("magicHealth", "Sounds/magicHealth.wav");
	soundMaster.AddSound("magicRock", "Sounds/magicRock.wav");
	soundMaster.AddSound("smoke", "Sounds/smoke.wav");
	soundMaster.AddSound("swordStrike", "Sounds/swordStrike.wav");
	soundMaster.AddSound("whistle", "Sounds/whistle.wav");

	soundMaster.FindSound("jump")->setVolume(30);
	soundMaster.FindSound("jump")->setPitch(0.9);

	soundMaster.FindSound("swordStrike")->setVolume(30);
	soundMaster.FindSound("fireProjectile")->setVolume(30);
	// Testi
	int tempRNG = RNG::Random(2);
	{
		if (tempRNG == 0)
		{
			soundMaster.setCurrentMusic("music1");
		}
		else if (tempRNG == 1)
		{
			soundMaster.setCurrentMusic("music2");
		}
		else
		{
			soundMaster.setCurrentMusic("music3");
		}
	}
	soundMaster.currentMusic->setVolume(40);
	soundMaster.currentMusic->setLoop(true);
	soundMaster.currentMusic->play();
}
/*sf::Vector2i Gameboard::windowSize = sf::Vector2i(0, 0);
void Gameboard::SetWindowSize(sf::Vector2i size)
{
	windowSize = size;
}
sf::Vector2i Gameboard::GetWindowSize()
{
	return windowSize;
}*/