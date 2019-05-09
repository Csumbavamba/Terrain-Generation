#pragma once
#include "Collider.h"

class GameObject;
class Collider_Sphere;

class Collider_Box2D : public Collider // TODO LEARN THIS MOTHERFUCKER https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-detection
{
public:
	Collider_Box2D(GameObject * owner);
	virtual ~Collider_Box2D();

	void Initialise() override;
	void Update();

	// bool IsColliding(glm::vec3 newCenter, CircleCollider * otherCollider);
	bool IsColliding(glm::vec3 otherPosition);
	bool IsColliding(Collider_Sphere * collider);

	float GetWidth() const;
	float GetHeight() const;

	void SetWidth(float width);
	void SetHeight(float height);

private:

	float width;
	float height;

	bool isMeshVisible;

};

