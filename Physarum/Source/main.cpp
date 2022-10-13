#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Display.h"
#include "Shader.h"
#include "Agent.h"
#include "Config.h"

void GLAPIENTRY DebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n", (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),type, severity, message);
}

int main(void)
{
    Config::Load("./Config/config.ini"); // Load configuration file

    // Initialize GLFW
    if (!glfwInit()) 
        return -1;

    Display display("Simulation"); // Create window and context

    // Initialize GLEW
    if (glewInit() != GLEW_OK) { 
        std::cerr << "Failed to initialize GLEW " << std::endl; 
    }

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(DebugMessageCallback, 0);

    // Load and compile shaders 
    Shader renderShader(
        "./Shaders/vertex.glsl",
        "./Shaders/fragment.glsl"
    );

    Shader agentShader(
        "./Shaders/agent.glsl"
    );

    Shader decayShader(
        "./Shaders/decay.glsl"
    );

    Shader diffuseShader(
        "./Shaders/diffuse.glsl"
    );

    display.InitScreen(); // Creates full screen quad & trailmap texture
    Agent::Init(); // Intialize agents

    // Agent shader uniform variables
    glProgramUniform1i(agentShader.program, glGetUniformLocation(agentShader.program, "width"), TEXTURE_WIDTH);
    glProgramUniform1i(agentShader.program, glGetUniformLocation(agentShader.program, "height"), TEXTURE_HEIGHT);
    glProgramUniform1i(agentShader.program, glGetUniformLocation(agentShader.program, "stepSize"), STEP_SIZE);

    // Decay shader uniform variables
    glProgramUniform1i(decayShader.program, glGetUniformLocation(decayShader.program, "decaySpeed"), DECAY_SPEED);

    // Diffuse shader uniform variables
    glProgramUniform1i(diffuseShader.program, glGetUniformLocation(diffuseShader.program, "width"), TEXTURE_WIDTH);
    glProgramUniform1i(diffuseShader.program, glGetUniformLocation(diffuseShader.program, "height"), TEXTURE_HEIGHT);

    while (!glfwWindowShouldClose(display.window))
    {
        glUseProgram(diffuseShader.program);
        glDispatchCompute(TEXTURE_WIDTH, TEXTURE_HEIGHT, 1); // NEED TO OPTIMIZE WORK GROUPS
        glMemoryBarrier(GL_ALL_BARRIER_BITS);

        glUseProgram(decayShader.program);
        glDispatchCompute(TEXTURE_WIDTH, TEXTURE_HEIGHT, 1); // NEED TO OPTIMIZE WORK GROUPS
        glMemoryBarrier(GL_ALL_BARRIER_BITS);

        glUseProgram(agentShader.program);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, Agent::buffer);
        glDispatchCompute(AGENT_COUNT/32, 1, 1); // NEED TO OPTIMIZE WORK GROUPS
        glMemoryBarrier(GL_ALL_BARRIER_BITS);

        glUseProgram(renderShader.program);
        display.Update();
    }

    glfwTerminate();
    return 0;
}