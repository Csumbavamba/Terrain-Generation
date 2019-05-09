#include "AudioSystem.h"
#include "AudioEngine.h"

#include <vector>

AudioSystem::AudioSystem()
{
	audioSystem = NULL;
	FMOD_RESULT createdSystem;

	// Create audio system
	createdSystem = FMOD::System_Create(&audioSystem);
	AudioEngine::ErrorCheck(createdSystem);

	// Setup Audio System
	createdSystem = audioSystem->init(100, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, 0);
	AudioEngine::ErrorCheck(createdSystem);

}

AudioSystem::~AudioSystem()
{
	audioSystem->release();
}

void AudioSystem::Update()
{
	std::vector<ChannelMap::iterator> stoppedChannels;

	for (auto it = channels.begin(); it != channels.end(); ++it)
	{
		bool isPlaying = false;

		// Check if the sound is playing currently
		it->second->isPlaying(&isPlaying);

		if (!isPlaying)
		{
			// If it is not playing, add the sound to the not playing vector
			stoppedChannels.push_back(it);
		}
	}

	// Remove the sound from the channels
	for (auto& it : stoppedChannels)
	{
		channels.erase(it);
	}

	AudioEngine::ErrorCheck(audioSystem->update());
}