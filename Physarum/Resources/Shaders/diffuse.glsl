#version 430 core

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout(rgba32f, binding = 0) uniform image2D trailMap;

void main()
{
    ivec2 pixelPos = ivec2(gl_GlobalInvocationID.xy);
    vec4 sum = vec4(0.0);

    for (int i = -1; i <= 1; i++) {                  // Loop X offsets
        for (int j = -1; j <= 1; j++) {              // Loop Y offsets
            ivec2 pos = pixelPos + ivec2(i, j);
            sum += imageLoad(trailMap, pos);
        }
    }
    
    vec4 average = sum / 9.0;
    imageStore(trailMap, pixelPos, average);
}