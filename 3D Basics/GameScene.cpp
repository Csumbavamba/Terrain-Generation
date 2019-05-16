#include "GameScene.h"
#include "Input.h"
#include "PauseMenu.h"
#include "Time.h"
#include "Terrain.h"
#include "Camera.h"
#include "MovingCube.h"
#include "Star_2D.h"
#include "TessalatedQuad.h"

GameScene::GameScene()
{
	sceneName = "GameScene";

	pauseMenu = new PauseMenu(mainCamera);
	pauseMenu->SetActive(false);

	terrain = new Terrain(mainCamera);
	movingCube = new MovingCube(mainCamera);
	movingCube->SetTerrain(terrain);
	star = new Star_2D(mainCamera);
	star->SetTerrain(terrain);
	tessQuad = new TessalatedQuad(mainCamera);
	tessQuad->SetTerrain(terrain);

	gameObjects.push_back(terrain);
	gameObjects.push_back(movingCube);
	gameObjects.push_back(star);
	gameObjects.push_back(tessQuad);
	gameObjects.push_back(pauseMenu);
	

}

void GameScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);

	// Pause Input
	ProcessPauseInput();

	if (Input::GetKeyState('q') == DOWN)
	{
		glPolygonMode(GL_FRONT, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT, GL_FILL);
	}
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
