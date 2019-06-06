#pragma once
#include "GameObject.h"

class Mesh_Cube;
class Terrain;
class ParticleSystem;

class MovingCube :
	public GameObject
{
public:
	MovingCube(Camera * mainCamera);
	virtual ~MovingCube();

	void SetTerrain(Terrain* terrain);

	virtual void Initialise() override;
	virtual void Render(GLuint program) override;
	virtual void Update(float deltaTime) override;

	void ProcessMovementInput(float deltaTime);

	void FollowTerrainHeight();

	void CameraTraceCube();
	bool IsOnTerrain();

private:

	ParticleSystem* particleSystem = nullptr;

	float speed;
	Terrain* terrain = NULL;
	Mesh_Cube* mesh = NULL;

};

