#include "Animation2D.h"


Animation2D::Animation2D(int spriteWidth, int spriteHeight, int texWidth, int texHeight, int frameIndex, std::string filePath)
{
	spriteSheetWidth = spriteWidth;
	spriteSheetHeight = spriteHeight;
	frameWidth = texWidth;
	frameHeight = texHeight;

	textureWidth = float(spriteSheetWidth) / frameWidth;
	textureHeight = float(spriteSheetHeight) / frameHeight;
	int numPerRow = texWidth / spriteSheetWidth;
	textureX = (frameIndex % numPerRow) * textureWidth;
	textureY = (frameIndex / numPerRow + 1) * textureHeight;

	this->filePath = filePath;

	this->frameIndex = frameIndex;
}

Animation2D::~Animation2D()
{
}

void Animation2D::Update(int animationIndex, bool isInAction, float deltaTime)
{

	frameIndex++; //USE DELTATIME

	if (animationIndex != 0)
	{
		if (isInAction)
		{
			int numPerRow = frameWidth / spriteSheetWidth;
			if (currentFrame >= numPerRow)
			{
				SetIsAnimationComplete(true);
				currentFrame = 0;
				return;
			}
		}

		if (animationIndex >= 1)
		{
			int spriteIndex = (int)(frameIndex * 0.15);
			int numPerRow = frameWidth / spriteSheetWidth;
			textureX = (spriteIndex % numPerRow) * textureWidth;
			textureY = animationIndex * textureHeight;

			currentFrame += 1;
			SetIsAnimationComplete(false);
		}
	}
}

void Animation2D::SetIsAnimationComplete(bool isComplete)
{
	isAnimationComplete = isComplete;
}

bool Animation2D::GetIsAnimationComplete()
{
	return isAnimationComplete;
}

GLfloat Animation2D::GetTextureX()
{
	return textureX;
}

GLfloat Animation2D::GetTextureY()
{
	return textureY;
}

GLfloat Animation2D::GetTextureWidth()
{
	return textureWidth;
}

GLfloat Animation2D::GetTextureHeight()
{
	return textureHeight;
}

std::string Animation2D::GetFilePath()
{
	return filePath;
}
