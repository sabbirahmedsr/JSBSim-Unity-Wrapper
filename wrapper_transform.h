// wrapper_transform.h
#pragma once
#include "wrapper_global.h"

// --- Structs ---
struct JSBSimVector3 { double x, y, z; };
struct JSBSimQuaternion { double w, x, y, z; };

extern "C" {

#define JSB_FUNC JSB_API

// Raw Position (NED)
JSB_FUNC double JSBSim_GetRawNorthPositionMeters();
JSB_FUNC double JSBSim_GetRawEastPositionMeters();
JSB_FUNC double JSBSim_GetRawDownPositionMeters();
JSB_FUNC JSBSimVector3 JSBSim_GetRawPosition();

// Unity Position (EUN)
JSB_FUNC double JSBSim_GetUnityPositionX();
JSB_FUNC double JSBSim_GetUnityPositionY();
JSB_FUNC double JSBSim_GetUnityPositionZ();
JSB_FUNC JSBSimVector3 JSBSim_GetUnityPosition();

// Raw Velocity (NED)
JSB_FUNC double JSBSim_GetRawVelocityNorthFPS();
JSB_FUNC double JSBSim_GetRawVelocityEastFPS();
JSB_FUNC double JSBSim_GetRawVelocityDownFPS();
JSB_FUNC JSBSimVector3 JSBSim_GetRawVelocity();

// Unity Velocity (EUN)
JSB_FUNC double JSBSim_GetUnityVelocityX();
JSB_FUNC double JSBSim_GetUnityVelocityY();
JSB_FUNC double JSBSim_GetUnityVelocityZ();
JSB_FUNC JSBSimVector3 JSBSim_GetUnityVelocity();

// Raw Quaternion (NED)
JSB_FUNC double JSBSim_GetRawQuaternionW();
JSB_FUNC double JSBSim_GetRawQuaternionX();
JSB_FUNC double JSBSim_GetRawQuaternionY();
JSB_FUNC double JSBSim_GetRawQuaternionZ();
JSB_FUNC JSBSimQuaternion JSBSim_GetRawQuaternion();

// Unity Quaternion (EUN)
JSB_FUNC double JSBSim_GetUnityQuaternionW();
JSB_FUNC double JSBSim_GetUnityQuaternionX();
JSB_FUNC double JSBSim_GetUnityQuaternionY();
JSB_FUNC double JSBSim_GetUnityQuaternionZ();
JSB_FUNC JSBSimQuaternion JSBSim_GetUnityQuaternion();

#undef JSB_FUNC
}