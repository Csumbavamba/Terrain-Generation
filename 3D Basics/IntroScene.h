#pragma once
#include "Scene.h"
#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glew\glew.h" 
#include "Dependencies\freeglut\freeglut.h" 
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Mesh2D_Quad.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "GameObject.h"
#include "Input.h"
#include <iostream>
class IntroScene :public Scene
{
	Texture texture;

public:
	IntroScene();
	virtual ~IntroScene();

	virtual void Render(GLuint program) override;

	virtual void Update(float deltaTime) override;

	virtual void Initialise() override;

	void updateSprite();

private:
	bool hasBeenReleased = true;
	int frameIndex = 1;
	int animationIndex = 13;
	bool isVisible = true;
};

