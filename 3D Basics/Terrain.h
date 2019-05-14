#pragma once
#include "GameObject.h"

class Mesh_Terrain;

class Terrain :
	public GameObject
{
public:
	Terrain(Camera * camera);
	virtual ~Terrain();

	virtual void Initialise() override;
	virtual void Render(GLuint program) override;
	virtual void Update(float deltaTime) override;

	float GetHeightAt(float x, float z) const;

private:
	Mesh_Terrain* terrain = NULL;
};

