#include "wrapper_transform.h"

// --- Helper ---
static double GetQ(int i, double f) {
    std::string p = "attitude/q" + std::to_string(i);
    return JSBSim_HasPropertyInternal(p.c_str()) ? JSBSim_SafeGet(p.c_str()) : f;
}

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

// --- Quaternions ---
double JSBSim_GetRawQuaternionW()         { return GetQ(0, 1.0); }
double JSBSim_GetRawQuaternionX()         { return GetQ(1, 0.0); }
double JSBSim_GetRawQuaternionY()         { return GetQ(2, 0.0); }
double JSBSim_GetRawQuaternionZ()         { return GetQ(3, 0.0); }
JSBSimQuaternion JSBSim_GetRawQuaternion() { return { JSBSim_GetRawQuaternionX(), JSBSim_GetRawQuaternionY(), JSBSim_GetRawQuaternionZ(), JSBSim_GetRawQuaternionW() }; }

double JSBSim_GetUnityQuaternionX()       { return JSBSim_GetRawQuaternionY(); }
double JSBSim_GetUnityQuaternionY()       { return -JSBSim_GetRawQuaternionZ(); }
double JSBSim_GetUnityQuaternionZ()       { return -JSBSim_GetRawQuaternionX(); }
double JSBSim_GetUnityQuaternionW()       { return JSBSim_GetRawQuaternionW(); }
JSBSimQuaternion JSBSim_GetUnityQuaternion() { return { JSBSim_GetUnityQuaternionX(), JSBSim_GetUnityQuaternionY(), JSBSim_GetUnityQuaternionZ(), JSBSim_GetUnityQuaternionW() }; }