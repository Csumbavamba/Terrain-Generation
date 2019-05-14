#include "UI_Image.h"
#include "Mesh2D_Quad.h"
#include "Texture.h"
#include "ShaderLoader.h"
#include "Camera.h"

#include "Utility.h"



UI_Image::UI_Image(Camera * camera, std::string imagePath, glm::vec2 sizeInPixels)
{
	// Setup Background Image
	backgroundImage = new Mesh2D_Quad(this);
	backgroundImage->GetTexture()->SetTexturePath(imagePath);
	this->camera = camera;

	transform.rotation.x = -90.0f;

	transform.scale.x = -sizeInPixels.x;
	transform.scale.z = sizeInPixels.y;

	// Create Background Program
	imageProgram = ShaderLoader::GetInstance()->CreateProgram("VertexShader.vs", "FragmentShader.fs");

	backgroundImage->Initialise();
}


UI_Image::~UI_Image()
{
	delete backgroundImage;
	backgroundImage = NULL;
}


void UI_Image::Render(GLuint program)
{
	// Enable Culling
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	backgroundImage->Render(camera, imageProgram);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
}

void UI_Image::Update(float deltaTime)
{
	backgroundImage->Update();
}
