#pragma once
#include "wrapper_global.h"

// Ensures the memory layout matches the C# struct exactly
#pragma pack(push, 8)
struct InitialStateParameter {
    // GEOGRAPHIC POSITIONING
    double latitudeDegrees;    // Initial latitude coordinate in degrees
    double longitudeDegrees;   // Initial longitude coordinate in degrees
    double altitudeFeet;       // Starting altitude above sea level in feet
    // ATTITUDE
    double headingDegrees;     // Initial compass direction of the nose
    double pitchDegrees;       // Initial nose up/down angle
    double rollDegrees;        // Initial bank angle (left/right tilt)
    // VELOCITY VECTORS
    double northVelocityFPS;   // Starting speed towards North (feet/second)
    double eastVelocityFPS;    // Starting speed towards East (feet/second)
    double downVelocityFPS;    // Starting vertical speed (feet/second)
    double forwardVelocityFPS; // Starting speed along the nose direction
    double airspeedKTS;        // Starting airspeed in Knots
    // ENGINE & SYSTEMS
    float throttle;            // Engine power level from 0.0 (idle) to 1.0 (full)
    float mixture;             // Fuel/air ratio control from 0.0 to 1.0
    bool parkingBrake;         // True if the parking brake is locked at start
    bool engineRunning;        // True if the engine is already running
};
#pragma pack(pop)

#ifdef __cplusplus
extern "C" {
#endif

    // Function to pass initialization data from Unity to JSBSim
    JSB_API void JSBSim_SetInitialConditions(InitialStateParameter* ic);

#ifdef __cplusplus
}
#endif