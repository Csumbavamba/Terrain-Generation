#include "ParticleSystem.h"

#include "ShaderLoader.h"
#include "GameObject.h"
#include "Camera.h"
#include "Texture.h"
#include "Particle.h"
#include "Time.h"

#define NUM_PARTICLES 128 * 500

ParticleSystem::ParticleSystem(GameObject* owner, bool onGPU)
{
	this->owner = owner;
	this->onGPU = onGPU;

	// Setup Particle system
	numberOfParticles = NUM_PARTICLES;

	// If done by CPU
	if (!onGPU)
	{
		numberOfParticles = 500;

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
	

	// Create Texture
	texture = new Texture();
	texture->SetTexturePath("Sprites/fireBall.png");
	texture->Initialise();

	// Create the shader program
	particlesProgram = ShaderLoader::GetInstance()->CreateProgram("Shaders/ParticleVertex.vs", "Shaders/ParticleGeometry.gs" ,"Shaders/ParticleFragment.fs");
	GPUParticlesProgram = ShaderLoader::GetInstance()->CreateProgram("Shaders/ParticleVertexGPU.vs", "Shaders/ParticleFragmentGPU.fs");

	
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
	if (!onGPU)
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
	else
	{
		for (int i = 0; i < NUM_PARTICLES; ++i)
		{
			// Populate initial positions
			initialPosition.push_back(glm::vec4(
				0.0f,
				0.0f,
				0.0f,
				Particle::RandomFloat() + 0.125f));

			// Populate initial velocities
			initialVelocity.push_back(glm::vec4(
				0.25f * sin(i * Time::GetDeltaTime()) + 0.25f * Particle::RandomFloat() - 0.125f,
				1.5f + 0.25f * Particle::RandomFloat() - 0.125f,
				0.25f * cos(i * Time::GetDeltaTime()) + 0.25f * Particle::RandomFloat() - 0.125f,
				Particle::RandomFloat() + 0.125f));
		}

		/// Store Position Data
		// Generate Position Storage
		glGenBuffers(1, &positionVBO);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, positionVBO);

		// Generate Initial Position Storage
		glBufferData(GL_SHADER_STORAGE_BUFFER, initialPosition.size() * sizeof(glm::vec4), &initialPosition[0], GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, positionVBO);

		/// Store Velocity Data
		// Generate Velocity Storage
		glGenBuffers(1, &velocityVBO);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, velocityVBO);
		glBufferData(GL_SHADER_STORAGE_BUFFER, initialVelocity.size() * sizeof(glm::vec4), &initialVelocity[0], GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, velocityVBO);

		// Generate Initial Velocity Storage
		glGenBuffers(1, &initialVelocityVBO);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, initialVelocityVBO);
		glBufferData(GL_SHADER_STORAGE_BUFFER, initialVelocity.size() * sizeof(glm::vec4), &initialVelocity[0], GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, initialVelocityVBO);


		/// Bind the placeholder VAO
		glGenVertexArrays(1, &particleVAO);
		glBindVertexArray(particleVAO);

		glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, NULL, 0);
		glEnableVertexAttribArray(0);

		// Unbind Bufers
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	
}



void ParticleSystem::Render(Camera* camera, GLuint program)
{
	
	// Additive blending to give a glow effect
	glEnable(GL_BLEND); // This Might not needed
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);

	// Get View and Projection matrix
	glm::mat4 PV = camera->GetPV();

	// GPU RENDERING
	if (onGPU)
	{
		// Do GPU calculation here
		glUseProgram(computeProgram);

		glDispatchCompute(NUM_PARTICLES / 128, 1, 1);

		// Sync wait for completion
		glMemoryBarrier(GL_ALL_BARRIER_BITS);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

		glUseProgram(GPUParticlesProgram);

		// Send in the PV
		GLuint PVLoc = glGetUniformLocation(GPUParticlesProgram, "PV");
		glUniformMatrix4fv(PVLoc, 1, GL_FALSE, glm::value_ptr(PV));

		GLuint DELTALoc = glGetUniformLocation(GPUParticlesProgram, "deltaTime");
		glUniform1f(DELTALoc, Time::GetDeltaTime());

		// Bind Position of buffer as GL_ARRAY_BUFFER
		glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, NULL, 0);
		glEnableVertexAttribArray(0);

		// Render
		glDrawArrays(GL_POINTS, 0, NUM_PARTICLES);

		// Clean Stuff
		glDisableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glUseProgram(0);

	}
	// CPU RENDERING
	else
	{
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
	}
	

	// Reset Blending to standard blend
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_TRUE); 
	//glDisable(GL_BLEND); // TODO - this might need removal
}

void ParticleSystem::Update(float deltaTime, glm::vec2 offSet)
{
	if (!onGPU)
	{
		for (int i = 0; i < numberOfParticles; i++)
		{
			particles[i]->Update(deltaTime);
			particlePositions[i] = particles[i]->GetPosition();
		}
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
