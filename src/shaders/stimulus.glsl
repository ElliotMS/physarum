#version 430 core

layout(local_size_x = 8, local_size_y = 8, local_size_z = 1) in;

layout(rgba32f, binding = 0) uniform image2D trailMap;
layout(rgba32f, binding = 1) uniform image2D stimulusMap;

uniform int width;
uniform int height;
uniform float stimWeight;

void main()
{
    ivec2 pixelPos = ivec2(gl_GlobalInvocationID.xy);
    if (pixelPos.x < 0 || pixelPos.x > width || pixelPos.y < 0 || pixelPos.y > height) return;
    vec4 currentValue = imageLoad(trailMap, pixelPos);
    vec4 stimulusValue = imageLoad(stimulusMap, pixelPos);
    imageStore(trailMap, pixelPos, currentValue + stimulusValue * stimWeight);
}