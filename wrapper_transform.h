// wrapper_transform.h
#pragma once
#include "wrapper_global.h"

#ifdef __cplusplus
extern "C" {
#endif

    // Position
    JSB_API double JSBSim_GetRawNorthPositionMeters();
    JSB_API double JSBSim_GetRawEastPositionMeters();
    JSB_API double JSBSim_GetRawDownPositionMeters();
    JSB_API JSBSimVector3 JSBSim_GetRawPosition();
    JSB_API double JSBSim_GetUnityPositionX();
    JSB_API double JSBSim_GetUnityPositionY();
    JSB_API double JSBSim_GetUnityPositionZ();
    JSB_API JSBSimVector3 JSBSim_GetUnityPosition();

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