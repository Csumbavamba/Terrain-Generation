#pragma once
#include "GameObject.h"

class Mesh2D_Quad;

class UI_Image : public GameObject
{
public:
	UI_Image(Camera * camera, std::string imagePath, glm::vec2 sizeInPixels);
	virtual ~UI_Image();

	virtual void Render(GLuint program) override;
	void Update(float deltaTime);


private:
	virtual void Initialise() override {};

	GLuint imageProgram;
	Mesh2D_Quad * backgroundImage = NULL;
};

