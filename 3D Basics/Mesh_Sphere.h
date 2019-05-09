#pragma once
#include "Mesh.h"

class Mesh_Sphere : public Mesh
{
public:
	Mesh_Sphere(GameObject * owner);
	virtual ~Mesh_Sphere();

	virtual void Initialise() override;
};

