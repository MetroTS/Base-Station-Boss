#include "Protocol.h"
#include <iostream>

int main()
{
    // v2 On should give the byte 01
    if (BuildPayload(true, PowerState::On) == std::vector<std::uint8_t>{0x01})
        std::cout << "v2 On: OK\n";
    else
        std::cout << "v2 On: FAIL\n";

    // v2 Sleep should give the byte 00
    if (BuildPayload(true, PowerState::Sleep) == std::vector<std::uint8_t>{0x00})
        std::cout << "v2 Sleep: OK\n";
    else
        std::cout << "v2 Sleep: FAIL\n";

    // v2 Standby should give the byte 02
    if (BuildPayload(true, PowerState::Standby) == std::vector<std::uint8_t>{0x02})
        std::cout << "v2 Standby: OK\n";
    else
        std::cout << "v2 Standby: FAIL\n";

    // v1 On should give the bytes 0x12, 0x00 ... ID
        std::vector<std::uint8_t> v1payloadOn = {
        0x12, 0x00, 0x00, 0x00,
        0x8c, 0x6D, 0xA3, 0x35,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };

    if (BuildPayload(false, PowerState::On, 0x35A36D8C) == v1payloadOn)
        std::cout << "v1 On: OK\n";
    else
        std::cout << "v1 On: FAIL\n";

    // v1 Standby should give the bytes 0x12, 0x02, 0x00, 0x01 ... ID
    std::vector<std::uint8_t> v1payloadStandby = {
        0x12, 0x02, 0x00, 0x01,
        0x8c, 0x6D, 0xA3, 0x35,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };

    if (BuildPayload(false, PowerState::Standby, 0x35A36D8C) == v1payloadStandby)
        std::cout << "v1 On: OK\n";
    else
        std::cout << "v1 On: FAIL\n";
    return 0;

}