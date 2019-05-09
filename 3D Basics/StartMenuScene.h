#pragma once
#include "Scene.h"

class GameMenu;
class ShoutInputMenu;
class UI_Image;

class StartMenuScene :
	public Scene
{
public:
	StartMenuScene();
	virtual ~StartMenuScene() {};

private:
	
	UI_Image* backgroundImage = NULL;
	GameMenu * startMenu = NULL;
};

