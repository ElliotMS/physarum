#include "Display.h"
#include <iostream>

static void WindowResizeCallback(GLFWwindow * window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Display::Display(int width, int height, const char* title)
{
    windowWidth = width;
    windowHeight = height;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(windowWidth, windowHeight, title, NULL, NULL);
    
    if (!window)
    {
        glfwTerminate();
        std::cerr << "Error: Window creation failed " << std::endl;;
    }
    
    glfwMakeContextCurrent(window);
    glViewport(0, 0, windowWidth, windowHeight);
    glfwSetWindowSizeCallback(window, WindowResizeCallback);
    glfwSwapInterval(1);
}

void Display::InitScreen(int textureWidth, int textureHeight)
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

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0); // quadCoords
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float))); // texCoords
    glEnableVertexAttribArray(1);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Texture //
    glGenTextures(1, &screenTexture);
    glBindTexture(GL_TEXTURE_2D, screenTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, textureWidth, textureHeight, 0, GL_RGBA, GL_FLOAT, NULL);

    glBindImageTexture(0, screenTexture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
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
