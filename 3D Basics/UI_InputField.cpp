#include "UI_InputField.h"
#include "TextLabel.h"
#include "Input.h"


UI_InputField::UI_InputField(glm::vec2 position, std::string menuTitle)
{
	std::string font = "Dependencies/Fonts/DWARVESC.TTF";
	positionOnScreen = position;
	isTyping = false;

	displayText = new TextLabel(menuTitle, font, position);
	displayText->Initialise();

	text = menuTitle;
	AdjustTextPosition();
}


UI_InputField::~UI_InputField()
{
	delete displayText;
	displayText = NULL;
}

void UI_InputField::Render(GLuint program)
{
	displayText->Render(NULL);
}

void UI_InputField::Update(float deltaTime)
{
	displayText->Update();

	// Get Input from player if it's in typing mode
	if (isTyping)
	{
		InputText();
	}
}

void UI_InputField::Reset()
{
	isTyping = false;
	text = "Default ";
	displayText->SetText(text);
}

void UI_InputField::AdjustTextPosition()
{
	displayText->CalculateDimensions();

	glm::vec2 adjustedPosition = glm::vec2(
		positionOnScreen.x - displayText->GetTextWidth() / 2,
		positionOnScreen.y - displayText->GetTextHeight() / 2);

	displayText->SetPosition(adjustedPosition);
}


void UI_InputField::SetIsTyping(bool isModifying)
{
	this->isTyping = isModifying;

	if (!isTyping)
	{
		displayText->SetColor(glm::vec3(0.8f, 0.8f, 0.8f));
	}
	else
	{
		displayText->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
		text = "";
		displayText->SetText(text);
	}
}

bool UI_InputField::IsTyping() const
{
	return isTyping;
}

void UI_InputField::InputText()
{
	// Get the last key that was pressed
	char letter(Input::GetLastKeyDown());

	// Erase last character if BackSpace is pressed
	if (Input::GetKeyState(8) == DOWN_FIRST || Input::GetKeyState(127) == DOWN_FIRST)
	{
		// Only erase if it's not empty
		if (!text.empty())
		{
			// Erase last character
			text.erase(text.end() - 1);

			// Display characters
			displayText->SetText(text);
		}

	}
	// Add character based on user press
	else if (letter != 'Null' && Input::GetKeyState(letter) == DOWN_FIRST)
	{
		std::string stringLetter(1, letter);

		// Append the text by the key that was pressed
		text.append(stringLetter);
		displayText->SetText(text);
	}
}

std::string UI_InputField::GetText() const
{
	return text;
}

void UI_InputField::SetFont(std::string font)
{
	displayText->SetFont(font);
}

void UI_InputField::SetText(std::string text)
{
	this->text = text;
	displayText->SetText(text);

	// Add Adjustment based on alignment
}

void UI_InputField::SetColor(glm::vec3 color)
{
	displayText->SetColor(color);
}

void UI_InputField::SetScale(float scale)
{
	displayText->SetScale(scale);
	AdjustTextPosition();
}
