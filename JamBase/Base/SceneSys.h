// P‰ivitt‰‰ ja piirt‰‰ SceneParentista perittyj‰ olioita.
// Helpoin tapa k‰ytt‰‰ lis‰‰m‰ll‰ Update/Draw mainlooppiin.
// Sen j‰lkeen scenej‰ manipuloidaan staattisesti.

#pragma once
#include <string>
#include <vector>
#include "SceneParent.h"

class SceneSys 
{
public:
	static void Draw(sf::RenderWindow &window);	// Piirret‰‰n scenet currentScene vektorissa.
	static void Update(float deltaTime, sf::Event &events);	// P‰ivitet‰‰n scenet currentScene vektorissa.
	static void OpenScene(SceneParent *newScene); // Avataan uusi scene kaikkien muiden p‰‰lle.
	static void ChangeScene(SceneParent *newScene); // Pyyhit‰‰n kaikki scenet ja aloitetaan uusi.
	static void CleanScenes(); // Poistetaan kaikki scenet.
	static void CloseCurrentScene(); // Lopetetaan viimeisin scene.

private:
	static std::vector<SceneParent*> currentScenes;	// T‰m‰n hetkiset scenet.
	static bool sceneChanged; // Est‰m‰‰n Update-iteraattorin rikkominen.
};