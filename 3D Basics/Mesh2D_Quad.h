#pragma once
#include "Mesh.h"

class Animation2D;

class Mesh2D_Quad : public Mesh
{
public:
	Mesh2D_Quad(GameObject * owner);
	virtual ~Mesh2D_Quad();

	virtual void Initialise() override;

	void PlayAnimation(Animation2D* animation);

	void Animate();

private:
	Animation2D* animation = NULL;
};

