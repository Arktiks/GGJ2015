#include "SceneSys.h"
std::vector<SceneParent*> SceneSys::currentScenes;
bool SceneSys::sceneChanged;

void SceneSys::Draw(sf::RenderWindow &window)
{
	window.clear(sf::Color::Black); // Pyyhit‰‰n RenderWindow.
	for (std::vector<SceneParent*>::iterator it=currentScenes.begin(); it!=currentScenes.end(); it++)
		(*it)->Draw(window); // Piirret‰‰n scenet j‰rjestyksess‰.
	window.display(); // Ja n‰ytet‰‰n scenet pelaajalle.
}

void SceneSys::Update(const float deltaTime, sf::Event &events)
{
	for (std::vector<SceneParent*>::iterator it=currentScenes.begin(); it!=currentScenes.end(); it++)
	{
		if(!(*it)->GetPaused()) // P‰ivitet‰‰n scene‰, jos se ei ole pausella.
			(*it)->Update(deltaTime, events);
		if(sceneChanged) // Jos scenejen m‰‰r‰ vaihtuu Updaten aikana - vanha iteraattori ei kelpaa en‰‰.
		{
			sceneChanged = false;
			break; // Poistutaan Update-loopista.
		}
	}
}

void SceneSys::OpenScene(SceneParent *newScene)
{
	currentScenes.push_back(newScene);
	sceneChanged = true;
}

void SceneSys::ChangeScene(SceneParent *newScene)
{
	CleanScenes();
	OpenScene(newScene); // Avataan uusi scene.
}

void SceneSys::CleanScenes()
{
	if(currentScenes.size() > 0)
	{
		for(std::vector<SceneParent*>::iterator it = currentScenes.begin(); it != currentScenes.end(); it++)
			delete (*it); // Deletoidaan jokainen scene.
	}
	currentScenes.clear(); // Puhdistetaan vektori.
}

void SceneSys::CloseCurrentScene()
{
	if(currentScenes.size() > 0)
	{
		delete currentScenes.back();
		currentScenes.pop_back();
		sceneChanged = true;
	}
}