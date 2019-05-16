#include "MovingCube.h"
#include "Mesh_Cube.h"
#include "Terrain.h"
#include "Input.h"


MovingCube::MovingCube(Camera* mainCamera)
{
	this->camera = mainCamera;

	mesh = new Mesh_Cube(this);
}


MovingCube::~MovingCube()
{
	delete mesh;
	mesh = NULL;
}

void MovingCube::SetTerrain(Terrain* terrain)
{
	this->terrain = terrain;
}

void MovingCube::Initialise()
{
	mesh->Initialise();
}

void MovingCube::Render(GLuint program)
{
	mesh->Render(camera, program);
}

void MovingCube::Update(float deltaTime)
{
	mesh->Update();

	// TODO Move the camera as well

	transform.position.y = terrain->GetHeightAt(transform.position.x, transform.position.z);

	// Move Forward
	if (Input::GetKeyState('w') == DOWN)
	{
		transform.position.z -= deltaTime;
	}
	// Move Backward
	else if (Input::GetKeyState('s') == DOWN)
	{
		transform.position.z += deltaTime;
	}

	// Move Right
	if (Input::GetKeyState('d') == DOWN)
	{
		transform.position.x += deltaTime;
	}
	// Move Left
	else if (Input::GetKeyState('a') == DOWN)
	{
		transform.position.x -= deltaTime;
	}

}
