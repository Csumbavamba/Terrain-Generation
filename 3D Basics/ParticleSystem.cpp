#include "ParticleSystem.h"

#include "ShaderLoader.h"
#include "GameObject.h"
#include "Camera.h"
#include "Texture.h"

ParticleSystem::ParticleSystem(GameObject* owner)
{
	this->owner = owner;

	numberOfParticles = 4000;
	numberOfNewParticles = 2;
	lastUsedParticle = 0;

	// Create Texture
	texture = new Texture();
	texture->SetTexturePath("Sprites/Rayman.jpg");
	texture->Initialise();

	// Create the shader program
	particlesProgram = ShaderLoader::GetInstance()->CreateProgram("Shaders/ParticleVertex.vs", "Shaders/" ,"Shaders/ParticleFragment.fs"); // TODO add geometry shader

	// Populate particles
	for (GLuint i = 0; i < numberOfParticles; ++i)
	{
		particlePositions.push_back(glm::vec3());
	}



	Initialise();
}

ParticleSystem::~ParticleSystem()
{
	delete texture;
	texture = nullptr;
}

void ParticleSystem::Initialise()
{
	// Set up mesh and attribute properties
	GLuint VBO;
	GLuint EBO;

	GLfloat particleQuad[] = {
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f
	};

	GLuint indicies[] =
	{
		0, 2, 1,
		2, 3, 1	

	};

	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	glGenBuffers(1, &VBO);
	
	// Fill the mesh buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particleQuad), particleQuad, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// EBO
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);
	
	glBindVertexArray(0);
}

void ParticleSystem::Render(Camera* camera, GLuint program)
{
	// Additive blending to give a glow effect
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glUseProgram(particlesProgram);

	for (Particle particle : particles)
	{
		// Only draw if they are alive
		if (particle.life > 0.0f)
		{
			// Add texture
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture->GetTexture());
			glUniform1i(glGetUniformLocation(program, "tex"), 0);

			glm::mat4 projection = camera->GetProjectionMatrix();

			// Send in the projection
			GLuint projectonLoc = glGetUniformLocation(program, "projection");
			glUniformMatrix4fv(projectonLoc, 1, GL_FALSE, glm::value_ptr(projection));

			// Send in the offset
			GLuint offSetLoc = glGetUniformLocation(program, "offSet");
			glUniform2fv(offSetLoc, 1, glm::value_ptr(particle.positon));

			// Send in the color
			GLuint colorLoc = glGetUniformLocation(program, "color");
			glUniform4fv(colorLoc, 1, glm::value_ptr(particle.color));

			glBindVertexArray(this->VAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
		}
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleSystem::Update(float deltaTime, glm::vec2 offSet)
{
	// Spawn New Particles
	for (GLuint i = 0; i < numberOfNewParticles; ++i)
	{
		int unusedParticles = GetFirstUnusedParticle();
		RespawnParticle(particles[unusedParticles], offSet);
	}

	// Update Current Particles
	for (GLuint i = 0; i < numberOfParticles; ++i)
	{
		Particle& particle = particles[i];

		// Decrease particle lifetme
		particle.life -= deltaTime;

		// if the particle is still alive
		if (particle.life > 0.0f)
		{
			// Move Particle with it's velocity
			particle.positon -= particle.velocity * deltaTime;

			// Fade particle out
			particle.color.a -= deltaTime * 2.5f;
		}
	}
}

GameObject* ParticleSystem::GetOwner() const
{
	return owner;
}


GLuint ParticleSystem::GetFirstUnusedParticle()
{
	// Search from the last used particle
	for (GLuint i = lastUsedParticle; i < numberOfParticles; ++i)
	{
		// Find the first dead particle
		if (particles[i].life <= 0.0f)
		{
			lastUsedParticle = i;
			return i;
		}
	}

	// If it's not found do a linear search
	for (GLuint i = 0; i < lastUsedParticle; ++i)
	{
		// Find the first dead particle
		if (particles[i].life <= 0.0f)
		{
			lastUsedParticle = i;
			return i;
		}
	}

	lastUsedParticle = 0;
	return 0;
}

void ParticleSystem::RespawnParticle(Particle& particle, glm::vec2 offSet)
{
	GLfloat random = ((rand() % 100) - 50) / 10.0f;
	GLfloat randomColor = 0.5 + ((rand() % 100) / 100.0f);

	// Randomize the spawn positon
	particle.positon.x = owner->transform.position.x + random;	// TODO add offset to it
	particle.positon.y = owner->transform.position.y + random;
	particle.color = glm::vec4(randomColor, randomColor, randomColor, 1.0f);
	particle.life = 1.0f;
	particle.velocity = glm::vec2(0.0f, +1.0f);
}
