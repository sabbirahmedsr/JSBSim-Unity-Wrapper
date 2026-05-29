#pragma once
#include "wrapper_global.h"
#include <cstdint>

struct MiscellaneousData {
    // --- ENVIRONMENT DATA ---
    float outsideAirTempF;      // Ambient air temperature in Fahrenheit
    float windSpeedKts;         // Wind speed in knots
    float windDirDeg;           // Wind direction in degrees

    // --- INSTRUMENTS & WARNINGS ---
    uint8_t stallWarning;       // True if stall is imminent
    float suctionInHg;          // Instrument vacuum pressure in Inches of Mercury
    float altimeterSetting;     // Barometric pressure setting in Inches of Mercury
};

extern "C" {
#define JSB_FUNC JSB_API
    JSB_FUNC void JSBSim_GetMiscellaneousData(MiscellaneousData* md);
#undef JSB_FUNC
}