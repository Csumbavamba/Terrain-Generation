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
	ParticleSystem(GameObject* owner);
	virtual ~ParticleSystem();

	virtual void Initialise();
	virtual void Render(Camera* camera, GLuint program);
	virtual void Update(float deltaTime, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
	GameObject* GetOwner() const;

// Functions
private:	
	
	void PopulateQuadPositions(Camera* camera, glm::vec3& OUT quad1, glm::vec3& OUT quad2);

	GLuint GetFirstUnusedParticle();
	void RespawnParticle(Particle& particle, glm::vec2 offSet);

private:

	GameObject* owner = nullptr;
	GLuint VAO, VBO;
	Texture* texture = NULL;

	GLuint numberOfParticles;
	GLuint numberOfNewParticles;
	GLuint lastUsedParticle;

	GLuint particlesProgram;
	std::vector<Particle*> particles;
	std::vector<glm::vec3> particlePositions;


	
};

