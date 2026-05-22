// wrapper_flightcontrol.h
#pragma once
#include "wrapper_global.h"

extern "C" {

#define JSB_FUNC JSB_API

// --- Primary Controls ---
JSB_FUNC void JSBSim_SetAileron(double value);
JSB_FUNC void JSBSim_SetElevator(double value);
JSB_FUNC void JSBSim_SetRudder(double value);
JSB_FUNC void JSBSim_SetElevatorTrim(double value);
JSB_FUNC void JSBSim_SetFlaps(double value);
JSB_FUNC void JSBSim_SetSteering(double value);

// --- Brakes ---
JSB_FUNC void JSBSim_SetParkingBrake(bool value);
JSB_FUNC void JSBSim_SetLeftBrake(double value);
JSB_FUNC void JSBSim_SetRightBrake(double value);

// --- Get Positions ---
JSB_FUNC double JSBSim_GetAileronPosition();
JSB_FUNC double JSBSim_GetElevatorPosition();
JSB_FUNC double JSBSim_GetRudderPosition();
JSB_FUNC double JSBSim_GetFlapsPosition();
JSB_FUNC double JSBSim_GetElevatorTrimPosition();

#undef JSB_FUNC
}