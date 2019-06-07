#include "Particle.h"
#include "ParticleSystem.h"
#include "GameObject.h"
#include "Time.h"
#include <time.h>
#include <random>

Particle::Particle(ParticleSystem* particleSystem, int randomizerID)
{
	srand(time(NULL));

	this->particleSystem = particleSystem;
	this->randomizerID = randomizerID;

	this->origin = particleSystem->GetOwner()->transform.position;

	this->position = this->origin;

	this->velocity = glm::vec3(
		0.25f * sin(randomizerID * Time::GetDeltaTime()) + 0.25f * RandomFloat() - 0.125f,
		1.5f + 0.25f * RandomFloat() - 0.125f,
		0.25f * cos(randomizerID* Time::GetDeltaTime()) + 0.25f * RandomFloat() - 0.125f);

	this->life = RandomFloat() + 0.5f;
}


void Particle::Update(float deltaTime)
{
	// keep updating the position of the particles
	this->origin = particleSystem->GetOwner()->transform.position;

	this->velocity.y += -0.2f * deltaTime;
	this->position += velocity * deltaTime;
	this->life -= deltaTime;

	// If Particle is dead
	if (life <= 0.0f)
	{
		// Reposition particle
		this->position = this->origin;

		// Randomize x and z coordinates
		this->position.x += RandomFloatInRange(-0.2f, 0.2f);
		this->position.z += RandomFloatInRange(-0.2f, 0.2f);

		// Calculate the actual velocity - TODO Add Speed
		this->velocity = glm::vec3(
			0.25f * sin(randomizerID * deltaTime) + 0.25f * RandomFloat() - 0.125f,
			1.5f + 0.25f * RandomFloat() - 0.125f,
			0.25f * cos(randomizerID * deltaTime) + 0.25f * RandomFloat() - 0.125f);

		// Reset particle life
		this->life = RandomFloat() + 0.5f;
	}
}

glm::vec3 Particle::GetPosition() const
{
	return position;
}

float Particle::GetLife() const
{
	return life;
}

void Particle::SetLife(float life)
{
	this->life = life;
}

float Particle::RandomFloatInRange(float from, float to)
{
	std::random_device rand_dev;
	std::mt19937 generator(rand_dev());
	std::uniform_real_distribution<float>  distributor(from, to);

	return distributor(generator);
}

float Particle::RandomFloat()
{
	return (float)rand() / (double)RAND_MAX;
}
