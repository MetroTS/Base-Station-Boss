#pragma once
#include <string>
#include <cstdint>

struct Station
{
    std::string Name; // Name of the base station
    std::string Address; // Bluetooth adress
    bool IsV2 = false; //If model is 2.0
    std::uint32_t ID = 0; //ID for 1.0
};
