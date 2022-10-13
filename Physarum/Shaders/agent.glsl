#version 430 core

layout(local_size_x = 32, local_size_y = 1, local_size_z = 1) in;

layout(rgba32f, binding = 0) uniform image2D trailMap;

uniform int width;
uniform int height;
uniform int stepSize;
uniform float sensorAngle;
uniform float rotationAngle;
uniform int sensorOffset;
uniform int sensorSize;

float PI = 3.14159265359;

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

void moveAgent(int ID) {
    Agent agent = agents[ID];

    vec2 direction = vec2(cos(agent.angle), sin(agent.angle));
    vec2 newPos = vec2(agent.x, agent.y) + direction * stepSize;

    if (newPos.x < 0 || newPos.x > width || newPos.y < 0 || newPos.y > height)
    {
        newPos.x = agent.x - 0.01;
        newPos.y = agent.y - 0.01;
        agents[ID].angle = random(vec2(agent.x + ID, agent.y)) * (2 * PI); // Need better seed
    }

    vec4 trailColor = vec4(1.0, 1.0, 1.0, 1.0);
    imageStore(trailMap, ivec2(agent.x, agent.y), trailColor);

    agents[ID].x = newPos.x;
    agents[ID].y = newPos.y;
}

float sense(Agent agent, float sensorAngle) {
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

void main()
{
    int ID = int(gl_GlobalInvocationID.x);
    Agent agent = agents[ID];
    float weightFront = sense(agent, 0);
    float weightRight = sense(agent, -sensorAngle);
    float weightLeft = sense(agent, sensorAngle);

    if (weightFront > weightRight && weightFront > weightLeft && weightFront - weightRight > 0.01 && weightFront - weightLeft > 0.01){
        // Don't turn
        agents[ID].angle += 0;
    } 
    else if (weightFront < weightRight && weightFront < weightLeft && weightRight - weightFront > 0.01 && weightLeft - weightFront > 0.01) {
        //Turn randomly left or right
        if (random(vec2(agent.x + ID, agent.y)) > 0.5) {
            agents[ID].angle -= rotationAngle;
        } else {
            agents[ID].angle += rotationAngle;
        }
    } 
    else if (weightRight > weightLeft && weightRight - weightLeft > 0.01) {
        // Turn right
        agents[ID].angle -= rotationAngle;
    } 
    else if (weightLeft > weightRight && weightLeft - weightRight > 0.01) {
        // Turn left
        agents[ID].angle += rotationAngle;
    }

    moveAgent(ID);
}
