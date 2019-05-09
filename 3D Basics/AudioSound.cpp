#include "AudioSound.h"
#include "AudioSystem.h"
#include "AudioEngine.h"




AudioSound::AudioSound(std::string filePath, PlayMode playMode)
{
	// Set Playmode
	if (playMode == LOOPING)
	{
		this->playMode = FMOD_LOOP_NORMAL;
	}
	else
	{
		this->playMode = FMOD_DEFAULT;
	}

	this->filePath = filePath;
	isStreaming = false;
	is3D = false; 
	volume = 1.0f;
	position = glm::vec3(0.0f, 0.0f, 0.0f);

	AudioEngine::GetInstance()->CreateSound(this);
}


AudioSound::~AudioSound()
{
	ReleaseSound();
}


FMOD_MODE AudioSound::GetPlayMode() const
{
	return playMode;
}

std::string AudioSound::GetFilePath() const
{
	return filePath;
}

FMOD::Channel * AudioSound::GetChannel() const
{
	return channel;
}

void AudioSound::SetChannel(FMOD::Channel * channel)
{
	this->channel = channel;
}

void AudioSound::SetVolume(float newVolume)
{
	AudioEngine::GetInstance()->SetChannelVolume(channelID, newVolume);
}

bool AudioSound::IsStreaming() const
{
	return isStreaming;
}

bool AudioSound::Is3D() const
{
	return is3D;
}

void AudioSound::PlaySound()
{
	channelID = AudioEngine::GetInstance()->PlaySound(this, position, volume);
}

void AudioSound::StopSound()
{
	AudioEngine::GetInstance()->StopSound(this);
}

void AudioSound::ReleaseSound()
{
	AudioEngine::GetInstance()->ReleaseSound(this);
}

FMOD::Sound * AudioSound::GetSound() const
{
	return sound;
}

void AudioSound::SetSound(FMOD::Sound * sound)
{
	this->sound = sound;
}
