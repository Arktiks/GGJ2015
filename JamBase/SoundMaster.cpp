#include "SoundMaster.h"


SoundMaster::SoundMaster()
{
	playing = false;
}


SoundMaster::~SoundMaster()
{
}

sf::SoundBuffer* SoundMaster::AddSound(std::string name, std::string filepath)
{
	sf::SoundBuffer* buffer = new sf::SoundBuffer;

	if (!buffer->loadFromFile("sounds/laava.wav"))
	{
		std::cout << "Sound loading fucked up" << std::endl;
	}
	else
	{
		sounds.insert(std::pair<std::string, sf::SoundBuffer*>(name, buffer));
		return buffer;
	}
}
sf::SoundBuffer* SoundMaster::FindSound(std::string name)
{
	std::map<std::string, sf::SoundBuffer*>::iterator it = sounds.find(name);
	sf::SoundBuffer* returnBuffer = it->second;
	return returnBuffer;
}
void SoundMaster::LoadMusic(std::string name, std::string filepath)
{
	sf::Music* music = new sf::Music;
	if (!music->openFromFile("music1.wav"))
	{
		std::cout << "Music loading fucked up" << std::endl;
	}
	else
	{
		musics.insert(std::pair<std::string, sf::Music*>(name, music));
	}
}

void SoundMaster::setCurrentMusic(std::string name)
{
	if (currentMusic != NULL)
	{
		currentMusic->stop();
	}
	std::map<std::string, sf::Music*>::iterator it = musics.find(name);
	currentMusic = it->second;
}