#version 430 core

layout(local_size_x = 32, local_size_y = 1, local_size_z = 1) in;

layout(rgba32f, binding = 0) uniform image2D trailMap;

struct Agent {
    float x;
    float y;
    float angle;
};

layout(std430, binding = 1) buffer Agents {
    Agent agents[];
};

float random(vec2 co) {
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

void main()
{
    int ID = int(gl_GlobalInvocationID.x);
    Agent agent = agents[ID];


    vec2 direction = vec2(cos(agent.angle), sin(agent.angle));
    vec2 newPos = vec2(agent.x, agent.y) + direction;

    if (newPos.x < 0 || newPos.x > 1920.0 || newPos.y < 0 || newPos.y > 1080.0) // Need to get texture size from cpu
    {
        newPos.x = agent.x - 0.01;
        newPos.y = agent.y - 0.01;
        agents[ID].angle = random(vec2(agent.x + ID, agent.y)) * 2 * 3.1415;    // Need better seed
    }

    vec4 trailColor = vec4(1.0, 1.0, 1.0, 1.0);
    imageStore(trailMap, ivec2(agent.x, agent.y), trailColor);

    agents[ID].x = newPos.x;
    agents[ID].y = newPos.y;
}
