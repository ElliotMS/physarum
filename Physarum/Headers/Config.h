#pragma once
#include <string>
#include <unordered_map>

#define DISPLAY_WIDTH Config::settings["DISPLAY_WIDTH"]
#define DISPLAY_HEIGHT Config::settings["DISPLAY_HEIGHT"]
#define TEXTURE_WIDTH Config::settings["TEXTURE_WIDTH"]
#define TEXTURE_HEIGHT Config::settings["TEXTURE_HEIGHT"]
#define AGENT_COUNT Config::settings["AGENT_COUNT"]

namespace Config
{
	extern std::unordered_map<std::string, int> settings;

	void Load(const std::string filePath);
}
