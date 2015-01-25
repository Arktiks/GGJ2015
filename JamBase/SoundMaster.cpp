#include "SoundMaster.h"


SoundMaster::SoundMaster()
{
}


SoundMaster::~SoundMaster()
{
}

void SoundMaster::AddSound(std::string name, std::string filepath)
{
	sf::SoundBuffer* buffer = new sf::SoundBuffer;

	if (!buffer->loadFromFile(filepath))
	{
		std::cout << "Sound loading fail" << std::endl;
	}
	else
	{
		std::cout << name << " from " << filepath << " loaded." << std::endl;
	//	sounds.insert(std::pair<std::string, sf::SoundBuffer>(name, buffer));
		soundbuffers.push_back(buffer);
		sounds.insert(std::pair<std::string, sf::Sound>(name, sf::Sound(*soundbuffers[soundbuffers.size()-1])));
	}
}
sf::Sound* SoundMaster::FindSound(std::string name)
{
	std::map<std::string, sf::Sound>::iterator it = sounds.find(name);
	if (sounds.end() != it)
		return &it->second;
	else
		return NULL;
}
void SoundMaster::PlaySound(std::string name)
{
	FindSound(name)->play();

}

void SoundMaster::LoadMusic(std::string name, std::string filepath)
{
	sf::Music* music = new sf::Music;
	if (!music->openFromFile(filepath))
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

