#include "Shader.h"
#include <iostream>
#include <fstream>

std::string Shader::ParseShader(const std::string& filePath)
{
    std::ifstream file;
    file.open((filePath).c_str());
    std::string output;

    if (file.is_open())
    {
        std::string line;

        while (file.good())
        {
            getline(file, line);
            output.append(line + "\n");
        }
    }
    else
    {
        std::cerr << "Unable to load shader: " << filePath << std::endl;
    }

    return output;
}

GLuint Shader::CreateShader(const std::string& text, unsigned int type)
{
    GLuint shader = glCreateShader(type);

    if (shader == 0)
        std::cerr << "Error compiling shader type " << type << std::endl;

    const GLchar* shaderSourceString[1];
    GLint shaderSourceStringLength[1];

    shaderSourceString[0] = text.c_str();
    shaderSourceStringLength[0] = text.length();

    glShaderSource(shader, 1, shaderSourceString, shaderSourceStringLength);
    glCompileShader(shader);

    return shader;
}

Shader::Shader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
{
    program = glCreateProgram();
    m_vertexShader = CreateShader(ParseShader(vertexShaderFilePath), GL_VERTEX_SHADER);
    m_fragmentShader = CreateShader(ParseShader(fragmentShaderFilePath), GL_FRAGMENT_SHADER);
    glAttachShader(program, m_vertexShader);
    glAttachShader(program, m_fragmentShader);
    glLinkProgram(program);
}

Shader::Shader(const std::string& computeShaderFilePath)
{
    program = glCreateProgram();
    m_computeShader = CreateShader(ParseShader(computeShaderFilePath), GL_COMPUTE_SHADER);
    glAttachShader(program, m_computeShader);
    glLinkProgram(program);
}

Shader::~Shader()
{
    glDetachShader(program, m_vertexShader);
    glDetachShader(program, m_fragmentShader);
    glDetachShader(program, m_computeShader);

    glDeleteShader(m_vertexShader);
    glDeleteShader(m_fragmentShader);
    glDeleteShader(m_computeShader);

    glDeleteProgram(program);
}