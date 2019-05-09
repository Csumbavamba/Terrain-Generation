#pragma once
#include "Camera.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"
#include "Mesh_Cube.h"

#include <vector>
#include <string>

class CubeMap : public Mesh_Cube
{
public:
	CubeMap(GameObject * owner, std::vector <std::string> vectorOfFilePaths);
	virtual ~CubeMap();

	virtual void Initialise() override;
	virtual void Render(Camera * camera, GLuint program) override;

	virtual GLuint GetTexture();

private:
	GLuint texID;
};

