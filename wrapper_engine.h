// wrapper_engine.h
#pragma once
#include "wrapper_global.h"
#include <cstdint>

struct EngineCommand {
    float throttle;           // Power level: 0.0 to 1.0
    float mixture;            // Fuel-air ratio: 0.0 to 1.0
    int8_t starterEnabled;    // 1 byte: 1=ON, 0=OFF
    int32_t magnetos;         // 4 bytes: 0=OFF, 1=R, 2=L, 3=BOTH
    int32_t fuelSelector;     // 4 bytes: Tank index
    int8_t fuelPumpEnabled;   // 1 byte: 1=ON, 0=OFF
    int8_t primer;            // 1 byte: 1=ON, 0=OFF
    int8_t engineRunning;     // 1 byte: 1=START, 0=STOP
};

// Status, performance, and fuel telemetry data from JSBSim
struct EngineData {
    // --- Actual positions in the simulation ---
    float throttlePos;        // Current throttle lever position (0.0 to 1.0)
    float mixturePos;         // Current mixture lever position (0.0 to 1.0)

    // --- Status flags (Using uint8_t for 1-byte boolean compatibility) ---
    uint8_t isStarterActive;   // True if starter is engaged
    int32_t magnetosState;     // Magneto switch (0=OFF, 1=R, 2=L, 3=BOTH)
    int32_t fuelSelectorState; // Currently selected fuel tank index
    uint8_t isEngineRunning;   // True if the engine is running
    uint8_t isPrimerActive;    // True if primer is active
    uint8_t isFuelPumpActive;  // True if fuel pump is active

    // --- Engine Performance & Health ---
    int32_t primerPumpCycles;  // Total count of primer pulses
    float rpm;                 // Engine speed in Revolutions Per Minute
    float powerHP;             // Power output in Horsepower
    float oilTemperatureF;     // Oil temperature in Fahrenheit
    float oilPressurePSI;      // Oil pressure in PSI
    float egtF;                // Exhaust Gas Temperature in Fahrenheit

    // --- Fuel System ---
    float fuelFlowGPH;         // Fuel consumption rate in Gallons Per Hour
    float totalFuelLBS;        // Total fuel weight in Pounds
    float leftFuelLBS;         // Fuel weight in left tank in Pounds
    float rightFuelLBS;        // Fuel weight in right tank in Pounds
};

extern "C" {
#define JSB_FUNC JSB_API
JSB_FUNC void JSBSim_ProcessEngineCommand(EngineCommand cmd);
JSB_FUNC void JSBSim_GetEngineSystemData(EngineData* ed);
#undef JSB_FUNC
}