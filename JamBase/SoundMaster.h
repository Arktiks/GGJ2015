#pragma once
#include <SFML\System.hpp>
#include <SFML\Audio.hpp>
#include <map>
#include <string>
#include <iostream>
class SoundMaster
{
public:
	SoundMaster();
	void AddSound(std::string name, std::string filepath);
	sf::SoundBuffer* FindSound(std::string name);
	void LoadMusic(std::string name, std::string filepath);
	void setCurrentMusic(std::string name);
	~SoundMaster();
	sf::Music* currentMusic;
private:
	std::map<std::string, sf::SoundBuffer> sounds;
	std::map<std::string, sf::Music*> musics;
};

