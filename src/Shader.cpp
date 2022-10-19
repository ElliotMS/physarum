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
        std::cerr << "Error: Unable to load shader: " << filePath << std::endl;
        std::exit(-1);
    }

    return output;
}

GLuint Shader::CreateShader(const std::string& text, GLuint type)
{
    GLuint shader = glCreateShader(type);

    if (shader == 0)
        std::cerr << "Error: Failed to compile shader of type: " << type << std::endl;

    const GLchar* shaderSourceString[1];
    GLint shaderSourceStringLength[1];

    shaderSourceString[0] = text.c_str();
    shaderSourceStringLength[0] = text.length();

    glShaderSource(shader, 1, shaderSourceString, shaderSourceStringLength);
    glCompileShader(shader);

    return shader;
}

Shader::Shader(const std::string& vsFilePath, const std::string& fsFilePath)
{
    m_program = glCreateProgram();
    m_vertexShader = CreateShader(ParseShader(vsFilePath), GL_VERTEX_SHADER);
    m_fragmentShader = CreateShader(ParseShader(fsFilePath), GL_FRAGMENT_SHADER);
    glAttachShader(m_program, m_vertexShader);
    glAttachShader(m_program, m_fragmentShader);
    glLinkProgram(m_program);
}

Shader::Shader(const std::string& csFilePath)
{
    m_program = glCreateProgram();
    m_computeShader = CreateShader(ParseShader(csFilePath), GL_COMPUTE_SHADER);
    glAttachShader(m_program, m_computeShader);
    glLinkProgram(m_program);
}

void Shader::BindAgentUniforms()
{
    glProgramUniform1i(m_program, glGetUniformLocation(m_program, "width"), TEXTURE_WIDTH);
    glProgramUniform1i(m_program, glGetUniformLocation(m_program, "height"), TEXTURE_HEIGHT);
    glProgramUniform1i(m_program, glGetUniformLocation(m_program, "agentCount"), AGENT_COUNT);
    glProgramUniform1i(m_program, glGetUniformLocation(m_program, "stepSize"), STEP_SIZE);
    glProgramUniform1f(m_program, glGetUniformLocation(m_program, "sensorAngle"), SENSOR_ANGLE);
    glProgramUniform1f(m_program, glGetUniformLocation(m_program, "rotationAngle"), ROTATION_ANGLE);
    glProgramUniform1i(m_program, glGetUniformLocation(m_program, "sensorOffset"), SENSOR_OFFSET);
    glProgramUniform1i(m_program, glGetUniformLocation(m_program, "sensorSize"), SENSOR_SIZE);
    glProgramUniform1f(m_program, glGetUniformLocation(m_program, "trailColorR"), TRAIL_COLOR_R);
    glProgramUniform1f(m_program, glGetUniformLocation(m_program, "trailColorG"), TRAIL_COLOR_G);
    glProgramUniform1f(m_program, glGetUniformLocation(m_program, "trailColorB"), TRAIL_COLOR_B);
}

void Shader::BindDiffuseUniforms()
{
    glProgramUniform1i(m_program, glGetUniformLocation(m_program, "width"), TEXTURE_WIDTH);
    glProgramUniform1i(m_program, glGetUniformLocation(m_program, "height"), TEXTURE_HEIGHT);
}

void Shader::BindDecayUniforms()
{
    glProgramUniform1i(m_program, glGetUniformLocation(m_program, "width"), TEXTURE_WIDTH);
    glProgramUniform1i(m_program, glGetUniformLocation(m_program, "height"), TEXTURE_HEIGHT);
    glProgramUniform1i(m_program, glGetUniformLocation(m_program, "decaySpeed"), DECAY_SPEED);
}

void Shader::Dispath(GLuint x, GLuint y, GLuint z)
{
    glUseProgram(m_program);
    glDispatchCompute(x, y, z);
    glMemoryBarrier(GL_ALL_BARRIER_BITS);
}

void Shader::Use()
{
    glUseProgram(m_program);
}

Shader::~Shader()
{
    glDetachShader(m_program, m_vertexShader);
    glDetachShader(m_program, m_fragmentShader);
    glDetachShader(m_program, m_computeShader);
    glDeleteShader(m_vertexShader);
    glDeleteShader(m_fragmentShader);
    glDeleteShader(m_computeShader);
    glDeleteProgram(m_program);
}