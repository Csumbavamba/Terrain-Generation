#include "GameMenu.h"

#include "UI_Button.h"
#include "Camera.h"
#include "AudioSound.h"
#include "Input.h"
#include "Application.h"
#include "SceneManager.h"

#include <iostream>


GameMenu::GameMenu(Camera * mainCamera)
{
	this->camera = mainCamera;

	buttonSelected = 0;

	// Create buttons
	startButton = new UI_Button("START", glm::vec2(0.0f, 100.0f));
	quitButton = new UI_Button("QUIT", glm::vec2(0.0f, -100.0f));


	// Move buttons into array for easier control
	buttons[0] = startButton;
	buttons[1] = quitButton;

	// Start is selected by default
	buttons[buttonSelected]->SetIsSelected(true);
	
	clickSound = new AudioSound("Audio/Click.wav", DEFAULT);
	swapSound = new AudioSound("Audio/Click2.wav", DEFAULT);
}


GameMenu::~GameMenu()
{
	for (int i = 0; i < 2; i++)
	{
		delete buttons[i];
		buttons[i] = NULL;
	}

	delete clickSound;
	clickSound = NULL;

	delete swapSound;
	swapSound = NULL;
}


void GameMenu::Render(GLuint program)
{
	if (isActive)
	{
		startButton->Render(NULL);
		quitButton->Render(NULL);
	}
}

void GameMenu::Update(float deltaTime)
{
	if (isActive)
	{
		startButton->Update(deltaTime);
		quitButton->Update(deltaTime);

		ProcessKeyboardNavigation();
		ProcessKeyboardClicks();
	}
}

void GameMenu::Reset()
{
	startButton->Reset();
	quitButton->Reset();

	isActive = true;

	// Start button is selected by default
	buttonSelected = 0;
	startButton->SetIsSelected(true);
}

void GameMenu::ProcessKeyboardNavigation()
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

void GameMenu::ProcessKeyboardClicks()
{
	// If Enter is pressed
	if (Input::GetKeyState(13) == DOWN_FIRST)
	{
		ClickButton();
		ActOnMenuChoice();
	}
}

void GameMenu::ChangeSelectedButton(int change)
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

void GameMenu::ActOnMenuChoice()
{
	if (startButton->IsClicked())
	{
		// Go to BattleShout Input
		this->Reset();
		SceneManager::ChangeActiveScene("GameScene");
	}
	else if (quitButton->IsClicked())
	{
		// Quit Application
		Application::QuitGame();
	}
}

void GameMenu::ClickButton()
{
	clickSound->PlaySound();
	buttons[buttonSelected]->SetIsClicked(true);
}
