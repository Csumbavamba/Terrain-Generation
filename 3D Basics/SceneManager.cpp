#include "SceneManager.h"
#include "Scene.h"

#include <iostream>

SceneManager * SceneManager::instance = NULL;

SceneManager * SceneManager::GetInstance()
{
	if (instance == NULL)
	{
		instance = new SceneManager();
	}
	return instance;
}

void SceneManager::AddScenes(std::vector<Scene*> scenes)
{
	GetInstance()->scenes = scenes;
	GetInstance()->activeScene = GetInstance()->scenes.front();
}

int SceneManager::GetActiveSceneIndex()
{
	for (unsigned int i = 0; i < GetInstance()->scenes.size(); i++)
	{
		if (GetInstance()->scenes[i] == GetInstance()->activeScene)
		{
			return i;
		}
	}

	std::cout << "WARNING: Scene couldn't be found!!" << std::endl;
	return -1; // TODO Log warning somewhere
}

Scene * SceneManager::GetActiveScene()
{
	for (Scene * scene : GetInstance()->scenes)
	{
		if (scene->IsActiveScene())
		{
			return scene;
		}
	}

	std::cout << "WARNING: Scene couldn't be found!!" << std::endl;
	return nullptr;
}

void SceneManager::ChangeActiveScene(int sceneNumber)
{
	// Reset Scenes
	for (Scene * scene : GetInstance()->scenes)
	{
		scene->SetIsActiveScene(false);
	}

	GetInstance()->activeScene = GetInstance()->scenes.at(sceneNumber);
	GetInstance()->activeScene->SetIsActiveScene(true);
}

void SceneManager::ChangeActiveScene(std::string sceneName)
{
	// Reset Scenes
	for (Scene * scene : GetInstance()->scenes)
	{
		scene->SetIsActiveScene(false);

		// Find the scene with the string and set it active
		if (scene->GetSceneName() == sceneName)
		{
			scene->SetIsActiveScene(true);
			GetInstance()->activeScene = scene;
		}
	}
}

void SceneManager::ShutDown()
{
	GetInstance()->scenes.clear();

	delete instance;
	instance = NULL;
}
