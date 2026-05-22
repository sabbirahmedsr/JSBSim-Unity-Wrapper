#include "wrapper_transform.h"
#include "wrapper_telemetry.h"

// --- Position ---
double JSBSim_GetRawNorthPositionMeters() { return JSBSim_SafeGet("position/distance-from-start-lat-mt"); }
double JSBSim_GetRawEastPositionMeters()  { return JSBSim_SafeGet("position/distance-from-start-lon-mt"); }
double JSBSim_GetRawDownPositionMeters()  { return -JSBSim_SafeGet("position/h-sl-meters"); }
JSBSimVector3 JSBSim_GetRawPosition()     { return { JSBSim_GetRawNorthPositionMeters(), JSBSim_GetRawEastPositionMeters(), JSBSim_GetRawDownPositionMeters() }; }

double JSBSim_GetUnityPositionX()         { return JSBSim_GetRawEastPositionMeters(); }
double JSBSim_GetUnityPositionY()         { return -JSBSim_GetRawDownPositionMeters(); }
double JSBSim_GetUnityPositionZ()         { return JSBSim_GetRawNorthPositionMeters(); }
JSBSimVector3 JSBSim_GetUnityPosition()   { return { JSBSim_GetUnityPositionX(), JSBSim_GetUnityPositionY(), JSBSim_GetUnityPositionZ() }; }

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

