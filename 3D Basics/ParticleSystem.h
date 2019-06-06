#pragma once

#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

#include "Transform.h"

#include <vector>

class Camera;
class GameObject;
class Texture;

struct Particle
{
	glm::vec2 positon, velocity;
	glm::vec4 color;
	GLfloat life;

	Particle()
		: positon(0.0f), velocity(0.0f), color(1.0f), life(0.0f) { }
};

class ParticleSystem
{

public:
	ParticleSystem(GameObject* owner);
	virtual ~ParticleSystem();

	virtual void Render(Camera* camera, GLuint program);
	virtual void Update(float deltaTime, glm::vec2 offset = glm::vec2(0.0f, 0.0f));

// Functions
private:
	virtual void Initialise();
	GLuint GetFirstUnusedParticle();
	void RespawnParticle(Particle& particle, glm::vec2 offSet);

private:

	GameObject* owner = nullptr;
	GLuint VAO;
	Texture* texture = NULL;

	GLuint numberOfParticles;
	GLuint numberOfNewParticles;
	GLuint lastUsedParticle;

	GLuint particlesProgram;
	std::vector<Particle> particles;


	
};

