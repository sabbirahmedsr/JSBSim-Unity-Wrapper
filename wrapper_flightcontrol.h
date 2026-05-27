// wrapper_flightcontrol.h
#pragma once
#include "wrapper_global.h"
#include <cstdint> // Required for int32_t and int8_t

// Command from Unity to JSBSim
struct FlightControlCommand {
    float aileron, elevator, rudder;          // Primary surfaces: -1.0 to 1.0
    float pitchTrim, rollTrim, yawTrim;       // Trim settings
    float flaps;                              // Flaps position: 0.0 to 1.0
    float speedBrake;                         // Speed brake: 0.0 to 1.0
    float noseWheelSteering;                  // Steering input: -1.0 to 1.0
    float leftBrake, rightBrake;              // Brake pressure: 0.0 to 1.0
    int8_t parkingBrake;                      // 1 byte: 1=ON, 0=OFF (Matches MarshalAs I1)
};

// Receives flight control status back from JSBSim
struct FlightControlData {
    float aileronPos, elevatorPos, rudderPos; // Actual surface positions
    float pitchTrimPos, rollTrimPos, yawTrimPos; 
    float flapsPos;                           // Current flaps position
    float speedBrakePos;                      // Current speed brake position
    float noseWheelSteeringPos;               // Current nose wheel angle
    float leftBrakePos, rightBrakePos;        // Actual brake engagement level
    int8_t parkingBrakeState;                 // 1 byte: 1=ON, 0=OFF
};

extern "C" {
#define JSB_FUNC JSB_API
JSB_FUNC void JSBSim_ProcessFlightControlCommand(FlightControlCommand* cmd);
JSB_FUNC void JSBSim_GetFlightControlData(FlightControlData* fcd);
#undef JSB_FUNC
}