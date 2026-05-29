#pragma once
#include "wrapper_global.h"
#include <cstdint>

// Command structure to send landing gear inputs from Unity to JSBSim
struct LandingGearCommand {
    int8_t gearDownEnable; // 1 = trigger gear down, 0 = trigger gear up
};

// Data structure to receive landing gear feedback from JSBSim to Unity
struct LandingGearData {
    // 1. Operational Status
    int8_t isGearDown;           // True if gear is fully locked down
    float gearPosNorm;           // Current extension (0.0=up, 1.0=down)

    // 2. Ground Interaction & WOW (Weight On Wheels)
    int8_t isOnGround;           // True if the aircraft is touching the ground
    int8_t noseWOWState;         // True if nose wheel carries weight
    int8_t leftWOWState;         // True if left wheel carries weight
    int8_t rightWOWState;        // True if right wheel carries weight

    // 3. Structural Health
    int8_t isNoseGearBroken;     // True if nose gear structural failure occurs
    int8_t isLeftGearBroken;     // True if left gear structural failure occurs
    int8_t isRightGearBroken;    // True if right gear structural failure occurs

    // 4. Dynamics (Compression in meters)
    float noseGearCompression;   // Suspension compression in meters
    float leftGearCompression;   // Suspension compression in meters
    float rightGearCompression;  // Suspension compression in meters

    // 5. Kinematics & Control Feedback
    float noseWheelSteeringDeg;  // Nose wheel steering angle (degrees)
    float noseWheelSpeedFPS;     // Nose wheel rotation speed (FPS)
    float leftWheelSpeedFPS;     // Left wheel rotation speed (FPS)
    float rightWheelSpeedFPS;    // Right wheel rotation speed (FPS)
};

extern "C" {
    JSB_API void JSBSim_ProcessLandingGearCommand(LandingGearCommand* cmd);    
    JSB_API void JSBSim_GetLandingGearData(LandingGearData* data);
}