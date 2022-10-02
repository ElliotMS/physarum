#include "Config.h"
#include <iostream>
#include <fstream>

namespace Config {

    std::unordered_map<std::string, int> settings;

	void Load(const std::string filePath)
	{
        std::ifstream file;
        file.open((filePath).c_str());

        if (file.is_open())
        {
            std::string line;

            while (file.good())
            {
                getline(file, line);
                line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
                if (line[0] == '[' || line[0] == '#' || line.empty())
                    continue;
                auto delimiterPos = line.find("=");
                auto param = line.substr(0, delimiterPos);
                auto value = line.substr(delimiterPos + 1);
                settings.insert({ param, stoi(value) });
            }
        }
        else
        {
            std::cerr << "Unable to load shader: " << filePath << std::endl;
        }
	}
}