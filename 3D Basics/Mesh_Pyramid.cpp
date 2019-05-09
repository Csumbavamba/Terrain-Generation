#include "Mesh_Pyramid.h"
#include "GameObject.h"


Mesh_Pyramid::Mesh_Pyramid(GameObject * owner)
{
	this->owner = owner;
}


Mesh_Pyramid::~Mesh_Pyramid()
{
}

void Mesh_Pyramid::Initialise()
{
	GLfloat vertices[] =
	{
		// Position				// Normal				// Tex Coords
		-0.5f, 0.0f, -0.5f,		0.0f, -1.0f, 0.0f,		0.0f, 1.0f,	// 0
		-0.5f, 0.0f,  0.5f,		0.0f, -1.0f, 0.0f,		0.0f, 0.0f,	// 1
		0.5f, 0.0f,  0.5f,		0.0f, -1.0f, 0.0f,		1.0f, 0.0f, // 2
		0.5f, 0.0f, -0.5f,		0.0f, -1.0f, 0.0f,		1.0f, 1.0f,	// 3

		// Side 1
		-0.5f, 0.0f, -0.5f,		0.0f, 0.5f, -0.5f,		1.0f, 1.0f,	// 04
		0.5f, 0.0f, -0.5f,		0.0f, 0.5f, -0.5f,		0.0f, 1.0f, // 05

		// Side 2
		0.5f, 0.0f, -0.5f,		0.5f, 0.5f, 0.0f,		1.0f, 1.0f, // 06
		0.5f, 0.0f,  0.5f,		0.5f, 0.5f, 0.0f,		0.0f, 1.0f,	// 07

		// Side 3
		0.5f, 0.0f, 0.5f,		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,	// 08
		-0.5f, 0.0f, 0.5f,		0.0f, 0.5f, 0.5f,		0.0f, 1.0f,	// 09

		// Side 4
		-0.5f, 0.0f,  0.5f,		-0.5f, 0.5f, 0.0f,		1.0f, 1.0f, // 10
		-0.5f, 0.0f, -0.5f,		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f, // 11

		// Top point
		0.0f, 0.5f, 0.0f,		0.0f, 1.0f, 0.0f,		0.5f, 0.0f	// 12

	};

	GLuint indices[] =
	{


		4, 12, 5,	// Side 1
		6, 12, 7,	// Side 2
		8, 12, 9,	// Side 3
		10, 12, 11,	// Side 4

		1, 0, 3,	// Base Triangle 1
		1, 3, 2		// Base triangle 2

	};

	indexCount = 18;

	// VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(vertices),
		vertices,
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
		sizeof(indices),
		indices,
		GL_STATIC_DRAW
	);
}
