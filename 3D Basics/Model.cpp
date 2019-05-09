#include "Model.h"
#include "Camera.h"

#include <algorithm>

Model::Model(std::string path, Camera* camera, GameObject * owner)
{
	this->program = ShaderLoader::GetInstance()->CreateProgram("Model.vs", "Model.fs");

	this->camera = camera;
	this->owner = owner;

	this->LoadModel(path);
}

Model::~Model()
{
	for (auto mesh : meshes)
	{
		delete mesh;
		mesh = NULL;
	}
}

void Model::Initialise()
{
	for (GLuint i = 0; i < this->meshes.size(); i++)
	{
		this->meshes[i]->SetOwner(owner);
	}
}

void Model::Render()
{
	for (GLuint i = 0; i < this->meshes.size(); i++)
	{
		this->meshes[i]->Render(camera, program);
	}
}

void Model::Update()
{
	for (GLuint i = 0; i < this->meshes.size(); i++)
	{
		this->meshes[i]->Update();
	}
}

void Model::LoadModel(std::string filePath)
{
	// Read file via ASSIMP
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

	// Check for errors
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}

	// Retrieve the directory path of the filepath
	this->directory = filePath.substr(0, filePath.find_last_of('/'));

	// Process ASSIMP's root node recursively
	this->ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	// Process each mesh located at the current node
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		// The node object only contains indices to index the actual objects in the scene. 
		// The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

		if (meshes.size() == 1)
		{
			int k = 0;
		}

		Mesh_Model * meshCreated = this->ProcessMesh(mesh, scene);

		this->meshes.push_back(meshCreated);

		int ki = 0;

	}
	// int i = 0;
	// After we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		this->ProcessNode(node->mChildren[i], scene);
	}
}

Mesh_Model* Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	// Data to fill
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<MeshTexture> textures;

	// Walk through each of the mesh's vertices
	for (GLuint i = 0; i < mesh->mNumVertices; ++i)
	{
		Vertex vertex;
		// We declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class
		// so we transfer the data to this placeholder glm::vec3 first.
		glm::vec3 assimpVector3;

		// Positions
		assimpVector3.x = mesh->mVertices[i].x;
		assimpVector3.y = mesh->mVertices[i].y;
		assimpVector3.z = mesh->mVertices[i].z;
		vertex.position = assimpVector3;

		// Normals
		assimpVector3.x = mesh->mNormals[i].x;
		assimpVector3.y = mesh->mNormals[i].y;
		assimpVector3.z = mesh->mNormals[i].z;
		vertex.normal = assimpVector3;

		// Texture Coordinates
		if (mesh->mTextureCoords[0]) // If the mesh has texture coordinates
		{
			glm::vec2 assimpVector2;
			// A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			assimpVector2.x = mesh->mTextureCoords[0][i].x;
			assimpVector2.y = mesh->mTextureCoords[0][i].y;
			vertex.texCoords = assimpVector2;

		}
		else
			vertex.texCoords = glm::vec2(0.0f, 0.0f);
		vertices.push_back(vertex);
	}
	// Get all the faces of the mesh (calculate the indicies)
	for (GLuint i = 0; i < mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];

		// Retrieve all indices of the face and store them in the indices vector
		for (GLuint j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}	
	}

	// Process all the materials (textures)
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial * material = scene->mMaterials[mesh->mMaterialIndex];

		// We assume a convention for sampler names in the shaders. Each diffuse texture should be named
		// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
		// Same applies to other texture as the following list summarizes:
		// Diffuse: texture_diffuseN
		// Specular: texture_specularN
		// Normal: texture_normalN

		// 1. Diffuse maps
		std::vector<MeshTexture> diffuseMaps = this->LoadTextureMaterials(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		// 2. Specular maps
		std::vector<MeshTexture> specularMaps = this->LoadTextureMaterials(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}
	Mesh_Model * createdModel = new Mesh_Model(vertices, indices, textures);
	// Return a mesh object created from the extracted mesh data
	return createdModel;
}

std::vector<MeshTexture> Model::LoadTextureMaterials(aiMaterial* material, aiTextureType textureType, std::string typeName)
{
	std::vector<MeshTexture> textures;

	for (GLuint i = 0; i < material->GetTextureCount(textureType); ++i)
	{
		aiString texturePath;
		material->GetTexture(textureType, i, &texturePath);

		// Check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		GLboolean isTextureLoaded = false;

		for (GLuint j = 0; j < texturesLoaded.size(); ++j)
		{
			// A texture with the same filepath has already been loaded, continue to next one. (optimization)
			if (texturesLoaded[j].path == texturePath)
			{
				textures.push_back(texturesLoaded[j]);
				isTextureLoaded = true;
				break;
			}
		}
		// If texture hasn't been loaded already, load it
		if (!isTextureLoaded)
		{
			MeshTexture texture;
			texture.id = CreateTextureFromFile(texturePath.C_Str(), this->directory);
			texture.type = typeName;
			texture.path = texturePath;
			textures.push_back(texture);

			// Store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
			this->texturesLoaded.push_back(texture);
		}
	}

	return textures;
}

GLint Model::CreateTextureFromFile(const char* path, std::string directory)
{
	//Generate texture ID and load texture data 
	std::string fileName = std::string(path);
	fileName = directory + '/' + fileName;

	std::cout << "texture filename: " << fileName << std::endl;

	GLuint textureID;
	glGenTextures(1, &textureID);
	int width, height;
	unsigned char* image = SOIL_load_image(fileName.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
	return textureID;
}