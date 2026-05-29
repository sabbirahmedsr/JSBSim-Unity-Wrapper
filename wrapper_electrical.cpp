// wrapper_electrical.cpp
#include "wrapper_electrical.h"

// Store previous state to avoid redundant JSBSim property updates
static ElectricalCommand lastCmd = { -1 }; 

void JSBSim_ProcessElectrical(ElectricalCommand* cmd) {
    if (!cmd) return;

    // Helper to update property only on change
    auto syncSwitch = [](const char* prop, int8_t current, int8_t& last) {
        if (current != last) {
            JSBSim_SafeSet(prop, (double)current); // Apply new value to simulation
            last = current;                        // Update history for next check
        }
    };

    // Power Management
    syncSwitch("systems/electrical/battery-switch", cmd->masterBatteryEnable, lastCmd.masterBatteryEnable);
    syncSwitch("systems/electrical/alternator-switch", cmd->masterAlternatorEnable, lastCmd.masterAlternatorEnable);
    syncSwitch("systems/electrical/avionics-switch", cmd->avionicsMasterEnable, lastCmd.avionicsMasterEnable);
    syncSwitch("systems/electrical/pitot-heat", cmd->pitotHeatEnable, lastCmd.pitotHeatEnable); // New Pitot Heat control

    // Lighting Controls
    syncSwitch("lighting/beacon-light", cmd->beaconLightEnable, lastCmd.beaconLightEnable);
    syncSwitch("lighting/landing-light", cmd->landingLightEnable, lastCmd.landingLightEnable);
    syncSwitch("lighting/taxi-light", cmd->taxiLightEnable, lastCmd.taxiLightEnable);
    syncSwitch("lighting/nav-light", cmd->navigationLightEnable, lastCmd.navigationLightEnable);
    syncSwitch("lighting/strobe-light", cmd->strobeLightEnable, lastCmd.strobeLightEnable);
}

void JSBSim_GetElectricalData(ElectricalData* data) {
    if (!data) return;

    // Read current state from simulation
    data->masterBatteryState = (JSBSim_SafeGet("systems/electrical/battery-switch") > 0.5); // Check battery status
    data->masterAlternatorState = (JSBSim_SafeGet("systems/electrical/alternator-switch") > 0.5); // Check alternator status
    data->avionicsMasterState = (JSBSim_SafeGet("systems/electrical/avionics-switch") > 0.5); // Check avionics status
    data->pitotHeatState = (JSBSim_SafeGet("systems/electrical/pitot-heat") > 0.5); // Check pitot heater status
    
    // Read current lighting status
    data->beaconLightState = (JSBSim_SafeGet("lighting/beacon-light") > 0.5); // Check beacon light
    data->landingLightState = (JSBSim_SafeGet("lighting/landing-light") > 0.5); // Check landing light
    data->taxiLightState = (JSBSim_SafeGet("lighting/taxi-light") > 0.5); // Check taxi light
    data->navigationLightState = (JSBSim_SafeGet("lighting/nav-light") > 0.5); // Check nav light
    data->strobeLightState = (JSBSim_SafeGet("lighting/strobe-light") > 0.5); // Check strobe light

    // Read monitoring sensors
    data->busVoltage = (float)JSBSim_SafeGet("systems/electrical/bus-volts"); // Get current bus voltage
    data->loadAmperage = (float)JSBSim_SafeGet("systems/electrical/total-load-amps"); // Get current electrical load
}

/*
// --- Electrical Controls & State ---
void JSBSim_SetMasterBattery(bool v)   { JSBSim_SafeSet("systems/electrical/battery-switch", v ? 1.0 : 0.0); }
void JSBSim_SetMasterAlternator(bool v){ JSBSim_SafeSet("systems/electrical/alternator-switch", v ? 1.0 : 0.0); }
void JSBSim_SetAvionicsMaster(bool v)  { JSBSim_SafeSet("systems/electrical/avionics-switch", v ? 1.0 : 0.0); }

bool JSBSim_GetMasterBattery()     { return JSBSim_SafeGet("systems/electrical/battery-switch") > 0.5; }
bool JSBSim_GetMasterAlternator()  { return JSBSim_SafeGet("systems/electrical/alternator-switch") > 0.5; }
bool JSBSim_GetAvionicsMaster()    { return JSBSim_SafeGet("systems/electrical/avionics-switch") > 0.5; }

// --- Lighting Controls & State ---
void JSBSim_SetBeaconLight(bool v)     { JSBSim_SafeSet("lighting/beacon-light", v ? 1.0 : 0.0); }
void JSBSim_SetLandingLight(bool v)    { JSBSim_SafeSet("lighting/landing-light", v ? 1.0 : 0.0); }
void JSBSim_SetTaxiLight(bool v)       { JSBSim_SafeSet("lighting/taxi-light", v ? 1.0 : 0.0); }
void JSBSim_SetNavigationLight(bool v) { JSBSim_SafeSet("lighting/nav-light", v ? 1.0 : 0.0); }
void JSBSim_SetStrobeLight(bool v)     { JSBSim_SafeSet("lighting/strobe-light", v ? 1.0 : 0.0); }

bool JSBSim_GetBeaconLight()           { return JSBSim_SafeGet("lighting/beacon-light") > 0.5; }
bool JSBSim_GetLandingLight()          { return JSBSim_SafeGet("lighting/landing-light") > 0.5; }
bool JSBSim_GetTaxiLight()             { return JSBSim_SafeGet("lighting/taxi-light") > 0.5; }
bool JSBSim_GetNavigationLight()       { return JSBSim_SafeGet("lighting/nav-light") > 0.5; }
bool JSBSim_GetStrobeLight()           { return JSBSim_SafeGet("lighting/strobe-light") > 0.5; }
*/