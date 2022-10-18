#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Display
{
public:
    GLFWwindow* window;
    GLuint trailMap;

    Display(const char* title);
    
    void InitScreen();
    void Update();
};
