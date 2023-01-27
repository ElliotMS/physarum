#pragma once
#include <GL/glew.h>
#include <algorithm>
#include <random>
#include "config.h"

namespace trail_map
{
	GLuint texture;
    GLuint texture2;

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

        // Texture 
        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
        glBindImageTexture(0, texture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);

        // Texture 2
        glActiveTexture(GL_TEXTURE1);
        glGenTextures(1, &texture2);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
        glBindImageTexture(1, texture2, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
	};
};