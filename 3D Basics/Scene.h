#pragma once

#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

#include <string>
#include <vector>
#include <algorithm>

class GameObject;
class Camera;


class Scene
{
public:

	Scene();
	virtual~Scene();

	virtual void Initialise();
	virtual void Render(GLuint program);
	virtual void Update(float deltaTime);
	virtual void Reset() {};

	bool IsActiveScene() const;
	void SetIsActiveScene(bool isActiveScene);
	
	std::string GetSceneName() const;

protected:

	bool isActiveScene = false;
	Camera * mainCamera = NULL;

	std::string sceneName = ""; // TODO Create method to get this by code (without the .cpp or .h
	std::vector<GameObject*> gameObjects;

};

