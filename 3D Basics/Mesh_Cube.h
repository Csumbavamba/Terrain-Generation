#pragma once
#include "Mesh.h"
class Mesh_Cube : public Mesh
{
public:
	
	Mesh_Cube(GameObject * owner);
	virtual ~Mesh_Cube();

	virtual void Initialise() override;

protected:
	Mesh_Cube() {};
};

