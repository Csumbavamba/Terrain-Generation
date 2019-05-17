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

	virtual void Render(GLuint program) override;
	virtual void Update(float deltaTime) override;
	void SwapBetweenPostProcessing();
	virtual void Reset() override {};

	void ProcessPauseInput();

private:

	void CreateFrameBuffer();
	void PostProcessingRender(GLuint program);

	PauseMenu * pauseMenu = NULL;
	Terrain* terrain = NULL;
	MovingCube* movingCube = NULL;
	Star_2D* star = NULL;
	TessalatedQuad* tessQuad = NULL;

	// Post Processing
	GLuint frameBuffer;
	GLuint textureColorBuffer;
	GLuint screenVAO;
	GLuint sharpenProgram;
	GLuint blurProgram;
	GLuint edgeDetectionProgram;
	GLuint inverseColorsProgram;

	GLuint postProcessingProgram;
	bool isPostProcessingEnabled;

	
	
};

