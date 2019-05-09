#include "AudioEngine.h"
#include "AudioSound.h"
#include "AudioSystem.h"

#include <iostream>
#include <vector>

AudioEngine * AudioEngine::instance = NULL;

AudioEngine::AudioEngine()
{
	audioSystem = new AudioSystem();
}

AudioEngine::~AudioEngine()
{
	delete audioSystem;
	audioSystem = NULL;
}

AudioEngine * AudioEngine::GetInstance()
{
	if (instance == NULL)
	{
		instance = new AudioEngine();
	}
	return instance;
}


void AudioEngine::Update()
{
	GetInstance()->audioSystem->Update();
}

void AudioEngine::Shutdown()
{
	delete instance;
	instance = NULL;
}

int AudioEngine::ErrorCheck(FMOD_RESULT result)
{
	if (result != FMOD_OK) {
		std::cout << "FMOD ERROR " << result << std::endl;
		return 1;
	}

	return 0;
}

void AudioEngine::CreateSound(AudioSound * sound)
{
	auto foundIt = audioSystem->sounds.find(sound->GetFilePath());

	// If the sound exists, do nothing
	if (foundIt != audioSystem->sounds.end())
		return;

	// Set PlayMode
	FMOD_MODE playMode = FMOD_DEFAULT;

	playMode |= sound->Is3D() ? FMOD_3D : FMOD_2D;
	playMode |= sound->GetPlayMode() ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
	playMode |= sound->IsStreaming() ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;

	// Create the Sound
	FMOD::Sound * tempSound = NULL;

	AudioEngine::ErrorCheck(audioSystem->audioSystem->createSound(sound->GetFilePath().c_str(), playMode, 0, &tempSound));


	// If it is successfully created, add it to the sound library
	if (tempSound)
	{
		sound->SetSound(tempSound);
		audioSystem->sounds[sound->GetFilePath()] = sound;
	}

}

void AudioEngine::ReleaseSound(AudioSound * sound)
{
	// Check if the sound is registered
	auto foundIt = audioSystem->sounds.find(sound->GetFilePath());

	// If it is not don't do anything
	if (foundIt == audioSystem->sounds.end())
		return;

	// Otherwise release it
	AudioEngine::ErrorCheck(foundIt->second->GetSound()->release());
	audioSystem->sounds.erase(foundIt);
}

int AudioEngine::PlaySound(AudioSound * sound, glm::vec3 position, float volumeDB)
{
	// Assign channel ID for the sound
	int channelID = audioSystem->nextChannelID++;

	// Try to find the sound in the registered sounds
	auto foundIt = audioSystem->sounds.find(sound->GetFilePath());

	// If it doesn't exist
	if (foundIt == audioSystem->sounds.end())
	{
		// Load the sound
		CreateSound(sound); // TODO Load sound here not a string

		foundIt = audioSystem->sounds.find(sound->GetFilePath());

		// If it still doesn't work, there is something wrong
		if (foundIt == audioSystem->sounds.end())
		{
			return channelID;
		}
	}

	FMOD::Channel * channel = NULL;

	// Allow sound playing BUT pause the sound until it is set up
	AudioEngine::ErrorCheck(audioSystem->audioSystem->playSound(foundIt->second->GetSound(), NULL, true, &channel));

	// If the channel is fine
	if (channel)
	{
		FMOD_MODE currentMode;

		sound->SetChannel(channel);

		foundIt->second->GetSound()->getMode(&currentMode);

		// In case it's a 3D sound, place it in the world and set it's attributes
		if (currentMode & FMOD_3D)
		{
			FMOD_VECTOR soundPosition = VectorToFMOD(position);
			AudioEngine::ErrorCheck(channel->set3DAttributes(&soundPosition, NULL));
		}

		// Set the volume and unpause the sound
		AudioEngine::ErrorCheck(channel->setVolume(DBToVolume(volumeDB)));
		AudioEngine::ErrorCheck(channel->setPaused(false));
		audioSystem->channels[channelID] = channel;
	}

	return channelID;
}

void AudioEngine::StopSound(AudioSound * sound)
{
	// Try to find the sound in the registered sounds
	auto foundIt = audioSystem->sounds.find(sound->GetFilePath());

	// If it is not found, return null
	if (foundIt == audioSystem->sounds.end())
		return;

	// Otherwise, find the channel of the sound and pause it
	FMOD::Channel * channel = foundIt->second->GetChannel();
	channel->setPaused(true);
}


void AudioEngine::SetChannel3DPosition(int channelID, const glm::vec3 & position)
{
	auto foundIt = audioSystem->channels.find(channelID);

	// If the sound doesn't exist, stop execution
	if (foundIt == audioSystem->channels.end())
		return;

	// Transfer vector position to FMOD position
	FMOD_VECTOR FMODPosition = VectorToFMOD(position);

	// Setup the Audio attributes
	AudioEngine::ErrorCheck(foundIt->second->set3DAttributes(&FMODPosition, NULL));
}

void AudioEngine::SetChannelVolume(int channelID, float volumeDB)
{
	auto foundIt = audioSystem->channels.find(channelID);

	// If the sound doesn't exist, stop execution
	if (foundIt == audioSystem->channels.end())
		return;

	AudioEngine::ErrorCheck(foundIt->second->setVolume(volumeDB));
}



FMOD_VECTOR AudioEngine::VectorToFMOD(const glm::vec3 & position)
{
	FMOD_VECTOR fmodPosition;

	fmodPosition.x = position.x;
	fmodPosition.y = position.y;
	fmodPosition.z = position.z;

	return fmodPosition;
}

float AudioEngine::DBToVolume(float dB)
{
	return powf(10.0f, 0.05f * dB);
}

float AudioEngine::VolumeToDB(float volume)
{
	return 20.0f * log10f(volume);
}

