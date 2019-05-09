#pragma once

#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

#include <string>

class Texture
{
public:
	Texture();
	~Texture();

	void Initialise();
	void SetTexturePath(std::string path);
	GLuint GetTexture() const;

private:
	std::string filePath = "Sprites/Rayman.jpg";
	GLuint texture = NULL;

};

