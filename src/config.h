#pragma once
#include <string>
#include <unordered_map>

#define FULLSCREEN config::settings["FULLSCREEN"]
#define DISPLAY_WIDTH config::settings["DISPLAY_WIDTH"]
#define DISPLAY_HEIGHT config::settings["DISPLAY_HEIGHT"]

#define AGENT_COUNT config::settings["AGENT_COUNT"]
#define STEP_SIZE config::settings["STEP_SIZE"]
#define SENSOR_ANGLE float(config::settings["SENSOR_ANGLE"])
#define ROTATION_ANGLE float(config::settings["ROTATION_ANGLE"])
#define SENSOR_OFFSET config::settings["SENSOR_OFFSET"]
#define SENSOR_SIZE config::settings["SENSOR_SIZE"]

#define TEXTURE_WIDTH config::settings["TEXTURE_WIDTH"]
#define TEXTURE_HEIGHT config::settings["TEXTURE_HEIGHT"]
#define DECAY_SPEED config::settings["DECAY_SPEED"]
#define TRAIL_COLOR_R float(config::settings["TRAIL_COLOR_R"]) / 255
#define TRAIL_COLOR_G float(config::settings["TRAIL_COLOR_G"]) / 255
#define TRAIL_COLOR_B float(config::settings["TRAIL_COLOR_B"]) / 255

namespace config
{
	extern std::unordered_map<std::string, int> settings;

	void Load(const std::string filePath);
}
