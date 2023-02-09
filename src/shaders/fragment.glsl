#version 330 core

in vec2 texCoords;
uniform sampler2D trailMap;
uniform sampler2D stimulusMap;

out vec4 fragColor;

void main()
{
    fragColor = mix(texture(trailMap, texCoords), texture(stimulusMap, texCoords), 0);
}