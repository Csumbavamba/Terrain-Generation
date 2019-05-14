#pragma once

#include "Scene.h"

class PauseMenu;
class Terrain;

class GameScene :
	public Scene
{
public:
	GameScene();
	virtual ~GameScene() {};

	virtual void Update(float deltaTime) override;
	virtual void Reset() override {};

	void ProcessPauseInput();

private:

	PauseMenu * pauseMenu = NULL;
	Terrain* terrain = NULL;
};

