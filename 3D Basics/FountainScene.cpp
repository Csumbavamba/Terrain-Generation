#include "FountainScene.h"
#include "Fountain.h"
#include "Input.h"

FountainScene::FountainScene()
{
	fountain = new Fountain(mainCamera);

	gameObjects.push_back(fountain);
}

void FountainScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);

	if (Input::GetKeyState('q') == DOWN)
	{
		glPolygonMode(GL_FRONT, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT, GL_FILL);
	}
}


