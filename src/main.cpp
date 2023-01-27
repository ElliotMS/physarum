#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Window.h"
#include "Shader.h"
#include "config.h"
#include "debug.h"
#include "agent_buffer.h"
#include "trail_map.h"

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
    Shader stimuliShader("../src/shaders/stimuli.glsl");
    
    // Bind shader uniform variables
    config::BindRenderUniforms(renderShader.program);
    config::BindAgentUniforms(agentShader.program);
    config::BindDiffuseUniforms(diffuseShader.program);
    config::BindDecayUniforms(decayShader.program);
    config::BindStimuliUniforms(stimuliShader.program);
    
    trail_map::Init(); // Creates full screen quad & trailmap texture
    agent_buffer::Init(); // Intialize and bind agent buffer 

    // Main loop
    while (!window.ShouldClose())
    {
        if(!window.paused) {
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