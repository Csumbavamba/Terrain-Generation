#pragma once
#include "GameObject.h"

class Tess2D_Quad;
class Terrain;

class TessalatedQuad :
	public GameObject
{
public:
	TessalatedQuad(Camera * mainCamera);
	virtual ~TessalatedQuad();

	virtual void Initialise() override;
	virtual void Render(GLuint program) override;
	virtual void Update(float deltaTIme) override;

	void SetTerrain(Terrain* terrain);

private:
	Tess2D_Quad* mesh = NULL;
	GLuint tessalationProgram;
	Terrain* terrain = NULL;
};

