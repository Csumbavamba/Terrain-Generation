#pragma once
#include "Mesh.h"
#include "Camera.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Vertex
{
	glm::vec3 position; // Position	
	glm::vec3 normal; // Normal	
	glm::vec2 texCoords; // TexCoords
};
struct MeshTexture
{
	GLuint id;
	std::string type;
	aiString path;
};


class Mesh_Model : public Mesh
{
public:
	Mesh_Model(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<MeshTexture> textures);
	virtual ~Mesh_Model();

	virtual void Initialise() override;
	virtual void Render(Camera* camera, GLuint program) override;
	virtual void Update();

	void SetOwner(GameObject * owner);

private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<MeshTexture> textures;
};

