// wrapper_aircraft.h
#pragma once
#include "wrapper_global.h"

extern "C" {

#define JSB_FUNC JSB_API

// --- Aircraft State ---
JSB_FUNC bool JSBSim_GetWOW();
JSB_FUNC bool JSBSim_GetNoseWOW();
JSB_FUNC bool JSBSim_GetLeftWOW();
JSB_FUNC bool JSBSim_GetRightWOW();
JSB_FUNC bool JSBSim_IsOnGround();
JSB_FUNC bool JSBSim_IsFlying();
JSB_FUNC bool JSBSim_IsCrashed();
JSB_FUNC bool JSBSim_IsOnRunway();

// --- Gear Compression ---
JSB_FUNC double JSBSim_GetNoseGearCompressionFeet();
JSB_FUNC double JSBSim_GetLeftGearCompressionFeet();
JSB_FUNC double JSBSim_GetRightGearCompressionFeet();

// --- Parking Brake ---
JSB_FUNC bool JSBSim_GetParkingBrakeState();

#undef JSB_FUNC
}