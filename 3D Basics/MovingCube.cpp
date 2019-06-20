#include "MovingCube.h"
#include "Mesh_Cube.h"
#include "Terrain.h"
#include "Input.h"
#include "Camera.h"
#include "Texture.h"
#include "ParticleSystem.h"

MovingCube::MovingCube(Camera* mainCamera)
{
	this->camera = mainCamera;

	mesh = new Mesh_Cube(this);
	particleSystem = new ParticleSystem(this, false);

	speed = 15.0f;

	mesh->GetTexture()->SetTexturePath("Sprites/Rock.png");
}


MovingCube::~MovingCube()
{
	delete mesh;
	mesh = NULL;

	delete particleSystem;
	particleSystem = NULL;
}

void MovingCube::SetTerrain(Terrain* terrain)
{
	this->terrain = terrain;
}

void MovingCube::Initialise()
{
	mesh->Initialise();

	particleSystem->Initialise();

	FollowTerrainHeight();
}

void MovingCube::Render(GLuint program)
{
	mesh->Render(camera, program);

	particleSystem->Render(camera, NULL);
}

void MovingCube::Update(float deltaTime)
{
	mesh->Update();

	particleSystem->Update(deltaTime);

	CameraTraceCube();
	ProcessMovementInput(deltaTime);
}

void MovingCube::ProcessMovementInput(float deltaTime)
{
	// Move Forward
	if (Input::GetKeyState('w') == DOWN)
	{
		transform.position.z -= deltaTime * speed;
		FollowTerrainHeight();
	}
	// Move Backward
	else if (Input::GetKeyState('s') == DOWN)
	{
		transform.position.z += deltaTime * speed;
		FollowTerrainHeight();
	}

	// Move Right
	if (Input::GetKeyState('d') == DOWN)
	{
		transform.position.x += deltaTime * speed;
		FollowTerrainHeight();
	}
	// Move Left
	else if (Input::GetKeyState('a') == DOWN)
	{
		transform.position.x -= deltaTime * speed;
		FollowTerrainHeight();
	}

	
}

void MovingCube::FollowTerrainHeight()
{
	// Check if we are on the terrain
	if (IsOnTerrain())
	{
		// Mach terrain height
		transform.position.y = terrain->GetHeightAt(transform.position.x, transform.position.z) + transform.scale.y / 2.0f;
	}
}

void MovingCube::CameraTraceCube()
{
	// Make camera follow the cube
	glm::vec3 cameraPosition = transform.position;
	cameraPosition.z += 30.0f;
	cameraPosition.y += 10.0f;
	camera->SetCameraPosition(cameraPosition);

	//// Make camera look at the cube
	glm::vec3 lookDirection = transform.position - cameraPosition;
	camera->SetCameraLookDirection(lookDirection);
}

bool MovingCube::IsOnTerrain()
{
	// If we are no longer on the terrain
	if ((transform.position.x < terrain->transform.position.x - terrain->GetWidth() / 2.0f) ||	// Left
		(transform.position.x > terrain->transform.position.x + terrain->GetWidth() / 2.0f) ||	// Right
		(transform.position.z < terrain->transform.position.z - terrain->GetDepth() / 2.0f) ||	// Up
		(transform.position.z > terrain->transform.position.z + terrain->GetDepth() / 2.0f))	// Down
	{
		return false;
	}

	return true;
}
