#include "AudioQueue.h"
#include "AudioSound.h"


#include <vector>
#include <algorithm>
#include <time.h>



AudioQueue::AudioQueue()
{
	srand((unsigned int)time((NULL)));
}


AudioQueue::~AudioQueue()
{
	queue.clear();
}

void AudioQueue::AddToQueue(AudioSound * sound)
{
	queue.push_back(sound);
}

void AudioQueue::Play()
{
	// Generate random number between 0 and sizeofVector - 1
	int randomSoundNumber = rand() % (queue.size());

	// Player vector at random Number
	queue.at(randomSoundNumber)->PlaySound();

}
