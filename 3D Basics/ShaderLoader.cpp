#include "ShaderLoader.h" 
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

ShaderLoader * ShaderLoader::instance = NULL;

ShaderLoader * ShaderLoader::GetInstance()
{
	if (instance == NULL)
	{
		instance = new ShaderLoader();
	}
	return instance;
}

ShaderLoader::ShaderLoader(){}
ShaderLoader::~ShaderLoader()
{
	savedVertexShaders.clear();
	savedFragmentShaders.clear();
	savedPrograms.clear();
}


std::string ShaderLoader::ReadShader(const char *filename)
{
	std::string shaderCode;
	std::ifstream file(filename, std::ios::in);

	if (!file.good()){
		std::cout << "Can't read file " << filename << std::endl;
		std::terminate();
	}

	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

GLuint ShaderLoader::CreateShader(GLenum shaderType, std::string
	source, const char* shaderName)
{

	int compile_result = 0;

	GLuint shader = glCreateShader(shaderType);
	const char *shader_code_ptr = source.c_str();
	const int shader_code_size = source.size();

	glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);

	//check for errors
	if (compile_result == GL_FALSE)
	{

		int info_log_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> shader_log(info_log_length);
		glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
		std::cout << "ERROR compiling shader: " << shaderName << std::endl << &shader_log[0] << std::endl;
		return 0;
	}
	return shader;
}




GLuint ShaderLoader::CreateProgram(const char* vertexShaderFilename,
	const char* fragmentShaderFilename)
{
	// Check if the shaders exist
	GLuint program;
	GLuint vertexShader;
	GLuint fragmentShader;

	std::string vertexShaderCode;
	std::string fragmentShaderCode;

	std::map<std::string, GLuint>::iterator vertexIterator;
	std::map<std::string, GLuint>::iterator fragmentIterator;
	std::map<std::string, GLuint>::iterator programIterator;

	std::string programName = vertexShaderFilename;
	programName.append(fragmentShaderFilename);

	programIterator = savedPrograms.find(programName);

	// If the program doesn't exist
	if (programIterator == savedPrograms.end())
	{
		// Search for already existing vertex shader
		vertexIterator = savedVertexShaders.find(vertexShaderFilename);

		// If vertex shader exist
		if (vertexIterator == savedVertexShaders.end())
		{
			// Create vertex shader
			vertexShaderCode = ReadShader(vertexShaderFilename); //read the shader files and save the code
			vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderCode, "vertex shader");
			savedVertexShaders[vertexShaderFilename] = vertexShader;
		}
		else
		{
			vertexShader = vertexIterator->second; // = savedVertex
		}

		// Search for already existing fragment shader
		fragmentIterator = savedFragmentShaders.find(fragmentShaderFilename);

		// If fragment shader exist doesn't exist
		if (fragmentIterator == savedFragmentShaders.end())
		{
			// Create fragment shader
			fragmentShaderCode = ReadShader(fragmentShaderFilename); //read the shader files and save the code
			fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderCode, "fragment shader");
			savedFragmentShaders[fragmentShaderFilename] = fragmentShader;
		}
		else
		{
			fragmentShader = fragmentIterator->second;
		}

		// Create program
		int link_result = 0;
		//create the program handle, attatch the shaders and link it
		program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &link_result);

		//check for link errors
		if (link_result == GL_FALSE)
		{

			int info_log_length = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
			std::vector<char> program_log(info_log_length);
			glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
			std::cout << "Shader Loader : LINK ERROR" << std::endl << &program_log[0] << std::endl;
			return 0;
		}

		savedPrograms[programName] = program;
	}
	else
	{
		// Load program
		program = programIterator->second;
	}


	
	return program;
}

void ShaderLoader::ShutDown()
{
	delete instance;
	instance = NULL;
}


