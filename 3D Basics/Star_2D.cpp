#include "Star_2D.h"
#include "Geometry_Star.h"
#include "ShaderLoader.h"
#include "Terrain.h"


Star_2D::Star_2D(Camera* mainCamera)
{
	this->camera = mainCamera;
	geometry = new Geometry_Star(this);

	starGeometryProgram = ShaderLoader::GetInstance()->CreateProgram("VertexGeometry.vs", "GeometryShader.gs", "FragmentGeometry.fs");
}


Star_2D::~Star_2D()
{
	delete geometry;
	geometry = NULL;
}

void Star_2D::Initialise()
{
	geometry->Initialise();

	// Move star up
	transform.position.y = terrain->GetHeightAt(transform.position.x, transform.position.z) + transform.scale.y * 2.0f;
}

void Star_2D::Render(GLuint program)
{
	geometry->Render(camera, starGeometryProgram);
}

void Star_2D::Update(float deltaTime)
{
	geometry->Update();
}

void Star_2D::SetTerrain(Terrain* terrain)
{
	this->terrain = terrain;
}
