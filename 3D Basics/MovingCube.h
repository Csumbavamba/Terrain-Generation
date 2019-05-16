#pragma once
#include "GameObject.h"

class Mesh_Cube;
class Terrain;

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
	// Camera that follows the cube
	// a link for the mesh it's trying to walk on

	float speed;
	Terrain* terrain = NULL;
	Mesh_Cube* mesh = NULL;

};

