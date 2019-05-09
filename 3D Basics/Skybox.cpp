#include "Skybox.h"
#include <vector>
#include "CubeMap.h"



Skybox::Skybox(Camera * camera)
{
	this->camera = camera;
	std::vector <std::string> vectorOfFilePaths;
	vectorOfFilePaths.push_back("Sprites/CubeMap/right.jpg");
	vectorOfFilePaths.push_back("Sprites/CubeMap/left.jpg");
	vectorOfFilePaths.push_back("Sprites/CubeMap/top.jpg");
	vectorOfFilePaths.push_back("Sprites/CubeMap/bottom.jpg");
	vectorOfFilePaths.push_back("Sprites/CubeMap/back.jpg");
	vectorOfFilePaths.push_back("Sprites/CubeMap/front.jpg");
	cubeMap = new CubeMap(this, vectorOfFilePaths);

	transform.position = glm::vec3(0.0f, 0.0f, 0.0f); // TODO - check if needed
}


Skybox::~Skybox()
{
	delete cubeMap;
	cubeMap = NULL;
}

void Skybox::Initialise()
{
	cubeMap->Initialise();
}

void Skybox::Render(GLuint program)
{
	cubeMap->Render(camera, program);
}

void Skybox::Update()
{
	cubeMap->Update();
}

GLuint Skybox::GetTextureID()
{
	return cubeMap->GetTexture();
}


