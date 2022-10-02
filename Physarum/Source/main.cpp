#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Display.h"
#include "Shader.h"
#include "Agent.h"
#include "Config.h"

int main(void)
{
    Config::Load("./Config/config.ini"); // Load configuration file

    // Initialize GLFW
    if (!glfwInit()) 
        return -1;

    Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "Simulation"); // Create window and context

    // Initialize GLEW
    if (glewInit() != GLEW_OK) { 
        std::cerr << "Failed to initialize GLEW " << std::endl; 
    }

    // Load and compile shaders 
    Shader renderShader(
        "./Resources/Shaders/vertex.glsl",
        "./Resources/Shaders/fragment.glsl"
    );

    Shader agentShader(
        "./Resources/Shaders/agent.glsl"
    );

    Shader decayShader(
        "./Resources/Shaders/decay.glsl"
    );

    Shader diffuseShader(
        "./Resources/Shaders/diffuse.glsl"
    );

    display.InitScreen(TEXTURE_WIDTH, TEXTURE_HEIGHT); // Creates full screen quad & trailmap texture
    Agent::Init(); // Intialize agents

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