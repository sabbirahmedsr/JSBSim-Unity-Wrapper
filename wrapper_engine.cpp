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
#include "wrapper_engine.h"

void JSBSim_GetEngineSystemData(EngineData* ed) {
    if (!ed) return;

    // --- Inputs Status Mapping ---
    ed->throttlePos = (float)JSBSim_SafeGet("fcs/throttle-cmd-norm");
    ed->mixturePos  = (float)JSBSim_SafeGet("fcs/mixture-cmd-norm");
    
    // Status flags mapped to uint8_t (bool compatibility)
    ed->isStarterActive  = (JSBSim_SafeGet("controls/engines/engine[0]/starter") > 0.5);
    ed->isEngineRunning  = (JSBSim_SafeGet("propulsion/engine[0]/running") > 0.5);
    ed->isPrimerActive   = (JSBSim_SafeGet("propulsion/primer-state") > 0.5);
    ed->isFuelPumpActive = (JSBSim_SafeGet("propulsion/fuel-pump-state") > 0.5);

    // States (Keeping as int32_t)
    ed->magnetosState     = (int32_t)lastCmd.magnetos; 
    ed->fuelSelectorState = (int32_t)JSBSim_SafeGet("propulsion/fuel_selector");

    // --- Engine Performance & Health ---
    ed->primerPumpCycles = (int32_t)JSBSim_SafeGet("propulsion/primer-cycles");
    ed->rpm             = (float)JSBSim_SafeGet("propulsion/engine/engine-rpm");
    ed->powerHP         = (float)JSBSim_SafeGet("propulsion/engine[0]/power-hp");
    ed->oilTemperatureF = (float)JSBSim_SafeGet("propulsion/engine[0]/oil-temp-degf");
    ed->oilPressurePSI  = (float)JSBSim_SafeGet("propulsion/engine[0]/oil-pressure-psi");
    ed->egtF            = (float)JSBSim_SafeGet("propulsion/engine[0]/EGT-degf");

    // --- Fuel System ---
    ed->fuelFlowGPH    = (float)JSBSim_SafeGet("propulsion/engine[0]/fuel-flow-gph");
    ed->totalFuelLBS   = (float)JSBSim_SafeGet("propulsion/total-fuel-lbs");
    ed->leftFuelLBS    = (float)JSBSim_SafeGet("propulsion/tank[0]/contents-lbs");
    ed->rightFuelLBS   = (float)JSBSim_SafeGet("propulsion/tank[1]/contents-lbs");
}

/*
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
*/