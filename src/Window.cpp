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
            //Window::paused = true;
            Window* window= reinterpret_cast<Window*>(glfwGetWindowUserPointer(p_window));
            if (window) window->TogglePause();
            break;
        }
    }
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        float ratioX = DISPLAY_WIDTH / TEXTURE_WIDTH;
        float ratioY = DISPLAY_HEIGHT / TEXTURE_HEIGHT;

        glActiveTexture(GL_TEXTURE1);
        float data[4] = {1.0, 1.0, 1.0, 1.0};
        
        int r = STIM_RADIUS;
        for (int y = -r; y <= r; y++)
            for (int x = -r; x <= r; x++)
                if (x * x + y * y <= r * r) {
                    int xOffset = int(xpos / ratioX) + x;
                    int yOffset = (TEXTURE_HEIGHT - int(ypos / ratioY)) + y;
                    
                    if(xOffset >= TEXTURE_WIDTH || xOffset < 0 || yOffset >= TEXTURE_HEIGHT || yOffset < 0) continue;
                    
                    glTexSubImage2D(
                        GL_TEXTURE_2D,
                        0,
                        xOffset,
                        yOffset,
                        1,
                        1,
                        GL_RGBA,
                        GL_FLOAT,
                        (void*)data
                    );
                }
    }
}

Window::Window(const char* title)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

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
    glfwSetMouseButtonCallback(p_window, MouseButtonCallback);
    //glfwSetInputMode(p_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSwapInterval(1);

    //testing
    glfwSetWindowUserPointer(p_window, reinterpret_cast<void*>(this));
}

void Window::Update()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Draw fullscreen quad
    glfwPollEvents();
    glfwSwapBuffers(p_window);
}

void Window::TogglePause()
{
    Window::paused = !Window::paused;
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(p_window);
}