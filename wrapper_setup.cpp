// wrapper_setup.cpp
#include "wrapper_setup.h"

// --- Position & Orientation ---
void JSBSim_SetInitialLatitude(double v)        { JSBSim_SafeSet("ic/lat-gc-deg", v); }
void JSBSim_SetInitialLongitude(double v)       { JSBSim_SafeSet("ic/long-gc-deg", v); }
void JSBSim_SetInitialAltitudeFeet(double v)    { JSBSim_SafeSet("ic/h-sl-ft", v); }
void JSBSim_SetInitialHeadingDegrees(double v)  { JSBSim_SafeSet("ic/psi-true-deg", v); }
void JSBSim_SetInitialPitchDegrees(double v)    { JSBSim_SafeSet("ic/theta-deg", v); }
void JSBSim_SetInitialRollDegrees(double v)     { JSBSim_SafeSet("ic/phi-deg", v); }

// --- Velocity Configuration ---
void JSBSim_SetInitialNorthVelocityFPS(double v)   { JSBSim_SafeSet("ic/v-north-fps", v); }
void JSBSim_SetInitialEastVelocityFPS(double v)    { JSBSim_SafeSet("ic/v-east-fps", v); }
void JSBSim_SetInitialDownVelocityFPS(double v)    { JSBSim_SafeSet("ic/v-down-fps", v); }
void JSBSim_SetInitialForwardVelocityFPS(double v) { JSBSim_SafeSet("ic/u-fps", v); }

// --- Systems State ---
void JSBSim_SetInitialEngineRunning(bool v) { JSBSim_SafeSet("propulsion/set-running", v ? 1.0 : 0.0); }
void JSBSim_SetInitialOnGround(bool v)      { JSBSim_SafeSet("ic/on-ground", v ? 1.0 : 0.0); }