#pragma once

#include "Mesh.h"

class Mesh_Pyramid : public Mesh
{
public:
	Mesh_Pyramid(GameObject * owner);
	virtual ~Mesh_Pyramid();

	virtual void Initialise() override;
};

