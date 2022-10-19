#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Display
{
public:
    GLFWwindow* window;
    Display(const char* title);
    
    void InitScreen();
    void Update();
private:
    GLuint m_trailMap;
};
