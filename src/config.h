#pragma once
#include <string>
#include <inih/INIReader.h>

#define FULLSCREEN     config::settings.GetBoolean("PROGRAM", "FULLSCREEN", false)
#define DISPLAY_WIDTH  config::settings.GetInteger("PROGRAM", "DISPLAY_WIDTH", 1280)
#define DISPLAY_HEIGHT config::settings.GetInteger("PROGRAM", "DISPLAY_HEIGHT", 720)
#define AGENT_COUNT    config::settings.GetInteger("AGENT", "AGENT_COUNT", 50000)
#define SENSOR_ANGLE   config::settings.GetInteger("AGENT", "SENSOR_ANGLE", 45.0) * (3.14159265359 / 180)
#define ROTATION_ANGLE config::settings.GetFloat("AGENT", "ROTATION_ANGLE", 45.0) * (3.14159265359 / 180)
#define SENSOR_OFFSET  config::settings.GetFloat("AGENT", "SENSOR_OFFSET", 10)
#define SENSOR_SIZE    config::settings.GetInteger("AGENT",	"SENSOR_SIZE", 1)
#define STEP_SIZE      config::settings.GetInteger("AGENT", "STEP_SIZE", 1)
#define SPAWN_MODE     config::settings.GetInteger("AGENT", "SPAWN_MODE", 1)
#define TEXTURE_WIDTH  config::settings.GetInteger("ENVIRONMENT", "TEXTURE_WIDTH", 1280)
#define TEXTURE_HEIGHT config::settings.GetInteger("ENVIRONMENT", "TEXTURE_HEIGHT", 720)
#define DECAY_SPEED_R  config::settings.GetInteger("ENVIRONMENT", "DECAY_SPEED_R", 5)
#define DECAY_SPEED_G  config::settings.GetInteger("ENVIRONMENT", "DECAY_SPEED_G", 5)
#define DECAY_SPEED_B  config::settings.GetInteger("ENVIRONMENT", "DECAY_SPEED_B", 5)
#define DIFFUSE_SIZE   config::settings.GetInteger("ENVIRONMENT", "DIFFUSE_SIZE", 1)
#define TRAIL_COLOR_R  config::settings.GetFloat("ENVIRONMENT", "TRAIL_COLOR_R", 255) / 255
#define TRAIL_COLOR_G  config::settings.GetFloat("ENVIRONMENT", "TRAIL_COLOR_G", 255) / 255
#define TRAIL_COLOR_B  config::settings.GetFloat("ENVIRONMENT", "TRAIL_COLOR_B", 255) / 255

namespace config
{
	extern INIReader settings;

	void Load(const std::string filePath);
};
