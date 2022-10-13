#version 430 core

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout(rgba32f, binding = 0) uniform image2D trailMap;

uniform int width;
uniform int height;

void main()
{
    ivec2 pixelPos = ivec2(gl_GlobalInvocationID.xy);
    vec4 sum = vec4(0.0);
    int sumCount = 0;

    for (int i = -1; i <= 1; i++) { // Loop X offsets
        for (int j = -1; j <= 1; j++) { // Loop Y offsets
            ivec2 currentPos = pixelPos + ivec2(i, j);
            if (!(currentPos.x < 0 || currentPos.y < 0 || currentPos.x >= width || currentPos.y >= height)) { // Out of bounds check
                sum += imageLoad(trailMap, currentPos);
                sumCount += 1;
            }       
        }
    }
    
    vec4 average = sum / sumCount;
    imageStore(trailMap, pixelPos, average);
}