#include "Scene.h"

#include "GameObject.h"
#include "Camera.h"


Scene::Scene()
{
	this->mainCamera = new Camera(PERSPECTIVE);
}

Scene::~Scene()
{
	delete mainCamera;
	mainCamera = NULL;

	// Delete every GameObject
	for (GameObject * gameObject : gameObjects)
	{
		delete gameObject;
		gameObject = NULL;
	}
}

void Scene::Initialise()
{
	mainCamera->Initialise();

	// Initialise all GameObjects
	for (GameObject * gameObject : gameObjects)
	{
		gameObject->Initialise();
	}
}

void Scene::Render(GLuint program)
{
	// Render all GameObjects
	for (GameObject * gameObject : gameObjects)
	{
		// Only render if it's active
		if (gameObject->IsActive())
		{
			gameObject->Render(program);
		}
		
	}
}

void Scene::Update(float deltaTime)
{
	mainCamera->Update(deltaTime);

	// Render all GameObjects
	for (GameObject * gameObject : gameObjects)
	{
		// Only Update them if they are active
		if (gameObject->IsActive())
		{
			gameObject->Update(deltaTime);
		}
	}
}

bool Scene::IsActiveScene() const
{
	return isActiveScene;
}

void Scene::SetIsActiveScene(bool isActiveScene)
{
	this->isActiveScene = isActiveScene;
}

std::string Scene::GetSceneName() const
{
	return sceneName;
}
