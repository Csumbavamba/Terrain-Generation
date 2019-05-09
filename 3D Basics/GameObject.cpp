#include "GameObject.h"
#include "Camera.h"


GameObject::GameObject()
{
	isActive = true;
}
GameObject::~GameObject()
{
}


void GameObject::SetCamera(Camera * camera)
{
	this->camera = camera;
}

void GameObject::SetActive(bool isActive)
{
	this->isActive = isActive;
}

bool GameObject::IsActive() const
{
	return isActive;
}
