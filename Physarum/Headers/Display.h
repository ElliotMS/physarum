#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Display
{
public:
    Display(int width, int height, const char* title);
    
    GLFWwindow* window;

    int windowWidth;
    int windowHeight;

    void InitScreen(int textureWidth, int textureHeight);
    void Update();

    GLuint screenTexture;

};
