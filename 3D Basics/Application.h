#pragma once

// Vertices and Textures
#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

#include <vector>
#include <string>

class ShaderLoader;

class Scene;
class StartMenuScene;
class CreditsScene;
class ControlsScene;
class GameScene;
class UITestScene;
class CutScene;

class AudioSound;

class Application
{
public:
	static Application * GetInstance();

	static void PlayGame(int argc, char **argv);
	void Initialise();
	static void Render();
	static void Update();
	
	static void QuitGame();

private:

	// Singleton
	Application();
	~Application();
	Application(const Application& copy) {};
	Application& operator= (const Application& move) {};

	static void ShutDownGame();

	static Application * instance;

	GLuint program;

	StartMenuScene * startMenuScene = NULL;
	CreditsScene * creditsScene = NULL;
	ControlsScene * controlsScene = NULL;
	GameScene * gameScene = NULL;
	UITestScene* uiTestScene = NULL;
	CutScene* introCutscene = NULL;
	

	std::vector<Scene*> scenes;
	AudioSound * backgroundMusic = NULL;

};

