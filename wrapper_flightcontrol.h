// wrapper_flightcontrol.h
#pragma once
#include "wrapper_global.h"
#include <cstdint>

// These structs must match the C# struct layout exactly
struct FlightControlCommand {
    double aileron;
    double elevator;
    double rudder;
    double pitchTrim;
    double rollTrim;
    double yawTrim;
    double flaps;
    double speedBrake;
    double noseWheelSteering;
    double leftBrake;
    double rightBrake;
    int32_t parkingBrake; // 0 for false, 1 for true
};

struct FlightControlData {
    float aileronPos;
    float elevatorPos;
    float rudderPos;
    float pitchTrimPos;
    float rollTrimPos;
    float yawTrimPos;
    float flapsPos;
    float speedBrakePos;
    float noseWheelSteeringPos;
    float leftBrakePos;
    float rightBrakePos;
    int32_t parkingBrakeState; // 0 for OFF, 1 for ON
};

extern "C" {

#define JSB_FUNC JSB_API
JSB_FUNC void JSBSim_SetFlightControls(FlightControlCommand* cmd);
JSB_FUNC void JSBSim_GetFlightControlData(FlightControlData* fcd);
#undef JSB_FUNC

}