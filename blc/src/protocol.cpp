#include "protocol.h"
#include <iostream>

std::vector<std::uint8_t> BuildPayload(bool isV2, PowerState state, std::uint32_t id){
    if (isV2) {
        switch (state) {
            case PowerState::On: return{0x01};
            case PowerState::Sleep: return{0x00};
            case PowerState::Standby: return{0x02};
        }
    }
    return{};
}
