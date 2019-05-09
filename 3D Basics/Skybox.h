#pragma once
#include "GameObject.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

class CubeMap;

class Skybox : public GameObject
{
public:
	Skybox(Camera * camera);
	~Skybox();

	virtual void Initialise() override;
	virtual void Render(GLuint program) override;
	virtual void Update();

	GLuint GetTextureID();

private:
	CubeMap * cubeMap = NULL;
};

