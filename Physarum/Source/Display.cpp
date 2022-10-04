#include "Display.h"
#include "Config.h"
#include <iostream>


static void WindowResizeCallback(GLFWwindow * window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Display::Display(const char* title)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(DISPLAY_WIDTH, DISPLAY_HEIGHT, title, NULL, NULL);
    
    if (!window)
    {
        glfwTerminate();
        std::cerr << "Error: Window creation failed " << std::endl;;
    }
    
    glfwMakeContextCurrent(window);
    glViewport(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);
    glfwSetWindowSizeCallback(window, WindowResizeCallback);
    glfwSwapInterval(1);
}

void Display::InitScreen()
{
    // Quad //
    float vertices[] = {
        // Positions        // Texture coords
        -1.0f,  1.0f,       0.0f, 1.0f,         // Top left
         1.0f,  1.0f,       1.0f, 1.0f,         // Top Right
        -1.0f, -1.0f,       0.0f, 0.0f,         // Bottom left
         1.0f, -1.0f,       1.0f, 0.0f          // Bottom right
    };

     unsigned int indices[] = {
        0, 1, 2,
        1, 2, 3
    };

    // Create and bind vertex buffer object
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create and bind vertex array object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Define how the VBO data should be interpreted
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);                   // Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float))); // Texture coords
    glEnableVertexAttribArray(1);

    // Create and bind element buffer object
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Texture //
    glGenTextures(1, &trailMap);
    glBindTexture(GL_TEXTURE_2D, trailMap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);

    glBindImageTexture(0, trailMap, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
}

void Display::Update()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Draw fullscreen quad
    glfwPollEvents();
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, 1);
    }
    glfwSwapBuffers(window);
}
