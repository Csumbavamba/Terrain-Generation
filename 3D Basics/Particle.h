#pragma once

#include "Transform.h"


class ParticleSystem;

class Particle
{
public:

	Particle(ParticleSystem* particleSystem, int randomizerID);
	virtual ~Particle() {};

	void Update(float deltaTime);

	glm::vec3 GetPosition() const;
	float GetLife() const;
	void SetLife(float life);

	static float RandomFloat();

// Functions
private:

	float RandomFloatInRange(float from, float to);
	

// Variables
private:
	float life;
	int randomizerID;

	ParticleSystem* particleSystem = nullptr;
	glm::vec3 origin;
	glm::vec3 position;
	glm::vec3 velocity;
	
};

