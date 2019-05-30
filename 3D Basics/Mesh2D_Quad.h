#pragma once
#include "Mesh.h"

class Animation2D;

class Mesh2D_Quad : public Mesh
{
public:
	Mesh2D_Quad(GameObject * owner);
	virtual ~Mesh2D_Quad();

	virtual void Initialise() override;

private:
	Animation2D* animation = NULL;
};

