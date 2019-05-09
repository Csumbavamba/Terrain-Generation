#pragma once
#include "GameObject.h"

class TextLabel;

class UI_Text : public GameObject
{
public:
	UI_Text(std::string menuTitle, glm::vec2 position, std::string font = "Dependencies/Fonts/DWARVESC.TTF");
	virtual ~UI_Text();

	virtual void Render(GLuint program) override;
	virtual void Update(float deltaTime) override;
	void AdjustTextPosition();

	void SetFont(std::string font);
	void SetText(std::string text);
	void SetColor(glm::vec3 color);
	void SetScale(float scale);

private:

	virtual void Initialise() override {};
	glm::vec2 positionOnScreen;
	TextLabel * text = NULL;
};

