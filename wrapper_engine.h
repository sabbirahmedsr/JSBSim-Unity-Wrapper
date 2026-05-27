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

// Receives all engine status, performance, and fuel data back from JSBSim.
struct EngineData {
    // Inputs (Actual positions in simulation)
    float throttlePos;          // Current throttle lever position.
    float mixturePos;           // Current mixture lever position.
    int32_t starterState;       // 1 if starter is active.
    int32_t magnetosState;      // Current ignition switch position.
    int32_t fuelSelectorState;  // Currently selected fuel tank.
    int32_t engineRunning;      // 1 if the engine is running.
    int32_t primerState;        // 1 if primer is active.
    int32_t fuelPumpState;      // 1 if fuel pump is active.
    
    // Performance Data
    int32_t primerPumpCycles;   // Count of primer pushes.
    float rpm;                  // Current engine speed.
    float powerHP;              // Power output in Horsepower.
    float oilTemperatureF;      // Oil temperature in Fahrenheit.
    float egtF;                 // Exhaust Gas Temperature in Fahrenheit.
    
    // Fuel System
    float totalFuelLBS;         // Total fuel weight in pounds.
    float leftFuelLBS;          // Fuel in left tank in pounds.
    float rightFuelLBS;         // Fuel in right tank in pounds.
};

extern "C" {
#define JSB_FUNC JSB_API
/*
JSB_FUNC void JSBSim_SetThrottle(double value);
JSB_FUNC void JSBSim_SetMixture(double value);
JSB_FUNC void JSBSim_SetStarter(bool value);
JSB_FUNC void JSBSim_SetMagnetos(int value);
JSB_FUNC void JSBSim_SetFuelSelector(int value);
JSB_FUNC void JSBSim_SetEngineRunning(bool value);*/
JSB_FUNC void JSBSim_ProcessEngineCommand(EngineCommand cmd);
JSB_FUNC void JSBSim_GetEngineSystemData(EngineData* ed);
#undef JSB_FUNC
}