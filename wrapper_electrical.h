#pragma once
#include "wrapper_global.h"
#include <cstdint>

// Command structure to send inputs from Unity to JSBSim
struct ElectricalCommand {
    // Power Switches
    int8_t masterBatteryEnable;    // Request to turn on the main battery
    int8_t masterAlternatorEnable; // Request to activate the alternator for charging
    int8_t avionicsMasterEnable;   // Request to power on the avionics suite
    int8_t pitotHeatEnable;        // Request to turn on the pitot tube heater

    // External/Environment Lighting
    int8_t beaconLightEnable;      // Toggle the red anti-collision light
    int8_t landingLightEnable;     // Toggle high-intensity landing lights
    int8_t taxiLightEnable;        // Toggle low-intensity lights for taxiing
    int8_t navigationLightEnable;  // Toggle wing and tail position lights
    int8_t strobeLightEnable;      // Toggle high-intensity flashing wingtip strobes
};

// Data structure to receive feedback from JSBSim to Unity
struct ElectricalData {
    // Status Feedback
    int8_t masterBatteryState;    // Current status of the battery (1 for On)
    int8_t masterAlternatorState; // Current status of the alternator (1 for Charging)
    int8_t avionicsMasterState;   // Current status of avionics power (1 for Active)
    int8_t pitotHeatState;        // Current status of the pitot heater (1 for Heating)

    // Lighting States
    int8_t beaconLightState;      // 1 if the beacon light is currently lit
    int8_t landingLightState;     // 1 if the landing light is currently lit
    int8_t taxiLightState;        // 1 if the taxi light is currently lit
    int8_t navigationLightState;  // 1 if navigation lights are currently lit
    int8_t strobeLightState;      // 1 if the strobe lights are currently lit

    // Monitoring
    float busVoltage;             // Current electrical system voltage (in Volts)
    float loadAmperage;           // Total electrical current draw (in Amps)
};

extern "C" {
    JSB_API void JSBSim_ProcessElectrical(ElectricalCommand* cmd);    
    JSB_API void JSBSim_GetElectricalData(ElectricalData* data);
}