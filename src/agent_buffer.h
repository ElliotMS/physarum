#pragma once
#include <GL/glew.h>
#include <random>
#include <iostream>
#include "config.h"

namespace agent_buffer
{
	GLuint buffer;

	struct Agent {
		float x;
		float y;
		float angle;
		bool alive = true;
	};

	enum SpawnModes { CIRCLE, RANDOM };

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> rand(0.0, 1.0);

	void Init()
	{
		Agent* agentData = new Agent[AGENT_COUNT];
		float midPointX = TEXTURE_WIDTH / 2;
		float midPointY = TEXTURE_HEIGHT / 2;
		Agent agent;

		switch (SPAWN_MODE)
		{
		case CIRCLE:
			for (int i = 0; i < AGENT_COUNT; i++)
			{
				float a = rand(gen) * (2 * std::_Pi);
				float r = rand(gen) * midPointY;
				agent.x = cos(a) * r + midPointX;
				agent.y = sin(a) * r + midPointY;
				agent.angle = atan2(midPointY - agent.y, midPointX - agent.x); // Angle facing middle
				agentData[i] = agent;
			}
			break;
		case RANDOM:
			for (int i = 0; i < AGENT_COUNT; i++)
			{
				agent.x = rand(gen) * TEXTURE_WIDTH;
				agent.y = rand(gen) * TEXTURE_HEIGHT;
				agent.angle = rand(gen) * (2 * std::_Pi);
				agentData[i] = agent;
			}
			break;
		}

		glGenBuffers(1, &buffer);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer);
		glBufferData(GL_SHADER_STORAGE_BUFFER, AGENT_COUNT * sizeof(Agent), agentData, GL_DYNAMIC_COPY);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, buffer);
	}
}
