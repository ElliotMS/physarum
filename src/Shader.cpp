#include <iostream>
#include <fstream>
#include "Shader.h"
#include "config.h"

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

GLuint Shader::CreateShader(const std::string& text, GLuint type)
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

void Shader::BindAgentUniforms()
{
    glProgramUniform1i(program, glGetUniformLocation(program, "width"), TEXTURE_WIDTH);
    glProgramUniform1i(program, glGetUniformLocation(program, "height"), TEXTURE_HEIGHT);
    glProgramUniform1i(program, glGetUniformLocation(program, "agentCount"), AGENT_COUNT);
    glProgramUniform1i(program, glGetUniformLocation(program, "stepSize"), STEP_SIZE);
    glProgramUniform1f(program, glGetUniformLocation(program, "sensorAngle"), SENSOR_ANGLE * (3.14159265359 / 180));
    glProgramUniform1f(program, glGetUniformLocation(program, "rotationAngle"), ROTATION_ANGLE * (3.14159265359 / 180));
    glProgramUniform1i(program, glGetUniformLocation(program, "sensorOffset"), SENSOR_OFFSET);
    glProgramUniform1i(program, glGetUniformLocation(program, "sensorSize"), SENSOR_SIZE);
    glProgramUniform1f(program, glGetUniformLocation(program, "trailColorR"), TRAIL_COLOR_R);
    glProgramUniform1f(program, glGetUniformLocation(program, "trailColorG"), TRAIL_COLOR_G);
    glProgramUniform1f(program, glGetUniformLocation(program, "trailColorB"), TRAIL_COLOR_B);
}

void Shader::BindDiffuseUniforms()
{
    glProgramUniform1i(program, glGetUniformLocation(program, "width"), TEXTURE_WIDTH);
    glProgramUniform1i(program, glGetUniformLocation(program, "height"), TEXTURE_HEIGHT);
}

void Shader::BindDecayUniforms()
{
    glProgramUniform1i(program, glGetUniformLocation(program, "width"), TEXTURE_WIDTH);
    glProgramUniform1i(program, glGetUniformLocation(program, "height"), TEXTURE_HEIGHT);
    glProgramUniform1i(program, glGetUniformLocation(program, "decaySpeed"), DECAY_SPEED);
}

void Shader::Dispath(GLuint x, GLuint y, GLuint z)
{
    glUseProgram(program);
    glDispatchCompute(x, y, z);
    glMemoryBarrier(GL_ALL_BARRIER_BITS);
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