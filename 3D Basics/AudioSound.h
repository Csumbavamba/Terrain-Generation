#pragma once

#include <string>

#include "Dependencies\fmod\fmod.hpp"
#include "Dependencies/glm/glm.hpp"


enum PlayMode
{
	DEFAULT,
	LOOPING
};

class AudioSound
{
public:
	
	// Set the file path and whether it's looping or not
	AudioSound(std::string filePath, PlayMode playMode);
	~AudioSound();

	FMOD::Sound * GetSound() const;
	void SetSound(FMOD::Sound * sound);

	// Return whether it's Looping or Default
	FMOD_MODE GetPlayMode() const;
	std::string GetFilePath() const;

	// Return the Channel it's being played on
	FMOD::Channel * GetChannel() const;
	void SetChannel(FMOD::Channel * channel);

	// Value is between 0 and 1
	void SetVolume(float newVolume);

	// Streaming is not upported
	bool IsStreaming() const;

	// 3D is not supported
	bool Is3D() const;

	void PlaySound();
	void StopSound();

	// This is called when the sound is deleted
	void ReleaseSound();

private:

	std::string filePath;
	FMOD_MODE playMode;
	FMOD::Sound * sound = NULL;
	FMOD::Channel * channel = NULL;
	glm::vec3 position;
	int channelID;
	float volume;
	bool isStreaming;
	bool is3D;
};

