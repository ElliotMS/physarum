#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include "Window.h"
#include "Shader.h"
#include "config.h"
#include "debug.h"
#include "texture.h"
#include "quad.h"
#include "time_ms.h"
#include "agent_buffer.h"

int main(void)
{
    config::LoadSettings("../config/settings.ini"); // Load configuration file
    
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Error: Failed to initialize GLFW " << std::endl;
        return EXIT_FAILURE;
    }
    
    Window window("Simulation"); // Create window and context
    
    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Error: Failed to initialize GLEW " << std::endl;
        return EXIT_FAILURE;
    }
    
    // Enable KHR_debug output and set callback function
    debug::Enable();
    
    // Parse, compile and attach shaders to programs
    Shader renderShader("../src/shaders/vertex.glsl","../src/shaders/fragment.glsl");
    Shader agentShader("../src/shaders/agent.glsl");
    Shader diffuseShader("../src/shaders/diffuse.glsl");
    Shader decayShader("../src/shaders/decay.glsl");
    Shader stimuliShader("../src/shaders/stimulus.glsl");
    
    // Bind shader uniform variables
    config::BindRenderUniforms(renderShader.program);
    config::BindAgentUniforms(agentShader.program);
    config::BindDiffuseUniforms(diffuseShader.program);
    config::BindDecayUniforms(decayShader.program);
    config::BindStimulusUniforms(stimuliShader.program);
    
    // Initialize fullscreen quad, trail/stimulus-textures and agent buffer
    quad::Init();
    texture::InitTrailMap(); 
    texture::InitStimulusMap(); 
    agent_buffer::Init(); 

    // Main loop
    while (!window.ShouldClose())
    {
        if(!window.paused) {
            glProgramUniform1ui(agentShader.program, glGetUniformLocation(agentShader.program, "time"), time_ms::Get());
            stimuliShader.Dispath(TEXTURE_WIDTH, TEXTURE_HEIGHT, 1);
            diffuseShader.Dispath(TEXTURE_WIDTH, TEXTURE_HEIGHT, 1);
            agentShader.Dispath(AGENT_COUNT / 128, 1, 1);
            decayShader.Dispath(TEXTURE_WIDTH, TEXTURE_HEIGHT, 1);
            renderShader.Use();
        }
        window.Update();
    }
    
    // Once window is closed terminate program
    glfwTerminate();
    return EXIT_SUCCESS;
}