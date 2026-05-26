// wrapper_transform.h

#pragma once
#include "wrapper_global.h"

// --- Structs ---
struct JSBSimVector3 { float x, y, z; };

// Struct with self-explanatory variable names for clarity
struct TransformData {
    JSBSimVector3 rawGEOPosition;     // Latitude, Longitude, Altitude/Distance
    JSBSimVector3 unityGEOPosition;   // Geo position mapped to Unity world
    JSBSimVector3 rawNEUPosition;     // North, East, Up (Local)
    JSBSimVector3 unityNEUPosition;   // NEU mapped to Unity (X, Y, Z)
    JSBSimVector3 rawVelocityFPS;     // Velocity Feet per second
    JSBSimVector3 unityVelocityFPS;   // Velocity Feet per second
    JSBSimVector3 rawEulerAngles;     // Degrees
    JSBSimVector3 unityEulerAngles;   // Degrees
    float   geoDistanceMeters;        // Meters
    float   unitySpeedFPS;            // Feet per second
};

#ifdef __cplusplus
extern "C" {
#endif

    // Only one function needed to get all transform data
    JSB_API void JSBSim_GetTransformData(TransformData* outData);

#ifdef __cplusplus
}
#endif