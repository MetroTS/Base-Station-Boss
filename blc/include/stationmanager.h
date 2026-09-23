#pragma once
#include <vector>
#include "Station.h"

class StationManager{
    public:
        std::vector<Station> Scan(int seconds);
    private:
        std::vector<Station> stations_;
};