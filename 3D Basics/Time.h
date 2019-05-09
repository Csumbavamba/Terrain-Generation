#pragma once

class Time
{
public:

	static Time* GetInstance();

	// A requirement for working deltaTime calculation
	static void Update();

	// Deletes the singleton Instance
	static void ShutDown();
	static float GetDeltaTime();

	// Gets the current timeScale 0.0f is effectively pausing the game, while 1.0f is the standard scale
	static float GetTimeScale();

	// Sets the speed of the game, negative numbers are not allowed (negatives are clamped as 0)
	static void SetTimeScale(float newTimeScale);

private:
	// Singleton method
	Time();
	~Time() {};
	Time(const Time& copy) {};
	Time& operator= (const Time& move) {};

	static Time* instance;

	float deltaTime;
	float previousTimeStamp;
	float timeScale;
};

