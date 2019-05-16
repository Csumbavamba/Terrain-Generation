#include "Terrain.h"
#include "Mesh_Terrain.h"
#include "Texture.h"


Terrain::Terrain(Camera* camera)
{
	this->camera = camera;
	terrain = new Mesh_Terrain(this);

	//transform.scale *= 0.01f;
	terrain->GetTexture()->SetTexturePath("Sprites/grass.jpg");
}


Terrain::~Terrain()
{
	delete terrain;
	terrain = NULL;
}

void Terrain::Initialise()
{
	terrain->Initialise();
}

void Terrain::Render(GLuint program)
{
	terrain->Render(camera, program);
}

void Terrain::Update(float deltaTime)
{
	terrain->Update();
}

float Terrain::GetHeightAt(float x, float z) const
{
	return terrain->GetHeightAt(x, z);
}

float Terrain::GetWidth() const
{
	return terrain->GetWidth();
}

float Terrain::GetDepth() const
{
	return terrain->GetDepth();
}
