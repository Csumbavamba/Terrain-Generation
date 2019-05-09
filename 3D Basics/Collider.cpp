#include "Collider.h"
#include <algorithm>



Collider::Collider()
{
}


Collider::~Collider()
{
}

float Collider::Clamp(float value, float min, float max)
{
	return std::max(min, std::min(max, value));
}


glm::vec3 Collider::GetCenter() const
{
	return center;
}

GameObject * Collider::GetOwner() const
{
	return owner;
}
