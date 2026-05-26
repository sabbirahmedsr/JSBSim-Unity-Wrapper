#include "wrapper_transform.h"
#include "wrapper_telemetry.h"

static constexpr double F2M = 0.3048;

// --- GEO Position ---
double JSBSim_GetGEOLatitudeMeters()  { return JSBSim_SafeGet("position/distance-from-start-lat-mt"); }
double JSBSim_GetGEOLongitudeMeters() { return JSBSim_SafeGet("position/distance-from-start-lon-mt"); }
double JSBSim_GetGEODistanceMeters()  { return JSBSim_SafeGet("position/distance-from-start-mag-mt"); }
JSBSimVector3 JSBSim_GetRawGEOPosition() { return { JSBSim_GetGEOLatitudeMeters(), JSBSim_GetGEOLongitudeMeters(), JSBSim_GetGEODistanceMeters() };}
JSBSimVector3 JSBSim_GetUnityGEOPosition() { return { JSBSim_GetGEOLongitudeMeters(), 0.0, JSBSim_GetGEOLatitudeMeters() }; }

// --- NEU POSITION ---
double JSBSim_GetNEUNorthFeet() { return JSBSim_SafeGet("position/from-start-neu-n-ft"); }
double JSBSim_GetNEUEastFeet()  { return JSBSim_SafeGet("position/from-start-neu-e-ft"); }
double JSBSim_GetNEUUpFeet()    { return JSBSim_SafeGet("position/from-start-neu-u-ft"); }
JSBSimVector3 JSBSim_GetRawNEUPosition() { return { JSBSim_GetNEUNorthFeet() * F2M, JSBSim_GetNEUEastFeet() * F2M, JSBSim_GetNEUUpFeet() * F2M }; }
JSBSimVector3 JSBSim_GetUnityNEUPosition() { return { JSBSim_GetNEUEastFeet() * F2M, JSBSim_GetNEUUpFeet() * F2M, JSBSim_GetNEUNorthFeet() * F2M }; }

// --- Velocity ---
double JSBSim_GetRawVelocityNorthFPS()    { return JSBSim_SafeGet("velocities/v-north-fps"); }
double JSBSim_GetRawVelocityEastFPS()     { return JSBSim_SafeGet("velocities/v-east-fps"); }
double JSBSim_GetRawVelocityDownFPS()     { return JSBSim_SafeGet("velocities/v-down-fps"); }
JSBSimVector3 JSBSim_GetRawVelocity()     { return { JSBSim_GetRawVelocityNorthFPS(), JSBSim_GetRawVelocityEastFPS(), JSBSim_GetRawVelocityDownFPS() }; }

double JSBSim_GetUnityVelocityX()         { return JSBSim_GetRawVelocityEastFPS(); }
double JSBSim_GetUnityVelocityY()         { return -JSBSim_GetRawVelocityDownFPS(); }
double JSBSim_GetUnityVelocityZ()         { return JSBSim_GetRawVelocityNorthFPS(); }
JSBSimVector3 JSBSim_GetUnityVelocity()   { return { JSBSim_GetUnityVelocityX(), JSBSim_GetUnityVelocityY(), JSBSim_GetUnityVelocityZ() }; }

// --- Euler Angles ---
JSBSimVector3 JSBSim_GetRawEulerAngles()  { return { JSBSim_GetPitchDegrees(), JSBSim_GetHeadingDegrees(), JSBSim_GetRollDegrees() }; }
JSBSimVector3 JSBSim_GetUnityEulerAngles(){ return { -JSBSim_GetPitchDegrees(), JSBSim_GetHeadingDegrees(), -JSBSim_GetRollDegrees() }; }

