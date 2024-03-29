#version 430 core

layout(local_size_x = 128, local_size_y = 1, local_size_z = 1) in;

layout(rgba32f, binding = 0) uniform image2D trailMap;

uniform int width;
uniform int height;
uniform int agentCount;
uniform int stepSize;
uniform float sensorAngle;
uniform float rotationAngle;
uniform int sensorOffset;
uniform int sensorSize;
uniform float trailColorR;
uniform float trailColorG;
uniform float trailColorB;
uniform float killChance;
uniform uint time;

const float PI = 3.14159265359;

struct Agent {
    float x;
    float y;
    float angle;
    bool alive;
};

layout(std430, binding = 1) buffer Agents {
    Agent agents[];
};

uint Hash(uint s)
{
    s ^= 2747636419u;
    s *= 2654435769u;
    s ^= s >> 16;
    s *= 2654435769u;
    s ^= s >> 16;
    s *= 2654435769u;
    return s;
}

float Random(uint s)
{
    return Hash(s) / 4294967295.0;
}

float Sense(Agent agent, float sensorAngle) {
    float localSensorAngle = agent.angle + sensorAngle; 
    vec2 sensorDir = vec2(cos(localSensorAngle), sin(localSensorAngle));
    ivec2 sensorPos = ivec2(agent.x + sensorDir.x * sensorOffset, agent.y + sensorDir.y * sensorOffset);

    vec4 sum = vec4(0.0);
    for (int i = -sensorSize; i <= sensorSize; i++) { // Loop X offsets
        for (int j = -sensorSize; j <= sensorSize; j++) { // Loop Y offsets
            ivec2 pos = sensorPos + ivec2(i, j);
            if (!(pos.x < 0 || pos.y < 0 || pos.x >= width || pos.y >= height)) { // Out of bounds check
                sum += imageLoad(trailMap, pos);
            }       
        }
    }

    return sum.x + sum.y + sum.z;
}

void Turn(int ID) {
    Agent agent = agents[ID];
    float weightFront = Sense(agent, 0);
    float weightRight = Sense(agent, -sensorAngle);
    float weightLeft = Sense(agent, sensorAngle);

    if (weightFront > weightRight && weightFront > weightLeft){
        // Don't turn
        agents[ID].angle += 0;
    } 
    else if (weightFront < weightRight && weightFront < weightLeft) {
        //Turn randomly left or right
        if (Random(uint(agent.y * width + agent.x + Hash(uint(ID + time * 100000)))) > 0.5) {
            agents[ID].angle -= rotationAngle;
        } else {
            agents[ID].angle += rotationAngle;
        }
    } 
    else if (weightRight > weightLeft) {
        // Turn right
        agents[ID].angle -= rotationAngle;
    } 
    else if (weightLeft > weightRight) {
        // Turn left
        agents[ID].angle += rotationAngle;
    }
}

void Move(int ID) {
    Agent agent = agents[ID];

    vec2 direction = vec2(cos(agent.angle), sin(agent.angle));
    vec2 newPos = vec2(agent.x, agent.y) + direction * stepSize;

    if (newPos.x < 0 || newPos.x >= width || newPos.y < 0 || newPos.y >= height) {
        agents[ID].angle = Random(uint(agent.y * width + agent.x + Hash(uint(ID + time * 100000)))) * PI * 2;
    } else {
        vec4 trailColor = vec4(trailColorR, trailColorG, trailColorB, 1.0);
        imageStore(trailMap, ivec2(agent.x, agent.y), trailColor);
        agents[ID].x = newPos.x;
        agents[ID].y = newPos.y;
    }
}

void Kill(int ID) {
    Agent agent = agents[ID];
    float rand = Random(uint(agent.y * width + agent.x + Hash(uint(ID + time * 100000))));
    if(rand > 1-killChance) {
        agents[ID].alive = false;
    }
}

void main()
{
    int ID = int(gl_GlobalInvocationID.x);
    if (ID >= agentCount) return;
    Kill(ID);
    if (ID >= agentCount || !agents[ID].alive) return;
    Turn(ID);
    Move(ID);
}