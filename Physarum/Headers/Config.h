#pragma once
#include <string>
#include <unordered_map>

#define FULLSCREEN Config::settings["FULLSCREEN"]
#define DISPLAY_WIDTH Config::settings["DISPLAY_WIDTH"]
#define DISPLAY_HEIGHT Config::settings["DISPLAY_HEIGHT"]

#define AGENT_COUNT Config::settings["AGENT_COUNT"]
#define STEP_SIZE Config::settings["STEP_SIZE"]
#define SENSOR_ANGLE Config::settings["SENSOR_ANGLE"]
#define ROTATION_ANGLE Config::settings["ROTATION_ANGLE"]
#define SENSOR_OFFSET Config::settings["SENSOR_OFFSET"]
#define SENSOR_SIZE Config::settings["SENSOR_SIZE"]

#define TEXTURE_WIDTH Config::settings["TEXTURE_WIDTH"]
#define TEXTURE_HEIGHT Config::settings["TEXTURE_HEIGHT"]
#define DECAY_SPEED Config::settings["DECAY_SPEED"]

namespace Config
{
	extern std::unordered_map<std::string, int> settings;

	void Load(const std::string filePath);
}
