#include "Camera.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

#include "Utility.h"


Camera::Camera(ViewMode viewMode)
{
	this->viewMode = viewMode;
	
	cameraPosition = glm::vec3(0.0f, 1.0f, 10.0f);
	cameraLookDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUpDirection = glm::vec3(0.0f, 1.0f, 0.0f);

	fieldOfView = 120.0f;
}


Camera::~Camera()
{
}

void Camera::Initialise()
{
	timeElapsed = 0.0f;
	// Create Projection
	if (viewMode == PERSPECTIVE)
	{
		CreatePerspectiveProjection();
	}
	else
	{
		CreateOrthographicProjection();
	}
		
	// Generate PV
	CreatePV();
}

void Camera::SetViewMode(ViewMode viewMode)
{
	this->viewMode = viewMode;

	// Create Projection
	if (this->viewMode == PERSPECTIVE)
	{
		CreatePerspectiveProjection();
	}
	else
	{
		CreateOrthographicProjection();
	}

	// Generate PV
	CreatePV();
}

void Camera::Update(float deltaTime)
{
	// Last call
	CreatePV();
}

glm::mat4 Camera::GetViewMatrix() const
{
	return viewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix() const
{
	return projectionMatrix;
}

glm::mat4 Camera::GetPV() const
{
	return PV;
}


void Camera::CreatePerspectiveProjection()
{
	projectionMatrix = (glm::perspective(fieldOfView, (float)Utility::GetScreenWidth() / (float)Utility::GetScreenHeight(), 0.1f, 15000.0f));
}

void Camera::CreateOrthographicProjection()
{
	float halfScreenWidth = (float)(Utility::GetScreenWidth() / 2);
	float halfScreenHeight = (float)(Utility::GetScreenHeight() / 2);

	projectionMatrix = (glm::ortho(-halfScreenWidth, halfScreenWidth, -halfScreenHeight, halfScreenHeight, 0.1f, 1000.0f));
}

void Camera::CreatePV()
{
	viewMatrix = (glm::lookAt(cameraPosition, cameraPosition + cameraLookDirection, cameraUpDirection));

	PV = projectionMatrix * viewMatrix;
}

void Camera::SetCameraPosition(glm::vec3 cameraPosition)
{
	this->cameraPosition = cameraPosition;
}

void Camera::SetCameraLookDirection(glm::vec3 cameraLookDirection)
{
	this->cameraLookDirection = cameraLookDirection;
}

void Camera::SetCameraUpDirection(glm::vec3 cameraUpDirection)
{
	this->cameraUpDirection = cameraUpDirection;
}

glm::vec3 Camera::GetCameraPosition() const
{
	return cameraPosition;
}

glm::vec3 Camera::GetCameraLookDirection() const
{
	return cameraLookDirection;
}

glm::vec3 Camera::GetCameraUpDirection() const
{
	return cameraUpDirection;
}

float Camera::GetFieldOfView() const
{
	return fieldOfView;
}

void Camera::SetFieldOfView(float fieldOfView)
{
	this->fieldOfView = fieldOfView;

	// Recalculate the field of view
	CreatePerspectiveProjection();
}

void Camera::RotateAroundObject(glm::vec3 objectLocation, float distanceFromObject, float deltaTime)
{
	timeElapsed += deltaTime;

	float xMovement = sin(timeElapsed) * distanceFromObject;
	float zMovement = cos(timeElapsed) * distanceFromObject;

	cameraPosition = glm::vec3(objectLocation.x + xMovement, cameraPosition.y, objectLocation.z + zMovement);
	cameraLookDirection = objectLocation - cameraPosition;
}

void Camera::FollowObject(glm::vec3 objectLocation)
{
	cameraPosition = glm::vec3(objectLocation.x, cameraPosition.y, objectLocation.z);
	cameraLookDirection = glm::vec3(objectLocation.x, cameraLookDirection.y, objectLocation.z);
}
