#include "TessalatedQuad.h"
#include "Tess2D_Quad.h"
#include "ShaderLoader.h"
#include "Terrain.h"


TessalatedQuad::TessalatedQuad(Camera * mainCamera)
{
	this->camera = mainCamera;
	mesh = new Tess2D_Quad(this);

	tessalationProgram = ShaderLoader::GetInstance()->CreateProgram(
		"Shaders/VertexTessalation.vs",
		"Shaders/TessalationControl.tc",
		"Shaders/TessalationEvaluation.te",
		"Shaders/FragmentTessalation.fs");
}


TessalatedQuad::~TessalatedQuad()
{
	delete mesh;
	mesh = NULL;
}

void TessalatedQuad::Initialise()
{
	mesh->Initialise();

	// Move Quad to position
	transform.scale *= 3.0f;
	transform.position.y = terrain->GetHeightAt(transform.position.x, transform.position.z) + transform.scale.y;
	transform.position.x -= 3.0f;
	transform.position.z -= 3.0f;
}

void TessalatedQuad::Render(GLuint program)
{
	mesh->Render(camera, tessalationProgram);
}

void TessalatedQuad::Update(float deltaTIme)
{
	mesh->Update();
}

void TessalatedQuad::SetTerrain(Terrain* terrain)
{
	this->terrain = terrain;
}
