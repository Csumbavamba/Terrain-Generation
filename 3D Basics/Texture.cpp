#include "Texture.h"

Texture::Texture()
{
}

Texture::~Texture()
{
}

void Texture::Initialise()
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int width, height, channels;
	unsigned char* textureImage = SOIL_load_image(filePath.c_str(), &width, &height, &channels, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage);

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(textureImage);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::SetTexturePath(std::string path)
{
	filePath = path;

	Initialise();
}

GLuint Texture::GetTexture() const
{
	return texture;
}
