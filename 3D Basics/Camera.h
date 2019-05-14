#pragma once

#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

enum ViewMode
{
	PERSPECTIVE,
	ORTOGRAPHIC
};

class Camera
{
public:
	Camera(ViewMode viewMode);
	~Camera();

	void Initialise();
	void SetViewMode(ViewMode viewMode);
	void Update(float deltaTime);

	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const;
	glm::mat4 GetPV() const;

	void SetCameraPosition(glm::vec3 cameraPosition);
	void SetCameraLookDirection(glm::vec3 cameraLookDirection);
	void SetCameraUpDirection(glm::vec3 cameraUpDirection);

	glm::vec3 GetCameraPosition() const;
	glm::vec3 GetCameraLookDirection() const;
	glm::vec3 GetCameraUpDirection() const;

	float GetFieldOfView() const;
	void SetFieldOfView(float fieldOfView);

	void RotateAroundObject(glm::vec3 objectLocation, float distanceFromObject, float deltaTime);
	void FollowObject(glm::vec3 objectLocation);


private:
	glm::vec3 cameraPosition;
	glm::vec3 cameraLookDirection;
	glm::vec3 cameraUpDirection;

	// Matrix creation
	void CreatePerspectiveProjection();
	void CreateOrthographicProjection();
	void CreatePV();

	ViewMode viewMode;
	float timeElapsed;
	float fieldOfView;

	// Stored matricies
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 PV;

};

