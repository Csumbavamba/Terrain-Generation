#include "Mesh_Terrain.h"

#include <fstream>
#include <sstream>


Mesh_Terrain::Mesh_Terrain(GameObject * owner)
{
	this->owner = owner;

	numberOfRows = 513;
	numberOfColumns = 513;
	cellSpacing = 1.0f;
	indexCount = 0;
	heightScale = 0.1f;
	heightOffset = 0.0f;

	heightMapFileName = "HeigthMaps/coastMountain513.raw"; // TODO Add Functionality to enable PNG height maps
}


void Mesh_Terrain::Initialise()
{
	// Calculate vertex and face count
	numberOfVerticies = numberOfRows * numberOfColumns;
	numberOfFaces = (numberOfRows - 1) * (numberOfColumns - 1) * 2;

	// Load the height Map
	LoadHeightMap();
	SmoothTerrain();

	// Build Buffers
	BuildVertexBuffer();
	BuildIndexBuffer();
}

float Mesh_Terrain::GetHeightAt(float x, float z)
{
	// Transform from terrain local space to "cell" space.
	float cellX = (x + 0.5f * GetWidth()) / cellSpacing;
	float cellZ = (z - 0.5f * GetDepth()) / -cellSpacing;

	// Get the row and column we are in.
	int row = (int)floorf(cellZ);
	int col = (int)floorf(cellX);


	// Grab the heights of the cell we are in.
	float topLeft = heightMap[row * numberOfColumns + col];
	float topRight = heightMap[row * numberOfColumns + col + 1];
	float bottomLeft = heightMap[(row + 1) * numberOfColumns + col];
	float bottomRight = heightMap[(row + 1) * numberOfColumns + col + 1];

	// Where we are relative to the cell.
	float currentX = cellX - (float)col;
	float currentY = cellZ - (float)row;

	// If upper triangle ABC.
	if (currentX + currentY <= 1.0f)
	{
		float uy = topRight - topLeft;
		float vy = bottomLeft - topLeft;
		return (topLeft + currentX * uy + currentY * vy);
	}
	else // lower triangle DCB.
	{
		float uy = bottomLeft - bottomRight;
		float vy = topRight - bottomRight;
		return (bottomRight + (1.0f - currentX) * uy + (1.0f - currentY) * vy);
	}
}

float Mesh_Terrain::GetWidth() const
{
	return (numberOfColumns - 1) * cellSpacing;
}

float Mesh_Terrain::GetDepth() const
{
	return (numberOfRows - 1) * cellSpacing;
}

void Mesh_Terrain::BuildVertexBuffer()
{
	// Create a vector to store the vertices
	std::vector<VertexInfo> vertices(numberOfVerticies);

	// Enable centering the terrain
	float terrainHalfWidth = (numberOfColumns - 1) * cellSpacing * 0.5f;
	float terrainHalfDepth = (numberOfRows - 1) * cellSpacing * 0.5f;

	// Calculate the step of width and height
	float textureU = 1.0f / (numberOfColumns - 1);
	float textureV = 1.0f / (numberOfRows - 1);

	// Iterate through the steps and create vertices
	for (GLuint i = 0; i < numberOfRows; ++i)
	{
		// Add depth Value - Z is negative forward
		float positionZ = terrainHalfDepth - i * cellSpacing;

		for (GLuint j = 0; j < numberOfColumns; ++j)
		{
			// Add width value
			float positionX = -terrainHalfWidth + j * cellSpacing;

			float positionY = heightMap[i * numberOfColumns + j];

			// Set verticies
			vertices[i * numberOfColumns + j].position = glm::vec3(positionX, positionY, positionZ);
			vertices[i * numberOfColumns + j].normal = glm::vec3(0.0f, 1.0f, 0.0f);

			// Set texture coordinates - TODO this might need fixing
			vertices[i * numberOfColumns + j].texCoordinate.x = textureU * j;
			vertices[i * numberOfColumns + j].texCoordinate.y = textureV * i;

		}
	}

	// Estimate normals for interior nodes using central difference.
	float invTwoDX = 1.0f / (2.0f * cellSpacing);
	float invTwoDZ = 1.0f / (2.0f * cellSpacing);

	for (GLuint i = 2; i < numberOfRows - 1; ++i)
	{
		for (GLuint j = 2; j < numberOfColumns - 1; ++j)
		{
			float t = heightMap[(i - 1) * numberOfColumns + j];
			float b = heightMap[(i + 1) * numberOfColumns + j];
			float l = heightMap[i * numberOfColumns + j - 1];
			float r = heightMap[i * numberOfColumns + j + 1];

			glm::vec3 tanZ(0.0f, (t - b) * invTwoDZ, 1.0f);
			glm::vec3 tanX(1.0f, (r - l) * invTwoDX, 0.0f);

			glm::vec3 normal;
			normal = glm::cross(tanZ, tanX);
			normal = glm::normalize(normal);

			vertices[i * numberOfColumns + j].normal = normal;
		}
	}

	// Convert DirectX format to open GL
	std::vector<GLfloat> openGLVertices(numberOfVerticies * 8);

	int vertex = 0;

	for (GLuint i = 0; i < numberOfRows; i++)
	{
		for (GLuint j = 0; j < numberOfColumns; j++)
		{
			// Positions
			openGLVertices[vertex + 0] = vertices[i * numberOfColumns + j].position.x;
			openGLVertices[vertex + 1] = vertices[i * numberOfColumns + j].position.y;
			openGLVertices[vertex + 2] = vertices[i * numberOfColumns + j].position.z;

			// Normals
			openGLVertices[vertex + 3] = vertices[i * numberOfColumns + j].normal.x;
			openGLVertices[vertex + 4] = vertices[i * numberOfColumns + j].normal.y;
			openGLVertices[vertex + 5] = vertices[i * numberOfColumns + j].normal.z;

			// Texture coordinates
			openGLVertices[vertex + 6] = vertices[i * numberOfColumns + j].texCoordinate.x;
			openGLVertices[vertex + 7] = vertices[i * numberOfColumns + j].texCoordinate.y;

			vertex += 8;
		}
	}


	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, numberOfVerticies * 8 * sizeof(openGLVertices[0]), &openGLVertices[0], GL_STATIC_DRAW);

	// Binding Vertext attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	

}

void Mesh_Terrain::BuildIndexBuffer()
{
	// Create a vector to store the Indicies (3 indicies per face)
	std::vector<GLuint> indices(numberOfFaces * 3);

	// Iterate through each quad and compute indicies
	int quadIndex = 0;

	for (GLuint i = 0; i < numberOfRows - 1; ++i)
	{
		for (GLuint j = 0; j < numberOfColumns - 1; ++j)
		{
			indices[quadIndex] = i * numberOfColumns + j;
			indices[quadIndex + 1] = i * numberOfColumns + j + 1;
			indices[quadIndex + 2] = (i + 1) * numberOfColumns + j;

			indices[quadIndex + 3] = (i + 1) * numberOfColumns + j;
			indices[quadIndex + 4] = i * numberOfColumns + j + 1;
			indices[quadIndex + 5] = (i + 1) * numberOfColumns + j + 1;
			
			quadIndex += 6;
		}
	}

	// EBO
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfFaces * 3 * sizeof(GLuint),	&indices[0], GL_STATIC_DRAW);

	indexCount = numberOfFaces * 3;

}

void Mesh_Terrain::LoadHeightMap()
{
	// Create a height value for each vertex
	std::vector<unsigned char> loadedHeightMap(numberOfRows * numberOfColumns);

	// Open File
	std::ifstream inFile;
	inFile.open(heightMapFileName.c_str(), std::ios_base::binary);

	// If the file has opened
	if (inFile)
	{
		// Read the RAW bytes.
		inFile.read((char*)&loadedHeightMap[0], (std::streamsize)loadedHeightMap.size());

		// Done with file.
		inFile.close();
	}

	// Copy the array data into a float array, and scale and offset the heights.
	heightMap.resize(numberOfRows * numberOfColumns, 0);
	for (GLuint i = 0; i < numberOfRows * numberOfColumns; ++i)
	{
		heightMap[i] = (float)loadedHeightMap[i] * heightScale + heightOffset;
	}

}

void Mesh_Terrain::SmoothTerrain()
{
	std::vector<float> smoothHeightMap(heightMap.size());

	for (GLuint i = 0; i < numberOfRows; ++i)
	{
		for (GLuint j = 0; j < numberOfColumns; ++j)
		{
			smoothHeightMap[i * numberOfColumns + j] = Average(i, j);
		}
	}

	heightMap = smoothHeightMap;
}

bool Mesh_Terrain::IsInBounds(GLuint x, GLuint y)
{
	// True if the indices are valid
	return	(x >= 0 && x < numberOfRows && y >= 0 && y < numberOfColumns);
}

float Mesh_Terrain::Average(GLuint i, GLuint j)
{
	// Function computes the average height of the ij element.
	// It averages itself with its eight neighbor pixels.  Note
	// that if a pixel is missing neighbor, we just don't include it
	// in the average--that is, edge pixels don't have a neighbor pixel.
	//
	// ----------
	// | 1| 2| 3|
	// ----------
	// |4 |ij| 6|
	// ----------
	// | 7| 8| 9|
	// ----------

	float average = 0.0f;
	float numberOfElements = 0.0f;

	for (GLuint m = i - 1; m <= i + 1; ++m)
	{
		for (GLuint n = j - 1; n <= j + 1; ++n)
		{
			if (IsInBounds(m, n))
			{
				average += heightMap[m * numberOfColumns + n];
				numberOfElements += 1.0f;
			}
		}
	}

	return average / numberOfElements;
}
