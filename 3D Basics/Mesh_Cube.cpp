#include "Mesh_Cube.h"



Mesh_Cube::Mesh_Cube(GameObject * owner)
{
	this->owner = owner;
}


Mesh_Cube::~Mesh_Cube()
{
}

void Mesh_Cube::Initialise()
{
	GLfloat vertices[] =
	{
		// Position				// Normal			// Texture
		// Front
		-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,	// 0
		-0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	0.0f, 1.0f,	// 1
		0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f,	// 2
		0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	1.0f, 0.0f,	// 3

		// Back
		-0.5f, 0.5f, -0.5f,		0.0f, 0.0f, -1.0f,	0.0f, 0.0f,	// 4
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, -1.0f,	0.0f, 1.0f,	// 5
		0.5f, -0.5f, -0.5f,		0.0f, 0.0f, -1.0f,	1.0f, 1.0f,	// 6
		0.5f, 0.5f, -0.5f,		0.0f, 0.0f, -1.0f,	1.0f, 0.0f,	// 7

		// Left
		-0.5f, 0.5f, -0.5f,		-1.0f, 0.0f, 0.0f,	0.0f, 0.0f,	// 8
		-0.5f, -0.5f, -0.5f,	-1.0f, 0.0f, 0.0f,	0.0f, 1.0f,	// 9
		-0.5f, -0.5f, 0.5f,		-1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	// 10
		-0.5f, 0.5f, 0.5f,		-1.0f, 0.0f, 0.0f,	1.0f, 0.0f,	// 11

		// Right
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f,	// 12
		0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	0.0f, 1.0f,	// 13
		0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	// 14
		0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,	// 15

		// Top
		-0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,	// 16
		-0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,	// 17
		0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,	// 18
		0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,	// 19

		// Bottom
		-0.5f, -0.5f, 0.5f,		0.0f, -1.0f, 0.0f,	0.0f, 0.0f,	// 20
		-0.5f, -0.5f, -0.5f,	0.0f, -1.0f, 0.0f,	0.0f, 1.0f,	// 21
		0.5f, -0.5f, -0.5f,		0.0f, -1.0f, 0.0f,	1.0f, 1.0f,	// 22
		0.5f, -0.5f, 0.5f,		0.0f, -1.0f, 0.0f,	1.0f, 0.0f,	// 23
	};

	GLuint indices[] =
	{
		0, 1, 2,	// Front
		0, 2, 3,	// Front

		7, 6, 5,	// Back
		7, 5, 4,	// Back

		8, 9, 10,	// Left
		8, 10, 11,	// Left

		12, 13, 14,	// Right
		12, 14, 15,	// Right

		16, 17, 18,	// Top
		16, 18, 19,	// Top

		20, 21, 22,	// Bottom
		20, 22, 23	// Bottom
	};

	indexCount = 36;

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
