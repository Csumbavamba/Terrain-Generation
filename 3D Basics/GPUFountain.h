#pragma once
#include "GameObject.h"

class ParticleSystem;
class Terrain;

class GPUFountain :
	public GameObject
{
public:
	GPUFountain(Camera* mainCamera);
	virtual ~GPUFountain();

	virtual void Initialise() override;
	virtual void Render(GLuint program) override;
	virtual void Update(float deltaTime) override;

	void SetTerrain(Terrain* terrain);

private:

	Terrain* terrain = NULL;
	ParticleSystem* particleSystem = nullptr;
};

