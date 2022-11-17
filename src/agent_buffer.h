#pragma once
#include <GL/glew.h>
#include <random>
#include "agent_buffer.h"
#include "config.h"
#include <iostream>

namespace agent_buffer
{
	GLuint buffer;

	enum SpawnModes { CIRCLE, RANDOM, MIDDLE };

	void Init()
	{
		float* agentData = new float[AGENT_COUNT * 3];
		float x, y, angle;
		float midPointX = TEXTURE_WIDTH / 2;
		float midPointY = TEXTURE_HEIGHT / 2;

		switch (SPAWN_MODE)
		{
		case CIRCLE:
			for (int i = 0; i < AGENT_COUNT * 3; i += 3)
			{
				float a = (float(rand()) / float(RAND_MAX)) * (2 * 3.14159265359);
				float r = (float(rand()) / float(RAND_MAX)) * midPointY;
				x = cos(a) * r + midPointX;
				y = sin(a) * r + midPointY;
				angle = atan2(midPointY - y, midPointX - x); // Angle facing middle
				agentData[i + 0] = x;
				agentData[i + 1] = y;
				agentData[i + 2] = angle;
			}
			break;
		case RANDOM:
			for (int i = 0; i < AGENT_COUNT * 3; i += 3)
			{
				x = (float(rand()) / float(RAND_MAX)) * TEXTURE_WIDTH;
				y = (float(rand()) / float(RAND_MAX)) * TEXTURE_HEIGHT;
				angle = (float(rand()) / float(RAND_MAX)) * (2 * 3.14159265359);

				agentData[i + 0] = x;
				agentData[i + 1] = y;
				agentData[i + 2] = angle;
			}
			break;
		case MIDDLE:
			x = midPointX;
			y = midPointY;
			for (int i = 0; i < AGENT_COUNT * 3; i += 3)
			{
				angle = (float(rand()) / float(RAND_MAX)) * (2 * 3.14159265359);
				agentData[i + 0] = x;
				agentData[i + 1] = y;
				agentData[i + 2] = angle;
			}
			break;
		}

		glGenBuffers(1, &buffer);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer);
		glBufferData(GL_SHADER_STORAGE_BUFFER, AGENT_COUNT * 3 * sizeof(float), agentData, GL_DYNAMIC_COPY);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, buffer);
	}
}
