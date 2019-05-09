#include "Dependencies\freeglut\freeglut.h"

#include <iostream>

#include "Time.h"


Time* Time::instance = NULL;

Time::Time()
{
	deltaTime = 0.0f;
	timeScale = 1.0f;
	previousTimeStamp = (float)glutGet(GLUT_ELAPSED_TIME);
}


Time* Time::GetInstance()
{
	if (instance == NULL)
	{
		instance = new Time();
	}
	return instance;
}

void Time::Update()
{
	// Calculate Time
	float currentTime = (float)glutGet(GLUT_ELAPSED_TIME);
	GetInstance()->deltaTime = (currentTime - GetInstance()->previousTimeStamp) * 0.001f * GetInstance()->timeScale;
	GetInstance()->previousTimeStamp = currentTime;
}

void Time::ShutDown()
{
	delete instance;
	instance = NULL;
}

float Time::GetDeltaTime()
{
	return GetInstance()->deltaTime;
}

float Time::GetTimeScale()
{
	return GetInstance()->timeScale;
}


void Time::SetTimeScale(float newTimeScale)
{
	// If the given time scale is smaller than 0, set it to 0
	if (newTimeScale < 0.0f)
	{
		GetInstance()->timeScale = 0.0f;
	}
	else
	{
		GetInstance()->timeScale = newTimeScale;
	}
}
