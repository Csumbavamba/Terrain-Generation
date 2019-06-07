#pragma once
#include "Scene.h"

class Fountain;

class FountainScene :
	public Scene
{
public:
	FountainScene();
	virtual ~FountainScene() {};

	virtual void Update(float deltaTime) override;
private:

	Fountain* fountain = nullptr;
};

