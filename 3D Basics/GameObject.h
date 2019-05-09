#pragma once

#include <string>

#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

#include "Transform.h"

class Camera;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialise() {};
	virtual void Render(GLuint program) {};
	virtual void Update(float deltaTime) {};

	void SetCamera(Camera * camera);
	
	virtual void SetActive(bool isActive);
	virtual bool IsActive() const;

	Transform transform;

protected:
	Camera * camera = NULL;
	bool isActive;
	
};

