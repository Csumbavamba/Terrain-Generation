#pragma once

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

class GameObject;
class Texture;
class Camera;

class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	virtual void Initialise() = 0;

	virtual void Render(Camera * camera, GLuint program);

	virtual void ReflectionRender(Camera * camera, GLuint program, GLuint textureID);

	virtual void Update();

	Texture * GetTexture() const;

protected:
	GLuint VBO;
	GLuint VAO;
	GLuint EBO;

	// Calculations for rendering and updating
	void CalculateModelMatrix();
	glm::mat4 PVM;
	glm::mat4 modelMatrix;


	glm::vec3 CameraPosition;


	GameObject * owner = NULL;
	Texture * texture = NULL;

	int indexCount;
};

