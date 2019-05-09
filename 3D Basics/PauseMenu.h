#pragma once
#include "GameObject.h"

class UI_Button;
class AudioSound;
class UI_Image;

class PauseMenu :
	public GameObject
{
public:
	PauseMenu(Camera * mainCamera);
	virtual ~PauseMenu();

	virtual void Render(GLuint program) override;
	virtual void Update(float deltaTime) override;

	void Reset();

	void ProcessKeyboardNavigation();
	void ProcessKeyboardClicks();
	void ChangeSelectedButton(int change);
	void ActOnMenuChoice();
	void ClickButton();

private:

	int buttonSelected;
	UI_Button * buttons[2];
	UI_Button * returnButton = NULL;
	UI_Button * mainMenuButton = NULL;

	AudioSound * clickSound = NULL;
	AudioSound * swapSound = NULL;
	UI_Image * backgroundImage = NULL;
};

