#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Window
{
public:
    Window(const char* title);
    
    void Update();
    bool ShouldClose();

private:
    GLFWwindow* p_window;
};
