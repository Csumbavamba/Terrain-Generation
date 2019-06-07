#pragma once
#include "GameObject.h"

class ParticleSystem;

class Fountain :
	public GameObject
{
public:
	Fountain(Camera* mainCamera);
	virtual ~Fountain();

	virtual void Initialise() override;
	virtual void Render(GLuint program) override;
	virtual void Update(float deltaTime) override;

private:

	ParticleSystem* particleSystem = nullptr;

};

