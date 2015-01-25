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
	void PlaySound(std::string name);
	sf::Sound* FindSound(std::string name);
	void LoadMusic(std::string name, std::string filepath);
	void setCurrentMusic(std::string name);
	~SoundMaster();
	sf::Music* currentMusic;
private:
	std::vector<sf::SoundBuffer*> soundbuffers;
	std::map<std::string, sf::SoundBuffer> soundbuffeers;
	std::map<std::string, sf::Music*> musics;
	std::map<std::string, sf::Sound> sounds;

};

