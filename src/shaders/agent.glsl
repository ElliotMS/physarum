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

const float PI = 3.14159265359;

struct Agent {
    float x;
    float y;
    float angle;
    bool status;
};

layout(std430, binding = 1) buffer Agents {
    Agent agents[];
};

float random(vec2 co) {
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
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
        if (random(vec2(agent.x + ID, agent.y)) > 0) {
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

    if (newPos.x < 0 || newPos.x >= width || newPos.y < 0 || newPos.y >= height) // Out of bounds check
    {
        newPos.x = agent.x - 0.01;
        newPos.y = agent.y - 0.01;
        agents[ID].angle = (random(vec2(agent.x + ID, agent.y))+1) * PI;
    }

    vec4 trailColor = vec4(trailColorR, trailColorG, trailColorB, 0.0);
    imageStore(trailMap, ivec2(agent.x, agent.y), trailColor);

    agents[ID].x = newPos.x;
    agents[ID].y = newPos.y;
}

void Kill(int ID) {
    Agent agent = agents[ID];
    float rand = random(vec2(agent.x + ID, agent.y));
    if(rand > 1-killChance*2) {
        agents[ID].status = false;
    }
}

void main()
{
    int ID = int(gl_GlobalInvocationID.x);
    if (ID >= agentCount || !agents[ID].status) return;
    Kill(ID);
    Turn(ID);
    Move(ID);
}