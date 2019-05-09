#pragma once
#include "Animation2D.h"
#include <vector>

class Mesh2D_Quad;

class Animator2D
{
public:
	Animator2D(Mesh2D_Quad* mesh);
	~Animator2D();

	void Update(int animationIndex);

	void PlayAnimation();
	void AddAnimationClip(Animation2D* animation);
	void SetCurrentAnimation(int animationIndex);
	void SetCurrentAnimation(Animation2D* animation);
	

private:
	std::vector<Animation2D*> vectorOfAnimationClips;
	Animation2D* currentAnimation = NULL;
	Mesh2D_Quad* mesh = NULL;
};

