#include "ParticleSystem.h"

#include "ShaderLoader.h"
#include "GameObject.h"
#include "Camera.h"
#include "Texture.h"
#include "Particle.h"

ParticleSystem::ParticleSystem(GameObject* owner)
{
	this->owner = owner;

	// Setup Particle system
	numberOfParticles = 500;
	numberOfNewParticles = 2;
	lastUsedParticle = 0;

	// Create Texture
	texture = new Texture();
	texture->SetTexturePath("Sprites/fireBall.png");
	texture->Initialise();

	// Create the shader program
	particlesProgram = ShaderLoader::GetInstance()->CreateProgram("Shaders/ParticleVertex.vs", "Shaders/ParticleGeometry.gs" ,"Shaders/ParticleFragment.fs");

	// Create Particles and store them
	for (GLuint i = 0; i < numberOfParticles; ++i)
	{
		// Push particle positions
		particlePositions.push_back(glm::vec3(0.0f, 0.0f, 0.0f));

		// Create particles
		Particle* particle = new Particle(this, i);

		particles.push_back(particle);
	}
}

ParticleSystem::~ParticleSystem()
{
	delete texture;
	texture = nullptr;

	// Delete each particle
	for (int i = 0; i < particles.size(); ++i)
	{
		delete particles[i];
		particles[i] = nullptr;
	}

	// Clear the particle containers
	particles.clear();
	particlePositions.clear();
}

void ParticleSystem::Initialise()
{
	// Set up mesh and attribute properties
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);
	
	// Fill the mesh buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * particlePositions.size(), &particlePositions[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	
	glBindVertexArray(0);
}



void ParticleSystem::Render(Camera* camera, GLuint program)
{
	// Additive blending to give a glow effect
	glEnable(GL_BLEND); // This Might not needed
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);

	// Get View and Projection matrix
	glm::mat4 PV = camera->GetPV();

	/// Create Particle Quad details
	glm::vec3 quad1, quad2;
	PopulateQuadPositions(camera, quad1, quad2);

	// Utilise the particle program
	glUseProgram(particlesProgram);

	// Add texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->GetTexture());
	glUniform1i(glGetUniformLocation(particlesProgram, "tex"), 0);

	// Send in quads to vertex shader
	glUniform3f(glGetUniformLocation(particlesProgram, "quad1"), quad1.x, quad1.y, quad1.z);
	glUniform3f(glGetUniformLocation(particlesProgram, "quad2"), quad2.x, quad2.y, quad2.z);

	// Send in the PV
	GLuint PVLoc = glGetUniformLocation(particlesProgram, "PV");
	glUniformMatrix4fv(PVLoc, 1, GL_FALSE, glm::value_ptr(PV));

	glBindBuffer(GL_ARRAY_BUFFER, VBO); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * particlePositions.size(), &particlePositions[0], GL_STATIC_DRAW);
	glBindVertexArray(this->VAO);

	glDrawArrays(GL_POINTS, 0, numberOfParticles);
	glBindVertexArray(0);

	// Reset Blending to standard blend
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_TRUE); 
	//glDisable(GL_BLEND); // TODO - this might need removal
}

void ParticleSystem::Update(float deltaTime, glm::vec2 offSet)
{
	for (int i = 0; i < numberOfParticles; i++) 
	{ 
		particles[i]->Update(deltaTime); 
		particlePositions[i] = particles[i]->GetPosition(); 
	}
}

void ParticleSystem::PopulateQuadPositions(Camera* camera, glm::vec3& OUT quad1, glm::vec3& OUT quad2)
{
	// Get Unit Look Direction
	glm::vec3 lookDirection = camera->GetCameraLookDirection();
	lookDirection = glm::normalize(lookDirection);

	quad1 = glm::cross(lookDirection, camera->GetCameraUpDirection());
	quad1 = glm::normalize(quad1);

	quad2 = glm::cross(lookDirection, quad1);
	quad2 = glm::normalize(quad2);
}

GameObject* ParticleSystem::GetOwner() const
{
	return owner;
}
