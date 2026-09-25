#include <iostream>
#include <simpleble/SimpleBLE.h>
#include <vector>
#include "Station.h"
#include "StationManager.h"

std::vector<Station> StationManager::Scan(int seconds){
    stations_.clear();
    auto adapters = SimpleBLE::Adapter::get_adapters();
    if (adapters.empty()) {
        std::cout << "No bluetooth adapter found!\n";
        return {};
    }
    bool bluetooth_enabled = SimpleBLE::Adapter::bluetooth_enabled();
    if (bluetooth_enabled == false) {
        std::cout << "Bluetooth isnt enabled!\n";
        return {};
    }

    auto adapter = adapters[0];
    adapter.scan_for(seconds * 1000);

    for (auto& peripheral : adapter.scan_get_results()) {
        std::string name = peripheral.identifier();
        bool isV2 = name.rfind("LHB-", 0) == 0;
        bool isV1 = name.rfind("HTC BS", 0) == 0;
        if (isV1 == false && isV2 == false) {
            continue;
        }

        Station s;
        s.Name = name;
        s.Address = peripheral.address();
        s.IsV2 = isV2;

        stations_.push_back(s);
    }
    return stations_;
}


    }
}