#pragma once


#include "Collider.h"

class GameObject;
class Collider_Box2D;

// TODO check OpenGL link - https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-detection

class Collider_Sphere : public Collider
{
public:
	Collider_Sphere(GameObject * owner);
	virtual ~Collider_Sphere();

	void Initialise() override;
	void Update();

	

	float GetRadius() const;
	void SetRadius(float newRadius);

	bool IsColliding(glm::vec3 newCenter, Collider_Sphere * otherCollider);
	bool IsColliding(Collider_Box2D * otherCollider);
	bool IsColliding(glm::vec3 newCenter, Collider_Box2D * otherCollider);

private:

	float radius;
	// TODO Render collider

};
