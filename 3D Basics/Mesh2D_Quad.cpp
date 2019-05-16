#include "Mesh2D_Quad.h"
#include "Texture.h"
#include "ShaderLoader.h"
#include "Animation2D.h"
#include <iostream>

Mesh2D_Quad::Mesh2D_Quad(GameObject * owner)
{
	this->owner = owner;
}


Mesh2D_Quad::~Mesh2D_Quad()
{
}

void Mesh2D_Quad::Initialise()
{

	GLfloat quad[] = 
	{
		// position				// color			// Tex Coords
		-0.5f,  0.0f,  0.5f,	0.0f, 1.0f, 1.0f,	0.0f, 0.0f,		// Top Left
		+0.5f,  0.0f,  0.5f,	0.0f, 1.0f, 1.0f,	1.0f, 0.0f,		// Top Right
		-0.5f,  0.0f, -0.5f,	0.0f, 1.0f, 1.0f,	0.0f, 1.0f,		// Bottom Left
		+0.5f,  0.0f, -0.5f,	0.0f, 1.0f, 1.0f,	1.0f, 1.0f		// Bottom Right
	};

	GLuint indicies[] =
	{
		0, 1, 2,	// Top Left 0, 2, 1 -- > FOR 3D
		3, 2, 1		// Bottom Right 2, 3, 1 --> FOR 3D

	};

	indexCount = 6;

	// VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

	// Binding Vertext attributes
	glVertexAttribPointer(0, 3,	GL_FLOAT, GL_FALSE,	8 * sizeof(GLfloat), (GLvoid*)(0));
	glVertexAttribPointer(1, 3,	GL_FLOAT, GL_FALSE,	8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 2,	GL_FLOAT, GL_FALSE,	8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// EBO
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies),	indicies, GL_STATIC_DRAW);
}

void Mesh2D_Quad::Animate()
{
	GLuint VBO;
	GLuint EBO;

	GLfloat quad[] = {
		// Positions               // Colors             // Tex Coords
		-0.5f,  0.0f,  0.5f,      0.0f, 1.0f, 1.0f,      animation->GetTextureX(), animation->GetTextureY(),                                                                // Top Left
		+0.5f,  0.0f,  0.5f,      0.0f, 1.0f, 1.0f,      animation->GetTextureX() + animation->GetTextureWidth(), animation->GetTextureY(),                                // Top Right 
		-0.5f,  0.0f, -0.5f,      0.0f, 1.0f, 1.0f,      animation->GetTextureX(), animation->GetTextureY() + animation->GetTextureHeight(),                                 // Bottom Left
		+0.5f,  0.0f, -0.5f,      0.0f, 1.0f, 1.0f,	     animation->GetTextureX() + animation->GetTextureWidth(), animation->GetTextureY() + animation->GetTextureHeight()                                                           // Bottom Right                             
	};

	std::cout << animation->GetTextureX() << std::endl;
	std::cout << animation->GetTextureY() << std::endl;
	std::cout << animation->GetTextureWidth() << std::endl;
	std::cout << animation->GetTextureHeight() << std::endl;

	GLuint indicies[] =
	{
		0, 1, 2,  //Right Triangle
		3, 2, 1   //Left Triangle

	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(quad),
		quad,
		GL_STATIC_DRAW
	);

	// Binding Vertext attributes
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(0)
	);

	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat))
	);

	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(6 * sizeof(GLfloat))
	);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// EBO
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		sizeof(indicies),
		indicies,
		GL_STATIC_DRAW
	);
}


void Mesh2D_Quad::PlayAnimation(Animation2D* animation)
{
	if (this->animation != animation)
	{
		this->animation = animation;
	}

	if (animation != NULL)
	{
		Animate();
	}
}




