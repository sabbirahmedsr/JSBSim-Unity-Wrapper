#pragma once
#include "wrapper_global.h"

#pragma pack(push, 8)
// Telemetry structure containing flight state, dynamics, and positioning data
struct TelemetryData {
    // --- GEOGRAPHIC DATA ---
    double latitudeDegrees;    // Current latitude coordinate in degrees
    double longitudeDegrees;   // Current longitude coordinate in degrees
    // --- VELOCITY & AIR DATA ---
    float airspeedKTS;         // Aircraft speed relative to the surrounding air in Knots
    float groundSpeedKTS;      // Aircraft speed relative to the ground surface in Knots
    float verticalSpeedFPS;    // Rate of climb or descent in Feet per Second
    // --- POSITION & ORIENTATION DATA ---
    float altitudeFeet;        // Elevation above Mean Sea Level (MSL) in Feet
    float altitudeMeters;      // Elevation above Mean Sea Level (MSL) in Meters
    float alphaDegrees;        // Angle of Attack: Angle between wing chord and airflow
    float betaDegrees;         // Sideslip angle: Angle of fuselage relative to airflow
    // --- ATTITUDE & HEADING ---
    float pitchDegrees;        // Aircraft nose up/down rotation around lateral axis
    float rollDegrees;         // Aircraft bank left/right rotation around longitudinal axis
    float headingDegrees;      // Compass direction the nose is pointing in degrees
    // --- PERFORMANCE & DYNAMICS ---
    float verticalG;           // Current vertical G-load force acting on the aircraft
};
#pragma pack(pop)

#ifdef __cplusplus
extern "C" {
#endif

    JSB_API void JSBSim_GetTelemetryData(TelemetryData* outData);
    // Attitude
JSB_API double JSBSim_GetPitchDegrees();
JSB_API double JSBSim_GetRollDegrees();
JSB_API double JSBSim_GetHeadingDegrees();

#ifdef __cplusplus
}
#endif