#pragma once

#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

class GameObject;

class Collider
{
public:
	Collider();
	virtual ~Collider();

	virtual void Initialise() = 0;

	float Clamp(float value, float min, float max);

	glm::vec3 GetCenter() const;
	GameObject * GetOwner() const;

protected:
	GameObject * owner = nullptr;
	glm::vec3 center;
};

