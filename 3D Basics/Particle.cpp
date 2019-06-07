#include "Particle.h"
#include "ParticleSystem.h"
#include "GameObject.h"

Particle::Particle(ParticleSystem* particleSystem)
{
	this->particleSystem = particleSystem;

	this->origin = particleSystem->GetOwner()->transform.position;

	this->position = this->origin;
	this->velocity = glm::vec3(0.0f, 1.0f, 0.0f);
	this->life = 1.0f;
}


void Particle::Update(float deltaTime)
{
	this->velocity.y += -0.2f * deltaTime;
	this->position += velocity;
	this->life -= deltaTime;

	if (life <= 0.0f)
	{
		this->position = this->origin;

		// TODO Calculate randmized velocity
		this->velocity = glm::vec3(0.1f, 1.0f, 0.1f);

		this->life = RandomFloat() + 0.125f;
	}
}

float Particle::RandomFloat()
{
	return (float)rand() / (double)RAND_MAX;
}
