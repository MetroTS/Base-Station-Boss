#include "Protocol.h"
#include "StationManager.h"
#include "V1ID.h"
#include <iostream>
using namespace std;

int main()
{
    // v2 On should give the byte 01
    if (BuildPayload(true, PowerState::On) == vector<uint8_t>{0x01})
        cout << "v2 On: OK\n";
    else
        cout << "v2 On: FAIL\n";

    // v2 Sleep should give the byte 00
    if (BuildPayload(true, PowerState::Sleep) == vector<uint8_t>{0x00})
        cout << "v2 Sleep: OK\n";
    else
        cout << "v2 Sleep: FAIL\n";

    // v2 Standby should give the byte 02
    if (BuildPayload(true, PowerState::Standby) == vector<uint8_t>{0x02})
        cout << "v2 Standby: OK\n";
    else
        cout << "v2 Standby: FAIL\n";

    // v1 On should give the bytes 0x12, 0x00 ... ID
        vector<uint8_t> v1payloadOn = {
        0x12, 0x00, 0x00, 0x00,
        0x8c, 0x6D, 0xA3, 0x35,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };

    if (BuildPayload(false, PowerState::On, 0x35A36D8C) == v1payloadOn)
        cout << "v1 On: OK\n";
    else
        cout << "v1 On: FAIL\n";

    // v1 Standby should give the bytes 0x12, 0x02, 0x00, 0x01 ... ID
    vector<uint8_t> v1payloadStandby = {
        0x12, 0x02, 0x00, 0x01,
        0x8c, 0x6D, 0xA3, 0x35,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };

    if (BuildPayload(false, PowerState::Standby, 0x35A36D8C) == v1payloadStandby)
        cout << "v1 Standby: OK\n";
    else
        cout << "v1 Standby: FAIL\n";

    StationManager manager;
    auto found = manager.Scan(5);
    cout << "Found " << found.size() << " base stations:\n";
    for (auto& s : found)
    cout << "  " << s.Name << "  (" << s.Address << ")\n";

    vector<uint32_t> serial_IDs = {0x2EAC4BFA, 0x35A36D8C};

    if (match_base_serial_number(serial_IDs, "HTC BS 4D6D8C") == 0x35A36D8C)
        cout << "match 4D6D8C: OK\n";
    else
        cout << "match 4D6D8C: FAIL\n";

    if (match_base_serial_number(serial_IDs, "HTC BS CB4BFA") == 0x2EAC4BFA)
        cout << "match CB4BFA: OK\n";
    else
        cout << "match CB4BFA: FAIL\n ";

    if (match_base_serial_number(serial_IDs, "HTC BS 123456") == 0x35A36D8C)
        cout << "match 123456: OK - this shouldnt have matched\n";
    else
        cout << "match 123456: FAIL - this is to be expected\n";

    if (match_base_serial_number(serial_IDs, "HTC BS AB") == 0x35A36D8C)
        cout << "match AB: OK - this shouldnt have matched\n";
    else
        cout << "match AB: FAIL - this is to be expected\n";

    vector<uint32_t> expectedIds = {0x2EAC4BFA, 0x35A36D8C};

    if (load_base_serial_number("C:/Program Files (x86)/Steam/config/lighthouse/lighthousedb.json") == expectedIds)
    cout << "load real file: OK\n";
    else
    cout << "load real file: FAIL\n";

    if (load_base_serial_number("C:/nope.json").empty())
    cout << "load missing file: OK\n";
    else
    cout << "load missing file: FAIL\n";

    return 0;
}