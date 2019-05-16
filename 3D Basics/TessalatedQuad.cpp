#include "TessalatedQuad.h"
#include "Tess2D_Quad.h"
#include "ShaderLoader.h"
#include "Terrain.h"


TessalatedQuad::TessalatedQuad(Camera * mainCamera)
{
	this->camera = mainCamera;
	mesh = new Tess2D_Quad(this);

	tessalationProgram = ShaderLoader::GetInstance()->CreateProgram(
		"VertexTessalation.vs",
		"TessalationControl.tc",
		"TessalationEvaluation.te",
		"FragmentTessalation.fs");
}


TessalatedQuad::~TessalatedQuad()
{
	delete mesh;
	mesh = NULL;
}

void TessalatedQuad::Initialise()
{
	mesh->Initialise();

	// Move Quad up
	transform.position.y = terrain->GetHeightAt(transform.position.x, transform.position.z) + transform.scale.y * 2.0f;
	transform.position.x -= 3.0f;
}

void TessalatedQuad::Render(GLuint program)
{
	glDisable(GL_CULL_FACE);
	mesh->Render(camera, tessalationProgram);
	glEnable(GL_CULL_FACE);
}

void TessalatedQuad::Update(float deltaTIme)
{
	mesh->Update();
}

void TessalatedQuad::SetTerrain(Terrain* terrain)
{
	this->terrain = terrain;
}
