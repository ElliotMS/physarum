#version 430 core

layout(local_size_x = 8, local_size_y = 8, local_size_z = 1) in;

layout(rgba32f, binding = 0) uniform image2D trailMap;

uniform int width;
uniform int height;
uniform int decaySpeed;

void main()
{
    ivec2 pixelPos = ivec2(gl_GlobalInvocationID.xy);
    if (pixelPos.x < 0 || pixelPos.x > width || pixelPos.y < 0 || pixelPos.y > height) return;
    vec4 currentValue = imageLoad(trailMap, pixelPos);
    vec4 decayedValue = max(
        vec4(0, 0, 0, 1.0),
        currentValue - vec4(0.001, 0.001, 0.001, 0.0) * decaySpeed
    );
        
    imageStore(trailMap, pixelPos, decayedValue);
}