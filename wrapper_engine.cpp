// wrapper_engine.cpp
#include "wrapper_engine.h"

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