#pragma once
#include <vector>
#include <cstdint>
#include "Station.h"
#include "Protocol.h"

class StationManager{
    public:
        std::vector<Station> Scan(int seconds, const std::vector<std::uint32_t>& knownIds);
        int SetAll(PowerState state);
    private:
        std::vector<Station> stations_;
};