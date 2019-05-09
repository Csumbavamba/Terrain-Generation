#pragma once
// Std. Includes
//#include <string>
//#include <fstream>
//#include <sstream>
//#include <iostream>
#include <map>
//#include <vector>
// GL Includes
#include "ShaderLoader.h"


#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh_Model.h"

class GameObject;
class Camera;

class Model
{
public:
	
	GLuint program;
	Camera* camera;
	
	/*  Functions   */
	// Constructor, expects a filepath to a 3D model.
	Model(std::string path, Camera* camera, GameObject * owner);
	~Model();

	// Draws the model, and thus all its meshes
	void Initialise();
	void Render();
	void Update();

	

private:
	/*  Model Data  */

	std::vector<Mesh_Model*> meshes;
	std::string directory;
	std::vector<MeshTexture> texturesLoaded;	// Stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.

	GameObject * owner = NULL;

	/*  Functions   */
	// Loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
	void LoadModel(std::string path);

	// Processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
	void ProcessNode(aiNode* node, const aiScene* scene);

	Mesh_Model* ProcessMesh(aiMesh* mesh, const aiScene* scene);

	// Checks all material textures of a given type and loads the textures if they're not loaded yet.
	// The required info is returned as a Texture struct.
	std::vector<MeshTexture> LoadTextureMaterials(aiMaterial* material, aiTextureType type, std::string typeName);

	GLint CreateTextureFromFile(const char* path, std::string directory);
};

