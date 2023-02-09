#pragma once
#include <chrono>

namespace time_ms
{
    unsigned int Get()
    {
        using namespace std::chrono;
        milliseconds ms = duration_cast<milliseconds>(
            system_clock::now().time_since_epoch()
            );
        return ms.count();
    }
}