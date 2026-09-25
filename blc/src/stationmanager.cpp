#include <iostream>
#include <simpleble/SimpleBLE.h>
#include <vector>
#include <thread>
#include <chrono>
#include "Station.h"
#include "StationManager.h"
#include "v1id.h"
#include "Protocol.h"
static std::vector<SimpleBLE::Peripheral> peripherals_;

std::vector<Station> StationManager::Scan(int seconds, const std::vector<uint32_t>& knownIds){
    stations_.clear();
    peripherals_.clear();
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
        if (isV1)
            s.ID = match_base_serial_number(knownIds, name);

        stations_.push_back(s);
        peripherals_.push_back(peripheral);
    }
    return stations_;
}

int StationManager::SetAll(PowerState state)
{
    if (peripherals_.size() != stations_.size()){
        std::cout << "SetAll: list mismatch: " << stations_.size()
                << " stations vs " << peripherals_.size() << " peripherals\n";
        return 0;
    }

    int reached = 0;
    for (size_t i = 0; i < stations_.size(); i++)
    {
        Station& s = stations_[i];
        SimpleBLE::Peripheral& p = peripherals_[i];
        if (!s.IsV2 && s.ID == 0) {
            std::cout << "SetAll: skipping " << s.Name << " (no ID)\n";
            continue;
        }


        std::vector<std::uint8_t> bytes = BuildPayload(s.IsV2, state, s.ID);
        std::string service = s.IsV2 ? "00001523-1212-efde-1523-785feabcd124"
                                     : "0000cb00-0000-1000-8000-00805f9b34fb";
        std::string charac  = s.IsV2 ? "00001525-1212-efde-1523-785feabcd124"
                                     : "0000cb01-0000-1000-8000-00805f9b34fb";
        for (int attempt = 1; attempt <= 3; attempt++)
            try
            {
                if (p.is_connected())
                    p.disconnect();
                p.connect();
                p.write_request(service, charac, SimpleBLE::ByteArray(bytes));
                p.disconnect();
                for (int w = 0; w < 30 && p.is_connected(); w++)
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                reached++;
                break;
            }
            catch (const std::exception& e)
            {
                std::cout << "send to " << s.Name << " failed (attempt "
                        << attempt << "/3): " << e.what() << "\n";
                try { p.disconnect(); } catch (...) {}
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
    }

    return reached;
}