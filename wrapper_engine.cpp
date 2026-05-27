// wrapper_engine.cpp
#include "wrapper_engine.h"

static EngineCommand lastCmd = { -1.0f, -1.0f, -1, -1, -1, -1, -1, -1 };
void JSBSim_ProcessEngineCommand(EngineCommand cmd) {
    // 1. Continuous Update (For Throttle & Mixture)
    JSBSim_SafeSet("fcs/throttle-cmd-norm", JSB_Clamp(cmd.throttle, 0.0f, 1.0f));
    JSBSim_SafeSet("fcs/mixture-cmd-norm", JSB_Clamp(cmd.mixture, 0.0f, 1.0f));

    
    // 3. Starter: Update if state differs
    if (cmd.starterEnabled != lastCmd.starterEnabled) {
        JSBSim_SafeSet("propulsion/starter_cmd", cmd.starterEnabled ? 1.0 : 0.0);
        lastCmd.starterEnabled = cmd.starterEnabled;
    }
    // 4. Magnetos: Update if state differs
    if (cmd.magnetos != lastCmd.magnetos) {
        JSBSim_SafeSet("propulsion/magneto_cmd", (double)cmd.magnetos);
        lastCmd.magnetos = cmd.magnetos;       
    }
    // 5. Fuel Selector: Update if state differs
    if (cmd.fuelSelector != lastCmd.fuelSelector) {
        JSBSim_SafeSet("propulsion/fuel_selector", (double)cmd.fuelSelector);
        lastCmd.fuelSelector = cmd.fuelSelector;
    }
    // 6. Fuel Pump: Update if state differs
    if (cmd.fuelPumpEnabled != lastCmd.fuelPumpEnabled) {
        JSBSim_SafeSet("propulsion/fuel-pump-cmd", cmd.fuelPumpEnabled ? 1.0 : 0.0);
        lastCmd.fuelPumpEnabled = cmd.fuelPumpEnabled;
    }
    // 7. Primer: Update if state differs
    if (cmd.primer != lastCmd.primer) {
        JSBSim_SafeSet("propulsion/primer-cmd", cmd.primer ? 1.0 : 0.0);
        lastCmd.primer = cmd.primer;
    }
    // 8. Engine Running: Update if state differs
    if (cmd.engineRunning != lastCmd.engineRunning) {
        JSBSim_SafeSet("propulsion/set-running", cmd.engineRunning ? 1.0 : 0.0);
        lastCmd.engineRunning = cmd.engineRunning;
    }
}


// Retrieves all engine performance, status, and fuel data in one call.
void JSBSim_GetEngineSystemData(EngineData* ed) {
    if (!ed) return;

    // Inputs Status Mapping (Feedback from Simulation)
    ed->throttlePos = (float)JSBSim_SafeGet("fcs/throttle-cmd-norm");
    ed->mixturePos = (float)JSBSim_SafeGet("fcs/mixture-cmd-norm");
    ed->starterState = (JSBSim_SafeGet("controls/engines/engine[0]/starter") > 0.5) ? 1 : 0;
    //ed->magnetosState = (int32_t)JSBSim_SafeGet("propulsion/magneto_cmd");
    ed->magnetosState = lastCmd.magnetos;
    ed->fuelSelectorState = (int32_t)JSBSim_SafeGet("propulsion/fuel_selector");
    ed->engineRunning = (JSBSim_SafeGet("propulsion/engine[0]/running") > 0.5) ? 1 : 0;
    ed->primerState = (int32_t)JSBSim_SafeGet("propulsion/primer-state");
    ed->fuelPumpState = (int32_t)JSBSim_SafeGet("propulsion/fuel-pump-state");

    // Engine Performance Mapping
    ed->primerPumpCycles = (int32_t)JSBSim_SafeGet("propulsion/primer-cycles");
    ed->rpm = (float)JSBSim_SafeGet("propulsion/engine/engine-rpm");
    ed->powerHP = (float)JSBSim_SafeGet("propulsion/engine[0]/power-hp");
    ed->oilTemperatureF = (float)JSBSim_SafeGet("propulsion/engine[0]/oil-temp-degf");
    ed->egtF = (float)JSBSim_SafeGet("propulsion/engine[0]/EGT-degf");

    // Fuel System Mapping
    ed->totalFuelLBS = (float)JSBSim_SafeGet("propulsion/total-fuel-lbs");
    ed->leftFuelLBS = (float)JSBSim_SafeGet("propulsion/tank[0]/contents-lbs");
    ed->rightFuelLBS = (float)JSBSim_SafeGet("propulsion/tank[1]/contents-lbs");
}


/*
// --- Engine Controls ---
void JSBSim_SetThrottle(double v)      { JSBSim_SafeSet("fcs/throttle-cmd-norm", JSB_Clamp(v, 0.0, 1.0)); }
void JSBSim_SetMixture(double v)       { JSBSim_SafeSet("fcs/mixture-cmd-norm", JSB_Clamp(v, 0.0, 1.0)); }
void JSBSim_SetStarter(bool v)         { JSBSim_SafeSet("propulsion/starter_cmd", v ? 1.0 : 0.0); }
void JSBSim_SetMagnetos(int v)         { JSBSim_SafeSet("propulsion/magneto_cmd", (double)v); }
void JSBSim_SetFuelSelector(int v)     { JSBSim_SafeSet("propulsion/fuel_selector", (double)v); }
void JSBSim_SetEngineRunning(bool v)   { JSBSim_SafeSet("propulsion/set-running", v ? 1.0 : 0.0); }

// --- Engine Data ---
bool   JSBSim_GetEngineRunning()       { return JSBSim_SafeGet("propulsion/engine[0]/running") > 0.5; }
double JSBSim_GetRPM()                 { return JSBSim_SafeGet("propulsion/engine[0]/rpm"); }
double JSBSim_GetEnginePowerHP()       { return JSBSim_SafeGet("propulsion/engine[0]/power-hp"); }
double JSBSim_GetFuelTotalLBS()        { return JSBSim_SafeGet("propulsion/total-fuel-lbs"); }
double JSBSim_GetFuelLeftLBS()         { return JSBSim_SafeGet("propulsion/tank[0]/contents-lbs"); }
double JSBSim_GetFuelRightLBS()        { return JSBSim_SafeGet("propulsion/tank[1]/contents-lbs"); }
double JSBSim_GetOilTemperatureF()     { return JSBSim_SafeGet("propulsion/engine[0]/oil-temp-degf"); }
double JSBSim_GetEGTF()                { return JSBSim_SafeGet("propulsion/engine[0]/EGT-degf"); }
int    JSBSim_GetMagnetosState()       { return (int)JSBSim_SafeGet("controls/engines/engine[0]/magnetos"); }
double JSBSim_GetThrottlePosition()    { return JSBSim_SafeGet("fcs/throttle-cmd-norm"); }
double JSBSim_GetMixturePosition()     { return JSBSim_SafeGet("fcs/mixture-cmd-norm"); }
bool   JSBSim_GetStarterState()        { return JSBSim_SafeGet("controls/engines/engine[0]/starter") > 0.5; }
bool   JSBSim_GetOilPumpState()        { return JSBSim_SafeGet("propulsion/engine[0]/oil-pump-state") > 0.5; }
*/