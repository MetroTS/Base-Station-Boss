#include "Protocol.h"

std::vector<std::uint8_t> BuildPayload(bool isV2, PowerState state, std::uint32_t id){
    if (isV2) {
        switch (state) {
            case PowerState::On: return{0x01};
            case PowerState::Sleep: return{0x00};
            case PowerState::Standby: return{0x02};}
    } else {
        std::vector<std::uint8_t> Payload(20, 0x00);
        if (state == PowerState::On){
            Payload[0] = 0x12; // command on
            Payload[1] = 0x00; 
            Payload[2] = 0x00;
            Payload[3] = 0x00;
        } else {
            Payload[0] = 0x12; // command off
            Payload[1] = 0x02; 
            Payload[2] = 0x00;
            Payload[3] = 0x01;
        }
        Payload[4] = id % 256;
        Payload[5] = (id/256) % 256;
        Payload[6] = (id/65536) % 256;
        Payload[7] = (id/16777216) % 256;
        return{Payload};
    }
    return{};
}


