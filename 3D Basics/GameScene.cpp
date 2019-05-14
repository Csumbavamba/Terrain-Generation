#include "GameScene.h"
#include "Input.h"
#include "PauseMenu.h"
#include "Time.h"
#include "Terrain.h"
#include "Camera.h"

GameScene::GameScene()
{
	sceneName = "GameScene";

	pauseMenu = new PauseMenu(mainCamera);
	pauseMenu->SetActive(false);

	terrain = new Terrain(mainCamera);

	gameObjects.push_back(terrain);
	gameObjects.push_back(pauseMenu);
	

}

void GameScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);

	// Pause Input
	ProcessPauseInput();
}

void GameScene::ProcessPauseInput()
{
	// If the Escape Button is pressed
	if (Input::GetKeyState(27) == DOWN_FIRST)
	{
		// If the game is paused (Pause Menu active)
		if (pauseMenu->IsActive())
		{
			pauseMenu->SetActive(false);

			// Change the timeflow back to normal
			Time::SetTimeScale(1.0f);
			
		}
		// If the game is running (Pause Menu inactive)
		else
		{
			pauseMenu->SetActive(true);

			// Pause the time flow
			Time::SetTimeScale(0.0f);
		}
	}
}
