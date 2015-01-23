// T‰m‰n hetkinen ResourceManager on mahdollista crashata aika monella tavalla. 
// Ehdottomasti pit‰‰ huolta ett‰ resourcet tuhotaan niitten Delete-komentojen avulla.


#pragma once
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <map>
#include <string>

class R
{
public:
	static sf::Texture* LoadTexture(std::string textureName);	// Ladataan Resources/Textures kansiosta.
	static sf::Texture* GetTexture(std::string textureName);	// Palautetaan pointteri haluttuun tekstuuriin.
	static void DeleteTexture(std::string textureName);			// Tekstuurit pit‰‰ tuhota t‰t‰ kautta ett‰ vektorit pysyy kunnossa.
	
	static sf::Font* LoadFont(std::string fontName);			// Ladataan Resources/Fonts kansiosta.
	static sf::Font* GetFont(std::string fontName);
	static void DeleteFont(std::string fontName);

private:
	static std::map<std::string, sf::Font*> fonts;
	static std::map<std::string, sf::Texture*> textures;
};