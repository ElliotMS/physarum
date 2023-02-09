#pragma once
#include <GL/glew.h>
#include "config.h"

namespace quad
{
    void Init()
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
        GLuint VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Create and bind vertex array object
        GLuint VAO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        // Define how the VBO data should be interpreted
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);                   // Positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float))); // Texture coords
        glEnableVertexAttribArray(1);

        // Create and bind element buffer object
        GLuint EBO;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    };
};