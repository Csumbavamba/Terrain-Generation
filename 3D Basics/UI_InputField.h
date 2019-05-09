#pragma once
#include "GameObject.h"

class TextLabel;

class UI_InputField :
	public GameObject
{
public:
	UI_InputField(glm::vec2 position, std::string menuTitle = "Default ");
	virtual ~UI_InputField();

	virtual void Render(GLuint program) override;
	virtual void Update(float deltaTime) override;
	void Reset();
	
	// Enables or Disables Input
	void SetIsTyping(bool isModifying);
	bool IsTyping() const;
	std::string GetText() const;

	void SetFont(std::string font);
	void SetText(std::string text);
	void SetColor(glm::vec3 color);
	void SetScale(float scale);

private:

	void InputText();
	void AdjustTextPosition();

	bool isTyping;
	glm::vec2 positionOnScreen;
	TextLabel* displayText = NULL;
	std::string text;
};

