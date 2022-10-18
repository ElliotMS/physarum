#pragma once
#include <GL/glew.h>
#include <string>

class Shader
{
public:
	GLuint program;
	
	Shader(const std::string& vsFilePath, const std::string& fsFilePath);	// Contructor for render shaders
	Shader(const std::string& csFilePath);									// Contructor for compute shader

	void BindAgentUniforms();
	void BindDiffuseUniforms();
	void BindDecayUniforms();

	void Dispath(GLuint x, GLuint y, GLuint z);

	~Shader();

private:
	GLuint m_vertexShader;
	GLuint m_fragmentShader;
	GLuint m_computeShader;

	std::string ParseShader(const std::string& filePath);
	GLuint CreateShader(const std::string& text, GLuint type);
};

