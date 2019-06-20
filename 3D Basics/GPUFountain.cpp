#include "GPUFountain.h"
#include "ParticleSystem.h"
#include "Terrain.h"

GPUFountain::GPUFountain(Camera* mainCamera)
{
	this->camera = mainCamera;

	particleSystem = new ParticleSystem(this, true);
}

GPUFountain::~GPUFountain()
{
	delete particleSystem;
	particleSystem = nullptr;
}

void GPUFountain::Initialise()
{
	transform.position.x = 10.0f;
	transform.position.y = terrain->GetHeightAt(transform.position.x, transform.position.z) + transform.scale.y * 5.0f;
	

	particleSystem->Initialise();
}

void GPUFountain::Render(GLuint program)
{
	particleSystem->Render(camera, NULL);
}

void GPUFountain::Update(float deltaTime)
{
	particleSystem->Update(deltaTime);
}

void GPUFountain::SetTerrain(Terrain* terrain)
{
	this->terrain = terrain;
}
