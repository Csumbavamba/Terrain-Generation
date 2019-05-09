#include "Animator2D.h"
#include "Mesh2D_Quad.h"
#include "Time.h"

Animator2D::Animator2D(Mesh2D_Quad* mesh)
{
	this->mesh = mesh;
}

Animator2D::~Animator2D()
{
	// See if there's a need for vector cleanup
}

void Animator2D::Update(int animationIndex)
{
	currentAnimation->Update(animationIndex, true, Time::GetDeltaTime());

	PlayAnimation();
}

void Animator2D::PlayAnimation()
{
	mesh->PlayAnimation(currentAnimation);
}

void Animator2D::AddAnimationClip(Animation2D* animation)
{
	vectorOfAnimationClips.push_back(animation);
}

void Animator2D::SetCurrentAnimation(int animationIndex)
{
	if (vectorOfAnimationClips.size() > 0)
	{
		currentAnimation = vectorOfAnimationClips.at(animationIndex);
		mesh->GetTexture()->SetTexturePath(currentAnimation->GetFilePath());
	}
}

void Animator2D::SetCurrentAnimation(Animation2D* animation)
{
	if (vectorOfAnimationClips.size() > 0)
	{
		currentAnimation = animation;
		mesh->GetTexture()->SetTexturePath(currentAnimation->GetFilePath());
	}
}