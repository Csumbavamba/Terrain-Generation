#include "Tess2D_Quad.h"
#include "Camera.h"
#include "GameObject.h"

Tess2D_Quad::Tess2D_Quad(GameObject* owner)
{
	this->owner = owner;
	distanceToCamera = 0.0f;
}


void Tess2D_Quad::Initialise()
{
	GLfloat points[] = {
		-1.0f, -1.0f, 0.0f,	// Bottom left
		-1.0, 1.0, 0.0f,	// Top Left
		1.0f, 1.0f, 0.0f, 	// Top right
		1.0f, -1.0f, 0.0f};	// Bottom right
		
		
	
	glPatchParameteri(GL_PATCH_VERTICES, 4); //comment for tri patch
	
	glGenVertexArrays(1, &VAO); 
	glBindVertexArray(VAO); 

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0); 
	
	glBindVertexArray(0);
}

void Tess2D_Quad::Render(Camera* camera, GLuint program)
{
	glUseProgram(program);

	PVM = camera->GetPV() * modelMatrix;

	distanceToCamera = glm::distance(camera->GetCameraPosition(), owner->transform.position);

	// Provide PVM
	GLuint PVMLoc = glGetUniformLocation(program, "PVM");
	glUniformMatrix4fv(PVMLoc, 1, GL_FALSE, glm::value_ptr(PVM));

	// LOD
	GLuint LODLoc = glGetUniformLocation(program, "LOD");
	glUniform1f(LODLoc, distanceToCamera);

	glBindVertexArray(VAO);
	glDrawArrays(GL_PATCHES, 0, 4); 
	glBindVertexArray(0);
}
