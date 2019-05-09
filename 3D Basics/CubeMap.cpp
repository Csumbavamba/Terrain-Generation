

#include "CubeMap.h"
#include "Texture.h"
#include "Camera.h"
#include "GameObject.h"



CubeMap::CubeMap(GameObject * owner, std::vector <std::string> vectorOfFilePaths)
{
	int width, height, channels;
	unsigned char* image;
	this->owner = owner;

	

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texID);

	for (GLuint i = 0; i < 6; i++)
	{
		image = SOIL_load_image(vectorOfFilePaths.at(i).c_str(),
			&width,
			&height,
			&channels,
			SOIL_LOAD_RGBA);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0,
			GL_RGBA,
			width,
			height,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			image);
		SOIL_free_image_data(image);

	}



	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}


void CubeMap::Initialise()
{
	GLfloat vertices[] =
	{

		// Position			
		// Front
		-0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,

		// Back
		-0.5f, 0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,

		// Left
		-0.5f, 0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,

		// Right
		0.5f, 0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,

		// Top
		-0.5f, 0.5f, -0.5f,
		-0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, -0.5f,

		// Bottom
		-0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,
	};

	GLuint indices[] =
	{
		0,   2,  1, 	// Front
		0,   3,  2, 	// Front

		7,   5,  6, 	// Back
		7,   4,  5, 	// Back

		8,  10,  9, 	// Left
		8,  11,  10,	// Left

		12, 14,	 13,// Right
		12, 15,	 14,// Right

		16, 18,	 17,// Top
		16, 19,	 18,// Top

		20, 22,	 21,// Bottom
		20, 23,	 22,// Bottom
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

	// Binding Vertex attributes
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(GLfloat),
		(GLvoid*)(0)
	);

	glEnableVertexAttribArray(0);

	// EBO
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		sizeof(indices),
		indices,
		GL_STATIC_DRAW
	);

	owner->transform.scale *= 2000;

}

void CubeMap::Render(Camera * camera, GLuint program)
{
	glUseProgram(program);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	// Add texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texID);
	glUniform1i(glGetUniformLocation(program, "cubeSampler"), 0);

	PVM = camera->GetPV() * modelMatrix;

	// Provide PVM
	GLuint PVMLoc = glGetUniformLocation(program, "PVM");
	glUniformMatrix4fv(PVMLoc, 1, GL_FALSE, glm::value_ptr(PVM));

	// Draw Object
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}


CubeMap::~CubeMap()
{
}

GLuint CubeMap::GetTexture()
{
	return texID;
}
