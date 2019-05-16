#include "GameScene.h"
#include "Input.h"
#include "PauseMenu.h"
#include "Time.h"
#include "Terrain.h"
#include "Camera.h"
#include "MovingCube.h"
#include "Star_2D.h"
#include "TessalatedQuad.h"
#include "Utility.h"

#include <iostream>

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


	CreateFrameBuffer();

}

void GameScene::CreateFrameBuffer()
{
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	// Create Color attachement texture
	GLuint textureColorBuffer;
	glGenTextures(1, &textureColorBuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorBuffer);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Utility::GetScreenWidth(), Utility::GetScreenHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind buffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorBuffer, 0); // Attach it to the framebuffer

																										// Create renderbuffer object for depth attachement
	GLuint renderBufferObject;
	glGenRenderbuffers(1, &renderBufferObject);
	glBindRenderbuffer(GL_RENDERBUFFER, renderBufferObject);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Utility::GetScreenWidth(), Utility::GetScreenHeight());

	glBindRenderbuffer(GL_RENDERBUFFER, 0); // Unbind buffer
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferObject); // Attach it to the framebuffer


																												 // Check if we were successful
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Successfully created framebuffer";
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	else
	{
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!";
	}
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
