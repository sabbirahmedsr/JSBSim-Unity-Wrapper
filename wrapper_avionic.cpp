// wrapper_avionic.cpp
#include "wrapper_avionic.h"

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