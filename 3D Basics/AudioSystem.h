#pragma once

#include "Dependencies\fmod\fmod.hpp"

#include <map>
#include <string>

class AudioSound;

class AudioSystem
{
public:
	AudioSystem();
	~AudioSystem();

	void Update();

	FMOD::System* audioSystem;

	int nextChannelID;

	typedef std::map<std::string, AudioSound*> SoundMap;
	typedef std::map<int, FMOD::Channel*> ChannelMap;

	SoundMap sounds;
	ChannelMap channels;
};