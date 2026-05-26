// wrapper_transform.h
#pragma once
#include "wrapper_global.h"

#ifdef __cplusplus
extern "C" {
#endif

    // GEO POSITION: Delta from spawn (Meters)
    JSB_API double JSBSim_GetGEOLatitudeMeters();
    JSB_API double JSBSim_GetGEOLongitudeMeters();
    JSB_API double JSBSim_GetGEODistanceMeters();
    JSB_API JSBSimVector3 JSBSim_GetRawGEOPosition();
    JSB_API JSBSimVector3 JSBSim_GetUnityGEOPosition();

    // NEU POSITION: Local simulation (Feet)
    JSB_API double JSBSim_GetNEUNorthFeet();
    JSB_API double JSBSim_GetNEUEastFeet();
    JSB_API double JSBSim_GetNEUUpFeet();
    JSB_API JSBSimVector3 JSBSim_GetRawNEUPosition();
    JSB_API JSBSimVector3 JSBSim_GetUnityNEUPosition();

    // Velocity
    JSB_API double JSBSim_GetRawVelocityNorthFPS();
    JSB_API double JSBSim_GetRawVelocityEastFPS();
    JSB_API double JSBSim_GetRawVelocityDownFPS();
    JSB_API JSBSimVector3 JSBSim_GetRawVelocity();
    JSB_API double JSBSim_GetUnityVelocityX();
    JSB_API double JSBSim_GetUnityVelocityY();
    JSB_API double JSBSim_GetUnityVelocityZ();
    JSB_API JSBSimVector3 JSBSim_GetUnityVelocity();

    // Rotation
    JSB_API JSBSimVector3 JSBSim_GetRawEulerAngles();
    JSB_API JSBSimVector3 JSBSim_GetUnityEulerAngles();

#ifdef __cplusplus
}
#endif