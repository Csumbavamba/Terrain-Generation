#pragma once
#include "Mesh.h"

#include <vector>
#include <algorithm>
#include <string>

struct VertexInfo
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoordinate;
};

class Mesh_Terrain : public Mesh
{
public:
	// Only works with .Raw file
	Mesh_Terrain(GameObject* owner, std::string heighMapFile);
	Mesh_Terrain(GameObject* owner);
	virtual ~Mesh_Terrain() {};

	virtual void Initialise() override;

	float GetHeightAt(float x, float z);
	float GetWidth() const;
	float GetDepth() const;


// Functions
private:
	void CreatePerlinNoise(int count, float seed, int octaves);
	void BuildVertexBuffer();
	void BuildIndexBuffer();
	void GenerateTerrain();
	void LoadHeightMap();
	void SmoothTerrain();
	bool IsInBounds(GLuint x, GLuint y);
	float Average(GLuint i, GLuint j);

// Variables
private:

	// Mesh Creation
	int numberOfVerticies;
	int numberOfFaces;
	GLuint numberOfRows = NULL;
	GLuint numberOfColumns = NULL;
	float cellSpacing;

	// Height info
	std::vector<float> heightMap;
	std::string heightMapFileName;
	float heightScale;
	float heightOffset;
	

	
};

