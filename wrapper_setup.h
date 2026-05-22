// wrapper_setup.h
#pragma once
#include "wrapper_global.h"

extern "C" {

    #define JSB_FUNC JSB_API

    // --- Initial State Configuration ---
    JSB_FUNC void JSBSim_SetInitialLatitude(double value);
    JSB_FUNC void JSBSim_SetInitialLongitude(double value);
    JSB_FUNC void JSBSim_SetInitialAltitudeFeet(double value);
    JSB_FUNC void JSBSim_SetInitialHeadingDegrees(double value);
    JSB_FUNC void JSBSim_SetInitialPitchDegrees(double value);
    JSB_FUNC void JSBSim_SetInitialRollDegrees(double value);

    // --- Velocity Configuration ---
    JSB_FUNC void JSBSim_SetInitialNorthVelocityFPS(double value);
    JSB_FUNC void JSBSim_SetInitialEastVelocityFPS(double value);
    JSB_FUNC void JSBSim_SetInitialDownVelocityFPS(double value);
    JSB_FUNC void JSBSim_SetInitialForwardVelocityFPS(double value);

    // --- Systems State ---
    JSB_FUNC void JSBSim_SetInitialEngineRunning(bool value);
    JSB_FUNC void JSBSim_SetInitialOnGround(bool value);

    #undef JSB_FUNC
}