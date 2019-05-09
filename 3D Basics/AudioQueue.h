#pragma once

#include "Dependencies\fmod\fmod.hpp"

#include <string>
#include <vector>

class AudioSound;

class AudioQueue
{
public:
	AudioQueue();
	~AudioQueue();

	void AddToQueue(AudioSound * sound);
	void Play();

private:
	std::vector <AudioSound*> queue;
};

