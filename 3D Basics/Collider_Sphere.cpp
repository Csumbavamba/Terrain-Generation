#include "Collider_Sphere.h"
#include "Collider_Box2D.h"
#include "GameObject.h"
#include "Transform.h"


Collider_Sphere::Collider_Sphere(GameObject * owner)
{
	this->owner = owner;
}


Collider_Sphere::~Collider_Sphere()
{
}

void Collider_Sphere::Initialise()
{
	radius = owner->transform.scale.x;
	center = owner->transform.position;
}

void Collider_Sphere::Update()
{
	// Update the collider position
	center = owner->transform.position;
}




float Collider_Sphere::GetRadius() const
{
	return radius;
}

void Collider_Sphere::SetRadius(float radius)
{
	this->radius = radius;
}


bool Collider_Sphere::IsColliding(glm::vec3 newCenter, Collider_Sphere * otherCollider)
{
	if (Transform::GetDistance(newCenter, otherCollider->GetCenter()) < radius + otherCollider->GetRadius())
	{
		return true;
	}
	else
	{
		return false;
	}

}

//bool Collider_Sphere::IsColliding(Collider_Box2D * otherCollider)
//{
//	// Get the closest point of the collider
//	glm::vec3 closestColliderPoint;
//	
//	// Get the closest X coordinate
//	closestColliderPoint.x = Clamp(	
//		center.x,
//		otherCollider->GetCenter().x - (Transform::GetRightVector(otherCollider->GetOwner()->transform.rotation).x * otherCollider->GetWidth() / 2),
//		otherCollider->GetCenter().x + (Transform::GetRightVector(otherCollider->GetOwner()->transform.rotation).x * otherCollider->GetWidth() / 2));
//	// Get the closest Z coordinate
//	closestColliderPoint.z = Clamp(	
//		center.z,
//		otherCollider->GetCenter().z + (Transform::GetForwardVector(otherCollider->GetOwner()->transform.rotation).z * otherCollider->GetHeight() / 2),
//		otherCollider->GetCenter().z - (Transform::GetForwardVector(otherCollider->GetOwner()->transform.rotation).z * otherCollider->GetHeight() / 2));
//	// Get the closest Y coordinate
//	// Do later
//	closestColliderPoint.y = 0.0f;
//
//	// If the distance between the closest point and the center is smaller than the radius --> collision
//	if (Transform::GetDistance(center, closestColliderPoint) < radius)
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}

bool Collider_Sphere::IsColliding(glm::vec3 newCenter, Collider_Box2D * otherCollider)
{
	// Get the closest point of the collider
	glm::vec3 closestColliderPoint;

	// Get the closest X coordinate
	closestColliderPoint.x = Clamp(
		center.x,
		otherCollider->GetCenter().x - (Transform::GetRightVector(otherCollider->GetOwner()->transform.rotation).x * otherCollider->GetWidth() / 2),
		otherCollider->GetCenter().x + (Transform::GetRightVector(otherCollider->GetOwner()->transform.rotation).x * otherCollider->GetWidth() / 2));
	// Get the closest Z coordinate
	closestColliderPoint.z = Clamp(
		center.z,
		otherCollider->GetCenter().z + (Transform::GetForwardVector(otherCollider->GetOwner()->transform.rotation).z * otherCollider->GetHeight() / 2),
		otherCollider->GetCenter().z - (Transform::GetForwardVector(otherCollider->GetOwner()->transform.rotation).z * otherCollider->GetHeight() / 2));
	// Get the closest Y coordinate
	// Do later
	closestColliderPoint.y = 0.0f;
	
	// If the distance between the closest point and the center is smaller than the radius --> collision
	if (Transform::GetDistance(newCenter, closestColliderPoint) < radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

