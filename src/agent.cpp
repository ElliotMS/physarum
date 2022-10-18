#include "Agent.h"
#include "config.h"
#include <random>

namespace agent
{
	GLuint buffer;

	void Init()
	{
		float* agentData = new float[AGENT_COUNT * 3];
		
		for (int i = 0; i < AGENT_COUNT * 3; i += 3)
		{
			float midPointX = TEXTURE_WIDTH / 2;
			float midPointY = TEXTURE_HEIGHT / 2;

		    //agentData[i+0] = (float(rand()) / float(RAND_MAX)) * TEXTURE_WIDTH;
		    //agentData[i+1] = (float(rand()) / float(RAND_MAX)) * TEXTURE_HEIGHT
			
			//agentData[i+0] = midPointX;
			//agentData[i+1] = midPointY;
			
			float randomAngle = (float(rand()) / float(RAND_MAX)) * (2 * 3.14159265359);
			float randomDistance = (float(rand()) / float(RAND_MAX)) * midPointY;
			float x = cos(randomAngle) * randomDistance + midPointX;
			float y = sin(randomAngle) * randomDistance + midPointY;
			agentData[i+0] = x;
			agentData[i+1] = y;
		    
			//agentData[i+2] = (float(rand()) / float(RAND_MAX)) * (2 * 3.14159265359);
			agentData[i+2] = atan2(midPointY - y, midPointX - x); // Angle facing middle
		}
		
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer);
		glBufferData(GL_SHADER_STORAGE_BUFFER, AGENT_COUNT * 3 * sizeof(float), agentData, GL_DYNAMIC_COPY);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, buffer);
	}
}