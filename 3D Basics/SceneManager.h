#pragma once

#include <vector>
#include <algorithm>
#include <string>

class Scene;

class SceneManager
{
public:

	static SceneManager * GetInstance();

	static void AddScenes(std::vector<Scene*> scenes);
	static int GetActiveSceneIndex();
	static Scene * GetActiveScene();
	static void ChangeActiveScene(int sceneNumber);
	static void ChangeActiveScene(std::string sceneName);
	static void ShutDown();

private:
	// Singleton
	SceneManager() {};
	~SceneManager() {};
	SceneManager(const SceneManager& copy) {};
	SceneManager& operator= (const SceneManager& move) {};

	static SceneManager * instance;

	std::vector<Scene*> scenes;
	Scene * activeScene = NULL;

};

