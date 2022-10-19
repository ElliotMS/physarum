#version 330 core

in vec2 texCoords;
uniform sampler2D trailMap;

out vec4 fragColor;

void main()
{
    fragColor = texture(trailMap, texCoords);
}