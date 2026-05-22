// wrapper_transform.cpp
#include "wrapper_transform.h"

// --- Helper Functions ---
static double GetRawQuaternionValue(int index, double fallback) {
    std::string property = "attitude/q" + std::to_string(index);
    return JSBSim_HasPropertyInternal(property.c_str()) ? JSBSim_SafeGet(property.c_str()) : fallback;
}

// --- Raw Position (NED) ---
double JSBSim_GetRawNorthPositionMeters() { return JSBSim_SafeGet("position/distance-from-start-lat-mt"); }
double JSBSim_GetRawEastPositionMeters()  { return JSBSim_SafeGet("position/distance-from-start-lon-mt"); }
double JSBSim_GetRawDownPositionMeters()  { return -JSBSim_SafeGet("position/h-sl-meters"); }
JSBSimVector3 JSBSim_GetRawPosition()     { return { JSBSim_GetRawNorthPositionMeters(), JSBSim_GetRawEastPositionMeters(), JSBSim_GetRawDownPositionMeters() }; }

// --- Unity Position (EUN) ---
double JSBSim_GetUnityPositionX() { return JSBSim_GetRawEastPositionMeters(); }
double JSBSim_GetUnityPositionY() { return -JSBSim_GetRawDownPositionMeters(); }
double JSBSim_GetUnityPositionZ() { return JSBSim_GetRawNorthPositionMeters(); }
JSBSimVector3 JSBSim_GetUnityPosition() { return { JSBSim_GetUnityPositionX(), JSBSim_GetUnityPositionY(), JSBSim_GetUnityPositionZ() }; }

// --- Raw Velocity (NED) ---
double JSBSim_GetRawVelocityNorthFPS() { return JSBSim_SafeGet("velocities/v-north-fps"); }
double JSBSim_GetRawVelocityEastFPS()  { return JSBSim_SafeGet("velocities/v-east-fps"); }
double JSBSim_GetRawVelocityDownFPS()  { return JSBSim_SafeGet("velocities/v-down-fps"); }
JSBSimVector3 JSBSim_GetRawVelocity()  { return { JSBSim_GetRawVelocityNorthFPS(), JSBSim_GetRawVelocityEastFPS(), JSBSim_GetRawVelocityDownFPS() }; }

// --- Unity Velocity (EUN) ---
double JSBSim_GetUnityVelocityX() { return JSBSim_GetRawVelocityEastFPS(); }
double JSBSim_GetUnityVelocityY() { return -JSBSim_GetRawVelocityDownFPS(); }
double JSBSim_GetUnityVelocityZ() { return JSBSim_GetRawVelocityNorthFPS(); }
JSBSimVector3 JSBSim_GetUnityVelocity() { return { JSBSim_GetUnityVelocityX(), JSBSim_GetUnityVelocityY(), JSBSim_GetUnityVelocityZ() }; }

// --- Raw Quaternion (NED) ---
double JSBSim_GetRawQuaternionW() { return GetRawQuaternionValue(0, 1.0); }
double JSBSim_GetRawQuaternionX() { return GetRawQuaternionValue(1, 0.0); }
double JSBSim_GetRawQuaternionY() { return GetRawQuaternionValue(2, 0.0); }
double JSBSim_GetRawQuaternionZ() { return GetRawQuaternionValue(3, 0.0); }
JSBSimQuaternion JSBSim_GetRawQuaternion() { return { JSBSim_GetRawQuaternionX(), JSBSim_GetRawQuaternionY(), JSBSim_GetRawQuaternionZ(), JSBSim_GetRawQuaternionW() }; }

// --- Unity Quaternion (EUN) ---
double JSBSim_GetUnityQuaternionW() { return JSBSim_GetRawQuaternionW(); }
double JSBSim_GetUnityQuaternionX() { return JSBSim_GetRawQuaternionY(); }
double JSBSim_GetUnityQuaternionY() { return -JSBSim_GetRawQuaternionZ(); }
double JSBSim_GetUnityQuaternionZ() { return -JSBSim_GetRawQuaternionX(); }
JSBSimQuaternion JSBSim_GetUnityQuaternion() { return { JSBSim_GetUnityQuaternionX(), JSBSim_GetUnityQuaternionY(), JSBSim_GetUnityQuaternionZ(), JSBSim_GetUnityQuaternionW() }; }