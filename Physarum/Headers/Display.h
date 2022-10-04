#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Display
{
public:
    Display(const char* title);
    
    GLFWwindow* window;

    void InitScreen();
    void Update();

    GLuint trailMap;

};
