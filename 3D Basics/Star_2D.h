#pragma once
#include "GameObject.h"

class Geometry_Star;
class Terrain;

class Star_2D :
	public GameObject
{
public:
	Star_2D(Camera * mainCamera);
	virtual ~Star_2D();

	virtual void Initialise() override;
	virtual void Render(GLuint program) override;
	virtual void Update(float deltaTime) override;

	void SetTerrain(Terrain* terrain);

private:

	GLuint starGeometryProgram;
	Geometry_Star* geometry = NULL;
	Terrain* terrain = NULL;
};

