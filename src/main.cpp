#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Display.h"
#include "Shader.h"
#include "agent_buffer.h"
#include "config.h"

void GLAPIENTRY DebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n", (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
}

int main(void)
{
    config::Load("../config/settings.ini"); // Load configuration file

    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Error: Failed to initialize GLFW " << std::endl;
        return -1;
    }

    Display display("Simulation"); // Create window and context

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Error: Failed to initialize GLEW " << std::endl;
        return -1;
    }

    // Enable KHR_debug output and set callback function
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(DebugMessageCallback, 0);

    // Parse, compile and attach shaders to programs
    Shader renderShader("../src/shaders/vertex.glsl","../src/shaders/fragment.glsl");
    Shader agentShader("../src/shaders/agent.glsl");
    Shader diffuseShader("../src/shaders/diffuse.glsl");
    Shader decayShader("../src/shaders/decay.glsl");

    // Bind shader uniform variables
    agentShader.BindAgentUniforms();
    diffuseShader.BindDiffuseUniforms();
    decayShader.BindDecayUniforms();

    display.InitScreen(); // Creates full screen quad & trailmap texture
    agent_buffer::Init(); // Intialize and bind agent buffer 

    // Main loop
    while (!glfwWindowShouldClose(display.window))
    {
        diffuseShader.Dispath(TEXTURE_WIDTH, TEXTURE_HEIGHT, 1);
        agentShader.Dispath(AGENT_COUNT / 128, 1, 1);
        decayShader.Dispath(TEXTURE_WIDTH, TEXTURE_HEIGHT, 1);
        renderShader.Use();
        display.Update();
    }

    glfwTerminate();
    return 0;
}