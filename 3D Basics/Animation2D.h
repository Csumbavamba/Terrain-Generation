#pragma once
#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glew\glew.h" 
#include "Dependencies\freeglut\freeglut.h" 
#include "Texture.h"
#include <string>

class Animation2D
{
public:

	Animation2D(int spriteWidth, int spriteHeight, int texWidth, int texHeight, int frameIndex, std::string filePath);
	~Animation2D();

	void Update(int lineOfSpriteSheetToPlay, bool isInAction, float deltaTime);
	void SetIsAnimationComplete(bool isComplete);
	bool GetIsAnimationComplete();

	GLfloat GetTextureX();
	GLfloat GetTextureY();
	GLfloat GetTextureWidth();
	GLfloat GetTextureHeight();

	std::string GetFilePath();

protected:
	bool isAnimationComplete = false;

	int spriteSheetWidth, spriteSheetHeight;
	int frameWidth, frameHeight;

	int currentFrame = 0;

	GLfloat textureWidth, textureHeight;
	GLfloat textureX, textureY;

	std::string filePath;

	int frameIndex = 0;

};

