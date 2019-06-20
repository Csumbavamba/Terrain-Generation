#pragma once

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <iostream>
#include <map>


class ShaderLoader
{
public:

	static ShaderLoader * GetInstance();

	
	GLuint CreateProgram(const char* VertexShaderFilename,
						const char* FragmentShaderFilename);

	GLuint CreateProgram(const char* VertexShaderFilename, 
		const char* GeometryShaderFileName,
		const char* FragmentShaderFilename);

	GLuint CreateProgram(const char* VertexShaderFilename,
		const char* TessalationControlShaderFileName,
		const char* TessalationEvaluationShaderFileName,
		const char* FragmentShaderFilename);

	GLuint CreateComputeProgram(const char* ComputeShaderFileName);

	static void ShutDown();

// Functions
private:
	// Singleton
	ShaderLoader(void);
	~ShaderLoader(void);
	ShaderLoader(const ShaderLoader& copy) {};
	ShaderLoader& operator= (const ShaderLoader& move) {};


	std::string ReadShader(const char *filename);
	GLuint CreateShader(GLenum shaderType,
		std::string source,
		const char* shaderName);

// Variables
private:

	static ShaderLoader * instance;

	std::map<std::string, GLuint> savedVertexShaders;
	std::map<std::string, GLuint> savedTessControlShaders;
	std::map<std::string, GLuint> savedTessEvaluationShaders;
	std::map<std::string, GLuint> savedFragmentShaders;
	std::map<std::string, GLuint> savedGeometryShaders;
	std::map<std::string, GLuint> savedComputeShaders;
	std::map<std::string, GLuint> savedPrograms;


};
