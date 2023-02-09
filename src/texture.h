#pragma once
#include <GL/glew.h>
#include "config.h"

namespace texture
{
    GLuint trailMap;
    GLuint stimulusMap;

    static void InitTexture(GLuint texture, GLint location, GLuint unit)
    {
        glActiveTexture(location);
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
        glBindImageTexture(unit, texture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
    }

    void InitTrailMap()
    {
        InitTexture(trailMap, GL_TEXTURE0, 0);
    }

    void InitStimulusMap()
    {
        InitTexture(stimulusMap, GL_TEXTURE1, 1);
    }
};