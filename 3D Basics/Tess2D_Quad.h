#pragma once
#include "Mesh.h"



class Tess2D_Quad :
	public Mesh
{
public:
	Tess2D_Quad(GameObject * owner);
	virtual ~Tess2D_Quad() {};

	virtual void Initialise() override;
	virtual void Render(Camera * camera, GLuint program) override;

private:
	float distanceToCamera;
};

