#pragma once

#include "Dependencies\fmod\fmod.hpp"
#include "Dependencies/glm/glm.hpp"

#include <map>
#include <string>

class AudioSound;
class AudioSystem;

class AudioEngine
{
public:
	static AudioEngine * GetInstance();
	static void Update();
	static void Shutdown();
	static int ErrorCheck(FMOD_RESULT result);

	void CreateSound(AudioSound * sound);
	void ReleaseSound(AudioSound * sound);
	int PlaySound(AudioSound * sound, glm::vec3 position, float volumeDB);
	void StopSound(AudioSound * sound);

	void SetChannel3DPosition(int channelID, const glm::vec3& position);
	void SetChannelVolume(int channelID, float volumeDB);

private:

	AudioEngine();
	~AudioEngine();
	AudioEngine(const AudioEngine& copy) {};
	AudioEngine& operator= (const AudioEngine& move) {};

	FMOD_VECTOR VectorToFMOD(const glm::vec3& position);
	float DBToVolume(float dB);
	float VolumeToDB(float volume);

	static AudioEngine * instance;

	AudioSystem * audioSystem = NULL;
};