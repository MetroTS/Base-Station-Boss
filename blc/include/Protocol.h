#pragma once
#include <cstdint>
#include <vector>

enum class PowerState {On, Sleep, Standby};
std::vector<std::uint8_t> BuildPayload(bool isV2, PowerState state, std::uint32_t id=0);