#pragma once

#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\common.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"
#include "Dependencies\glm\gtc\quaternion.hpp"
#include "Dependencies\glm\gtx\quaternion.hpp"


#include <sstream>
#include <math.h>

struct Transform
{
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::vec3 movementVector = glm::vec3();



	// Getting Vectors - TODO fix these
	static glm::vec3 GetForwardVector(glm::vec3 rotation)
	{
		// Convert to radians
		glm::vec3 rotationInRadians = ToRadians(rotation);

		// Calculate forward vector
		glm::vec3 forwardVector = glm::vec3(
			sin(rotationInRadians.y),
			cos(rotationInRadians.y) * sin(rotationInRadians.z),
			cos(rotationInRadians.y) * cos(rotationInRadians.z));

		// Normalize the vector
		glm::normalize(forwardVector);

		return -1.0f * forwardVector;
	}
	static glm::vec3 GetRightVector(glm::vec3 rotation)
	{
		// Convert to radians
		glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::vec3 rightVector = glm::cross(GetForwardVector(rotation), upVector); // TODO calculate right vector

		return rightVector;
	}

	// Calculate distance between 2 vectors
	static float GetDistance2D(glm::vec3 position1, glm::vec3 position2)
	{
		return std::sqrt(std::pow((position1.x - position2.x), 2.0f) + std::pow((position1.y - position2.y), 2.0f));
	}

	static float GetDistance(glm::vec3 position1, glm::vec3 position2)
	{
		return std::sqrt(std::pow((position1.x - position2.x), 2.0f) + std::pow((position1.y - position2.y), 2.0f) + std::pow((position1.z - position2.z), 2.0f));
	}

	static float GetScreenDistance(glm::vec2 position1, glm::vec2 position2)
	{
		return std::sqrt(std::pow((position1.x - position2.x), 2.0f) + std::pow((position1.y - position2.y), 2.0f));
	}
	static glm::vec3 GetDirectionVectorForTarget(glm::vec3 startPosition, glm::vec3 targetPosition)
	{
		return (targetPosition - startPosition);
	}

	glm::mat4 CalculateRotationMatrix()
	{
		glm::quat rotationQuaternion = glm::quat(ToRadians(rotation));
		return glm::toMat4(rotationQuaternion);
	}

	static glm::vec3 ToRadians(glm::vec3 degrees)
	{
		return glm::vec3(glm::radians(degrees.x), glm::radians(degrees.y), glm::radians(degrees.z));
	}

};