#include "R.h"
#include <utility>
#include <iostream>
std::map<std::string, sf::Texture*> R::textures;
std::map<std::string, sf::Font*> R::fonts;

sf::Texture* R::LoadTexture(std::string textureName)
{
	if(R::textures.count(textureName) == 0) // Tarkistetaan onko texture jo mapissa.
	{
		sf::Texture *texture = new sf::Texture;
		texture->loadFromFile(std::string("Resources/Textures/" + textureName + ".png")); // Textureille on m‰‰ritetty oma kansio.
		std::cout << "Texture " << textureName << " loaded." << std::endl; // Konfirmaatio viesti consolessa.
		textures.insert(std::make_pair(textureName, texture)); // Lis‰t‰‰n mappiin.
		return texture;
	}
	else
		return GetTexture(textureName); // Tekstuuri on jo luotu aiemmin, palautetaan pointer aiemmin luotuun.
}

sf::Texture* R::GetTexture(std::string textureName)
{
	if(R::textures.count(textureName) == 1)
	{
		std::map<std::string, sf::Texture*>::iterator it;
		it = textures.find(textureName);
		return it->second;
	}
	else
	{
		std::cout << "Couldn't find texture: " << textureName << std::endl;
		return NULL;
	}
}

void R::DeleteTexture(std::string textureName)
{
	if(R::textures.count(textureName) == 1)
	{
		std::map<std::string, sf::Texture*>::iterator it;
		it = textures.find(textureName);
		delete it->second;
		textures.erase(it);
	}
	else
		std::cout << "Couldn't delete texture: " << textureName << std::endl;
}

sf::Font* R::LoadFont(std::string fontName)
{
	if(fonts.count(fontName) == 0)
	{
		sf::Font *font = new sf::Font;
		font->loadFromFile(std::string("Resources/Fonts/" + fontName + ".ttf"));
		std::cout << "Font " << fontName << " loaded." << std::endl;
		fonts.insert(std::make_pair(fontName, font));
		return font;
	}
	else
		return GetFont(fontName);
}

sf::Font* R::GetFont(std::string fontName)
{
	if(R::fonts.count(fontName) == 1)
	{
		std::map<std::string, sf::Font*>::iterator it;
		it = fonts.find(fontName);
		return it->second;
	}
	else
	{
		std::cout << "Couldn't find font: " << fontName << std::endl;
		return NULL;
	}
}

void R::DeleteFont(std::string fontName)
{
	if(R::fonts.count(fontName) == 1)
	{
		std::map<std::string, sf::Font*>::iterator it;
		it = fonts.find(fontName);
		delete it->second;
		fonts.erase(it);
	}
	else
		std::cout << "Couldn't delete font: " << fontName << std::endl;
}