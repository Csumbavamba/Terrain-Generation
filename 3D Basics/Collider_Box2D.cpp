#include "Collider_Box2D.h"
#include "GameObject.h"
#include "Collider_Sphere.h"
#include "Mesh2D_Quad.h"



Collider_Box2D::Collider_Box2D(GameObject * owner)
{
	this->owner = owner;
	isMeshVisible = true;
}


Collider_Box2D::~Collider_Box2D()
{
}

void Collider_Box2D::Initialise()
{
	center = owner->transform.position;

	width = owner->transform.scale.x;
	height = owner->transform.scale.z;
}

void Collider_Box2D::Update()
{
	center = owner->transform.position;

	width = owner->transform.scale.x;
	height = owner->transform.scale.z;
}


bool Collider_Box2D::IsColliding(glm::vec3 otherPosition)
{
	// If the new position is inside the other collider
	bool collisionX = otherPosition.x + width / 2 >= center.x &&
		center.x + width / 2 >= otherPosition.x;

	bool collisionZ = otherPosition.z + height / 2 >= center.z &&
		center.z + height >= otherPosition.z;

	// If they are colliding
	if (collisionX && collisionZ)
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool Collider_Box2D::IsColliding(Collider_Sphere * otherCollider)
{
	// Get the closest point of the collider
	glm::vec3 closestColliderPoint;

	// Get the closest X coordinate
	closestColliderPoint.x = Clamp(
		otherCollider->GetCenter().x,
		center.x - (width / 2),
		center.x + (width / 2));
	// Get the closest Z coordinate
	closestColliderPoint.z = Clamp(
		otherCollider->GetCenter().z,
		center.z - (height / 2),
		center.z + (height / 2));
	// Get the closest Y coordinate
	// Do later
	closestColliderPoint.y = 0.0f;



	// If the distance between the closest point and the center is smaller than the radius --> collision
	if (Transform::GetDistance(otherCollider->GetCenter(), closestColliderPoint) < otherCollider->GetRadius())
	{
		return true;
	}
	else
	{
		return false;
	}
}


float Collider_Box2D::GetWidth() const
{
	return width;
}

float Collider_Box2D::GetHeight() const
{
	return height;
}

void Collider_Box2D::SetWidth(float width)
{
	this->width = width;
}

void Collider_Box2D::SetHeight(float height)
{
	this->height = height;
}
