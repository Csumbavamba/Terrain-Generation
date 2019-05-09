#pragma once
#include "GameObject.h"

class UI_Button;
class Camera;
class AudioSound;
class ShoutInputMenu;

class GameMenu :
	public GameObject
{
public:
	GameMenu(Camera * mainCamera);
	virtual ~GameMenu();
	
	virtual void Render(GLuint program) override;
	virtual void Update(float deltaTime) override;
	void Reset();

	void ProcessKeyboardNavigation();
	void ProcessKeyboardClicks();
	void ChangeSelectedButton(int change);
	void ActOnMenuChoice();
	void ClickButton();

private:

	UI_Button * buttons[2];
	int buttonSelected;
	
	UI_Button * startButton = NULL;
	UI_Button * quitButton = NULL;

	AudioSound * clickSound = NULL;
	AudioSound * swapSound = NULL;
};

