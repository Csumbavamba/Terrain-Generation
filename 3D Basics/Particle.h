#pragma once

#include "Transform.h"

class ParticleSystem;

class Particle
{
public:

	Particle(ParticleSystem* particleSystem);
	virtual ~Particle() {};

	void Update(float deltaTime);

// Functions
private:

	float RandomFloat();

// Variables
private:

	
	ParticleSystem* particleSystem = nullptr;
	glm::vec3 origin;
	glm::vec3 position;
	glm::vec3 velocity;
	float life;
};

