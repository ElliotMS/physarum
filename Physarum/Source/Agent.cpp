#include "Agent.h"
#include "Config.h"
#include <random>

namespace Agent
{
	GLuint buffer;

	void Init()
	{
		//float agentData[agentCount * 3];
		float* agentData = new float[AGENT_COUNT * 3];
		
		for (int i = 0; i < AGENT_COUNT * 3; i += 3)
		{
		    agentData[i+0] = (float(rand()) / float(RAND_MAX)) * TEXTURE_WIDTH;
		    agentData[i+1] = (float(rand()) / float(RAND_MAX)) * TEXTURE_HEIGHT;
		    agentData[i+2] = (float(rand()) / float(RAND_MAX)) * (2 * 3.14159265359);
		}
		
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer);
		glBufferData(GL_SHADER_STORAGE_BUFFER, AGENT_COUNT * 3 * sizeof(float), agentData, GL_DYNAMIC_COPY);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}
}