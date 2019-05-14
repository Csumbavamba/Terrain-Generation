#include "StartMenuScene.h"

#include "GameMenu.h"
#include "Camera.h"
#include "UI_Image.h"
#include "Utility.h"


StartMenuScene::StartMenuScene()
{
	startMenu = new GameMenu(mainCamera);
	backgroundImage = new UI_Image(mainCamera, "Sprites/DwarfBackground2.jpg", Utility::GetScreenSize() / mainCamera->GetFieldOfView());


	sceneName = "StartMenuScene"; // TODO Create method to get this from file

	gameObjects.push_back(backgroundImage);
	gameObjects.push_back(startMenu);
}




