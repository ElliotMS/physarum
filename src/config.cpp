#include "config.h"
#include <iostream>
#include <fstream>

namespace config {

    INIReader settings;

	void Load(const std::string filePath)
	{   
        settings = INIReader((filePath).c_str());

        if (settings.ParseError() != 0) {
            std::cerr << "Unable to load configuration file: " << filePath << std::endl;
            return;
        }
	}
}