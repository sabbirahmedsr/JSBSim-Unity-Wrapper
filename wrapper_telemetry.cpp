// wrapper_telemetry.cpp
#include "wrapper_telemetry.h"

// --- Air Data ---
double JSBSim_GetAirspeedKTS()        { return JSBSim_SafeGet("velocities/vc-kts"); }
double JSBSim_GetGroundSpeedKTS()     { return JSBSim_SafeGet("velocities/vg-kts"); }
double JSBSim_GetMach()               { return JSBSim_SafeGet("velocities/mach"); }
double JSBSim_GetVerticalSpeedFPS()   { return -JSBSim_SafeGet("velocities/v-down-fps"); }

// --- Position ---
double JSBSim_GetAltitudeFeet()       { return JSBSim_SafeGet("position/h-sl-ft"); }
double JSBSim_GetAltitudeMeters()     { return JSBSim_SafeGet("position/h-sl-meters"); }
double JSBSim_GetAGLFeet()            { return JSBSim_SafeGet("position/h-agl-ft"); }
double JSBSim_GetLatitudeDegrees()    { return JSBSim_SafeGet("position/lat-gc-deg"); }
double JSBSim_GetLongitudeDegrees()   { return JSBSim_SafeGet("position/long-gc-deg"); }

// --- Attitude ---
double JSBSim_GetPitchDegrees()       { return JSBSim_SafeGet("attitude/theta-deg"); }
double JSBSim_GetRollDegrees()        { return JSBSim_SafeGet("attitude/phi-deg"); }
double JSBSim_GetHeadingDegrees()     { return JSBSim_SafeGet("attitude/psi-deg"); }

// --- Aero ---
double JSBSim_GetAlphaDegrees()       { return JSBSim_SafeGet("aero/alpha-deg"); }
double JSBSim_GetBetaDegrees()        { return JSBSim_SafeGet("aero/beta-deg"); }