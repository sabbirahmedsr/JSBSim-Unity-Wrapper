// wrapper_aircraft.cpp
#include "wrapper_aircraft.h"

// --- Aircraft State (WOW) ---
bool JSBSim_GetNoseWOW()  { return JSBSim_SafeGet("gear/unit[0]/WOW") > 0.5; }
bool JSBSim_GetLeftWOW()  { return JSBSim_SafeGet("gear/unit[1]/WOW") > 0.5; }
bool JSBSim_GetRightWOW() { return JSBSim_SafeGet("gear/unit[2]/WOW") > 0.5; }
bool JSBSim_GetWOW()      { return JSBSim_GetNoseWOW() || JSBSim_GetLeftWOW() || JSBSim_GetRightWOW(); }

// --- Flight/Ground Status ---
bool JSBSim_IsOnGround()  { return JSBSim_GetWOW(); }
bool JSBSim_IsFlying()    { return !JSBSim_GetWOW(); }
bool JSBSim_IsCrashed()   { return JSBSim_SafeGet("simulation/crash-state") > 0.5; }
bool JSBSim_IsOnRunway()  { return JSBSim_SafeGet("gear/unit[0]/on-runway") > 0.5; }

// --- Gear Compression ---
double JSBSim_GetNoseGearCompressionFeet()  { return JSBSim_SafeGet("gear/unit[0]/compression-ft"); }
double JSBSim_GetLeftGearCompressionFeet()  { return JSBSim_SafeGet("gear/unit[1]/compression-ft"); }
double JSBSim_GetRightGearCompressionFeet() { return JSBSim_SafeGet("gear/unit[2]/compression-ft"); }

// --- Systems ---
bool JSBSim_GetParkingBrakeState() { return JSBSim_SafeGet("fcs/center-brake-cmd-norm") > 0.5; }