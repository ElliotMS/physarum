#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Window
{
public:
    bool paused = false;

    Window(const char* title);
    
    void Update();
    void TogglePause();
    bool ShouldClose();

private:
    GLFWwindow* p_window;
};
