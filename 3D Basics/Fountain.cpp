#include "Fountain.h"

#include "ParticleSystem.h"

Fountain::Fountain(Camera* mainCamera)
{
	this->camera = mainCamera;

	particleSystem = new ParticleSystem(this, false);
}

Fountain::~Fountain()
{
	delete particleSystem;
	particleSystem = nullptr;
}

void Fountain::Initialise()
{
	particleSystem->Initialise();
}

void Fountain::Render(GLuint program)
{
	particleSystem->Render(camera, NULL);
}

void Fountain::Update(float deltaTime)
{
	particleSystem->Update(deltaTime);
}
