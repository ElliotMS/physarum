#include "config.h"
#include <iostream>
#include <fstream>

namespace config {

    INIReader settings;

	void Load(const std::string filePath)
	{   
        settings = INIReader((filePath).c_str());
        int err = settings.ParseError();
        if (err != 0) {
            if (err == -1)
                std::cerr << "Unable to open configuration file: " << filePath << std::endl;
            else
                std::cerr << "Unable to parse configuration file: " << filePath << ". Error on line " << err << "." << std::endl;
                std::cerr << "Using default configuration values for obstructed/missing parameters." << std::endl;
        }
	}
}