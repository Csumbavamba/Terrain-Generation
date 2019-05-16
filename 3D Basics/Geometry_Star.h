#pragma once

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

class GameObject;
class Camera;


class Geometry_Star
{
public:
	Geometry_Star(GameObject * owner);
	virtual ~Geometry_Star();

	virtual void Initialise();
	virtual void Render(Camera* camera, GLuint program);
	virtual void Update();

protected:
	GLuint VBO;
	GLuint VAO;
	GLuint EBO;

	// Calculations for rendering and updating
	void CalculateModelMatrix();

	glm::mat4 PVM;
	glm::mat4 modelMatrix;
	glm::vec3 CameraPosition;

	GameObject* owner = NULL;
};

