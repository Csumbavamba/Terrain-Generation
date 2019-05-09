#include "PauseMenu.h"

#include "UI_Button.h"
#include "AudioSound.h"
#include "UI_Image.h"
#include "Utility.h"
#include "Input.h"
#include "SceneManager.h"
#include "Scene.h"


PauseMenu::PauseMenu(Camera * mainCamera)
{
	this->camera = mainCamera;

	// TODO Set Position
	returnButton = new UI_Button("RETURN", glm::vec2(0.0f, 100.0f));
	mainMenuButton = new UI_Button("MAIN MENU", glm::vec2(0.0f, -100.0f));

	backgroundImage = new UI_Image(mainCamera, "Sprites/DwarfBackground2.jpg", Utility::GetScreenSize());
	clickSound = new AudioSound("Audio/Click.wav", DEFAULT);
	swapSound = new AudioSound("Audio/Click2.wav", DEFAULT);

	// Return is Selected by default
	returnButton->SetIsSelected(true);
	buttonSelected = 0;

	buttons[0] = returnButton;
	buttons[1] = mainMenuButton;
}


PauseMenu::~PauseMenu()
{
	delete returnButton;
	returnButton = NULL;

	delete mainMenuButton;
	mainMenuButton = NULL;

	delete backgroundImage;
	backgroundImage = NULL;
	
	delete clickSound;
	clickSound = NULL;

	delete swapSound;
	swapSound = NULL;
}

void PauseMenu::Render(GLuint program)
{
	if (isActive)
	{
		backgroundImage->Render(program);
		returnButton->Render(program);
		mainMenuButton->Render(program);
	}
}

void PauseMenu::Update(float deltaTime)
{
	if (isActive)
	{
		backgroundImage->Update(deltaTime);
		returnButton->Update(deltaTime);
		mainMenuButton->Update(deltaTime);

		// Process keyboard events
		ProcessKeyboardNavigation();
		ProcessKeyboardClicks();
	}
}

void PauseMenu::Reset()
{
	isActive = false;
	returnButton->Reset();
	mainMenuButton->Reset();

	// Return is Selected by default
	returnButton->SetIsSelected(true);
	buttonSelected = 0;
}

void PauseMenu::ProcessKeyboardNavigation()
{
	// If user clicks down, increase the selected numbers
	if (Input::GetSpecialKeyState(GLUT_KEY_DOWN) == DOWN_FIRST)
	{
		ChangeSelectedButton(+1);
	}
	// If user clicks up
	else if (Input::GetSpecialKeyState(GLUT_KEY_UP) == DOWN_FIRST)
	{
		ChangeSelectedButton(-1);
	}
}

void PauseMenu::ProcessKeyboardClicks()
{
	// If Enter is pressed
	if (Input::GetKeyState(13) == DOWN_FIRST)
	{
		ClickButton();
		ActOnMenuChoice();
	}
}

void PauseMenu::ChangeSelectedButton(int change)
{
	// Deselect the previous button
	buttons[buttonSelected]->SetIsSelected(false);

	buttonSelected += change;

	// Play click sound
	swapSound->PlaySound();

	// Lerp around if neccessary
	if (buttonSelected > 1)
	{
		buttonSelected = 0;
	}
	else if (buttonSelected < 0)
	{
		buttonSelected = 1;
	}

	// Select the new button
	buttons[buttonSelected]->SetIsSelected(true);
}

void PauseMenu::ActOnMenuChoice()
{
	// Disable Pause Menu if you return to the game
	if (returnButton->IsClicked())
	{
		Reset();
	}
	// If Main Menu is clicked, return to main menu
	else if (mainMenuButton->IsClicked())
	{
		// Reset the Scene
		Reset();
		SceneManager::GetActiveScene()->Reset();
		SceneManager::ChangeActiveScene("StartMenuScene");
	}
}

void PauseMenu::ClickButton()
{
	clickSound->PlaySound();
	buttons[buttonSelected]->SetIsClicked(true);
}
