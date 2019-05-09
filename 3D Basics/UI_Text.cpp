#include "UI_Text.h"
#include "TextLabel.h"



UI_Text::UI_Text(std::string menuTitle, glm::vec2 position, std::string font)
{
	positionOnScreen = position;

	text = new TextLabel(menuTitle, font, position);
	text->Initialise();

	text->SetScale(0.5f);
	AdjustTextPosition();
}


UI_Text::~UI_Text()
{
	delete text;
	text = NULL;
}


void UI_Text::Render(GLuint program)
{
	text->Render(NULL);
}

void UI_Text::Update(float deltaTime)
{
	text->Update();
}

void UI_Text::AdjustTextPosition()
{
	text->CalculateDimensions();

	glm::vec2 adjustedPosition = glm::vec2(
		positionOnScreen.x - text->GetTextWidth() / 2,
		positionOnScreen.y - text->GetTextHeight() / 2);

	text->SetPosition(adjustedPosition);
}

void UI_Text::SetFont(std::string font)
{
	text->SetFont(font);
	text->Initialise();
}

void UI_Text::SetText(std::string text)
{
	this->text->SetText(text);
	
}

void UI_Text::SetColor(glm::vec3 color)
{
	text->SetColor(color);
}

void UI_Text::SetScale(float scale)
{
	text->SetScale(scale);
	AdjustTextPosition();
}

