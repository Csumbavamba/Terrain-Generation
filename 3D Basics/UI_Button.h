#pragma once
#include "GameObject.h"

class TextLabel;
class AudioSound;
class AudioSystem;

class UI_Button : public GameObject
{
public:
	UI_Button(std::string menuTitle, glm::vec2 position);
	virtual ~UI_Button();

	
	virtual void Render(GLuint program) override;
	virtual void Update(float deltaTime) override;

	// Design
	void AdjustButtonPosition();
	void SetScale(float scale);
	void SetFont(std::string font);
	void SetText(std::string text);


	// Interaction
	bool IsClicked() const;
	bool IsSelected() const;
	void SetIsSelected(bool isSelected);
	void SetIsClicked(bool isClicked);
	void Reset();

	

private:

	virtual void Initialise() override {};

	glm::vec2 positionOnScreen;
	bool isClicked;
	bool isSelected;
	TextLabel * button = NULL;

};

