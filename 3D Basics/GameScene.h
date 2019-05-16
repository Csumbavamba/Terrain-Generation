#pragma once

#include "Scene.h"

class PauseMenu;
class Terrain;
class MovingCube;
class Star_2D;
class TessalatedQuad;

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
	MovingCube* movingCube = NULL;
	Star_2D* star = NULL;
	TessalatedQuad* tessQuad = NULL;
};

