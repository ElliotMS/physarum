#version 430 core

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout(rgba32f, binding = 0) uniform image2D trailMap;

uniform int decaySpeed;

void main()
{
    ivec2 pixelPos = ivec2(gl_GlobalInvocationID.xy);
    vec4 currentValue = imageLoad(trailMap, pixelPos);
    vec4 decayedValue = currentValue - vec4(0.001, 0.001, 0.001, 0.0) * decaySpeed;
    
    imageStore(trailMap, pixelPos, decayedValue);
}