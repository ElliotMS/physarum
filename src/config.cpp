#include "config.h"
#include <iostream>
#include <fstream>

INIReader config::settings;

void config::LoadSettings(const std::string filePath)
{
    settings = INIReader((filePath).c_str());
    int err = settings.ParseError();
    if (err != 0) {
        if (err == -1)
            std::cerr << "Unable to open configuration file: " << filePath << std::endl;
        else
            std::cerr << "Unable to parse configuration file: " << filePath << ". Error on line " << err << "." << std::endl;
        std::cerr << "Using default configuration values for obstructed/missing parameters." << std::endl;
    }
}

void config::BindRenderUniforms(GLuint program)
{
    glProgramUniform1i(program, glGetUniformLocation(program, "trailMap"), 0);
    glProgramUniform1i(program, glGetUniformLocation(program, "stimuliMap"), 1);
}

void config::BindAgentUniforms(GLuint program)
{
    glProgramUniform1i(program, glGetUniformLocation(program, "width"), TEXTURE_WIDTH);
    glProgramUniform1i(program, glGetUniformLocation(program, "height"), TEXTURE_HEIGHT);
    glProgramUniform1i(program, glGetUniformLocation(program, "agentCount"), AGENT_COUNT);
    glProgramUniform1i(program, glGetUniformLocation(program, "stepSize"), STEP_SIZE);
    glProgramUniform1f(program, glGetUniformLocation(program, "sensorAngle"), SENSOR_ANGLE);
    glProgramUniform1f(program, glGetUniformLocation(program, "rotationAngle"), ROTATION_ANGLE);
    glProgramUniform1i(program, glGetUniformLocation(program, "sensorOffset"), SENSOR_OFFSET);
    glProgramUniform1i(program, glGetUniformLocation(program, "sensorSize"), SENSOR_SIZE);
    glProgramUniform1f(program, glGetUniformLocation(program, "trailColorR"), TRAIL_COLOR_R);
    glProgramUniform1f(program, glGetUniformLocation(program, "trailColorG"), TRAIL_COLOR_G);
    glProgramUniform1f(program, glGetUniformLocation(program, "trailColorB"), TRAIL_COLOR_B);
    glProgramUniform1f(program, glGetUniformLocation(program, "killChance"), KILL_CHANCE);
}

void config::BindDiffuseUniforms(GLuint program)
{
    glProgramUniform1i(program, glGetUniformLocation(program, "width"), TEXTURE_WIDTH);
    glProgramUniform1i(program, glGetUniformLocation(program, "height"), TEXTURE_HEIGHT);
    glProgramUniform1i(program, glGetUniformLocation(program, "diffuseSize"), DIFFUSE_SIZE);
}

void config::BindDecayUniforms(GLuint program)
{
    glProgramUniform1i(program, glGetUniformLocation(program, "width"), TEXTURE_WIDTH);
    glProgramUniform1i(program, glGetUniformLocation(program, "height"), TEXTURE_HEIGHT);
    glProgramUniform1i(program, glGetUniformLocation(program, "decaySpeedR"), DECAY_SPEED_R);
    glProgramUniform1i(program, glGetUniformLocation(program, "decaySpeedG"), DECAY_SPEED_G);
    glProgramUniform1i(program, glGetUniformLocation(program, "decaySpeedB"), DECAY_SPEED_B);
}

void config::BindStimuliUniforms(GLuint program)
{
    glProgramUniform1i(program, glGetUniformLocation(program, "width"), TEXTURE_WIDTH);
    glProgramUniform1i(program, glGetUniformLocation(program, "height"), TEXTURE_HEIGHT);
    glProgramUniform1f(program, glGetUniformLocation(program, "stimWeight"), STIM_WEIGHT);
}