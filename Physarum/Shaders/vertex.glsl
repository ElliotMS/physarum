#version 330 core

layout(location = 0) in vec2 positions;
layout(location = 1) in vec2 textureCoords;

out vec2 texCoords;

void main()
{
    gl_Position = vec4(positions.x, positions.y, 0.0, 1.0);
    texCoords = textureCoords;
}