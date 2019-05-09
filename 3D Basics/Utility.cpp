#include "Utility.h"

Utility * Utility::instance = NULL;

int Utility::GetScreenWidth()
{
	return GetInstance()->screenWidth;
}

int Utility::GetScreenHeight()
{
	return GetInstance()->screenHeight;
}

glm::vec2 Utility::GetScreenSize()
{
	return glm::vec2(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

void Utility::Update()
{
	GetInstance()->screenWidth = glutGet(GLUT_WINDOW_WIDTH);
	GetInstance()->screenHeight = glutGet(GLUT_WINDOW_HEIGHT);
}

void Utility::ShutDown()
{
	delete instance;
	instance = NULL;
}
