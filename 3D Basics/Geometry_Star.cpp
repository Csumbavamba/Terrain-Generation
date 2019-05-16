#include "Geometry_Star.h"
#include "GameObject.h"
#include "Camera.h"


Geometry_Star::Geometry_Star(GameObject * owner)
{
	this->owner = owner;

	VBO = NULL;
	VAO = NULL;
	EBO = NULL;
}


Geometry_Star::~Geometry_Star()
{
}

void Geometry_Star::Initialise()
{
	GLfloat points[] = { 0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,}; //passing in 1 point 

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO); 

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0); 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void Geometry_Star::Render(Camera* camera, GLuint program)
{
	glUseProgram(program);

	PVM = camera->GetPV() * modelMatrix;

	GLint PVMLoc = glGetUniformLocation(program, "PVM"); 
	glUniformMatrix4fv(PVMLoc, 1, GL_FALSE, glm::value_ptr(PVM));

	glBindVertexArray(VAO); 
	glDrawArrays(GL_POINTS, 0, 1); 
	glBindVertexArray(0);
}

void Geometry_Star::Update()
{
	CalculateModelMatrix();
}

void Geometry_Star::CalculateModelMatrix()
{
	glm::mat4 translationMatrix = glm::translate(glm::mat4(), owner->transform.position);
	glm::mat4 rotationmatrix = owner->transform.CalculateRotationMatrix();
	glm::mat4 scalingMatrix = glm::scale(glm::mat4(), owner->transform.scale); // TODO add scaling

	// Model																																					
	modelMatrix = translationMatrix * rotationmatrix * scalingMatrix;
}
