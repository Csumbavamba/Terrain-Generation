#pragma once

#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

#include "Transform.h"

#include <vector>

class Camera;
class GameObject;
class Texture;
class Particle;


class ParticleSystem
{

public:
	ParticleSystem(GameObject* owner, bool onGPU);
	virtual ~ParticleSystem();

	virtual void Initialise();
	virtual void Render(Camera* camera, GLuint program);
	virtual void Update(float deltaTime, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
	GameObject* GetOwner() const;

// Functions
private:	
	
	void PopulateQuadPositions(Camera* camera, glm::vec3& OUT quad1, glm::vec3& OUT quad2);

private:

	GameObject* owner = nullptr;
	GLuint VAO, VBO;
	Texture* texture = NULL;

	GLuint numberOfParticles;
	GLuint particlesProgram;

	std::vector<Particle*> particles;
	std::vector<glm::vec3> particlePositions;

	/// GPU calculations
	bool onGPU;
	std::vector<glm::vec4> initialPosition;
	std::vector<glm::vec4> initialVelocity;

	GLuint positionVBO, velocityVBO, initialVelocityVBO, particleVAO; // Particle VAO is not used, but needed to avoid errors
	GLuint computeProgram, GPUParticlesProgram;


	
};

