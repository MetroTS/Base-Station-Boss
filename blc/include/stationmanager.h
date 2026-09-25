#pragma once
#include <vector>
#include <cstdint>
#include "Station.h"

class StationManager{
    public:
        std::vector<Station> Scan(int seconds, const std::vector<std::uint32_t>& knownIds);
    private:
        std::vector<Station> stations_;
};