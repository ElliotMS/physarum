#include "Window.h"
#include "config.h"
#include <iostream>

static void WindowResizeCallback(GLFWwindow * p_window, int width, int height)
{
    glViewport(0, 0, width, height);
}

static void KeyCallback(GLFWwindow* p_window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS) {
        switch (key) {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(p_window, 1);
            break;
        case GLFW_KEY_SPACE:
            
            break;
        // Easily add more macros with additional switch cases
        }
    }
}

Window::Window(const char* title)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    if (FULLSCREEN)
        p_window = glfwCreateWindow(DISPLAY_WIDTH, DISPLAY_HEIGHT, title, glfwGetPrimaryMonitor(), NULL);
    else
        p_window = glfwCreateWindow(DISPLAY_WIDTH, DISPLAY_HEIGHT, title, NULL, NULL);

    if (!p_window)
    {
        glfwTerminate();
        std::cerr << "Error: Window creation failed " << std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    glfwMakeContextCurrent(p_window);
    glViewport(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);
    glfwSetWindowSizeCallback(p_window, WindowResizeCallback);
    glfwSetKeyCallback(p_window, KeyCallback);
    glfwSetInputMode(p_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSwapInterval(1);
}

void Window::Update()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Draw fullscreen quad
    glfwPollEvents();
    glfwSwapBuffers(p_window);
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(p_window);
}