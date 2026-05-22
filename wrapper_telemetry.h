// wrapper_telemetry.h
#pragma once
#include "wrapper_global.h"

extern "C" {

// Air Data
JSB_API double JSBSim_GetAirspeedKTS();
JSB_API double JSBSim_GetGroundSpeedKTS();
JSB_API double JSBSim_GetMach();
JSB_API double JSBSim_GetVerticalSpeedFPS();

// Position
JSB_API double JSBSim_GetAltitudeFeet();
JSB_API double JSBSim_GetAltitudeMeters();
JSB_API double JSBSim_GetAGLFeet();
JSB_API double JSBSim_GetLatitudeDegrees();
JSB_API double JSBSim_GetLongitudeDegrees();

// Attitude
JSB_API double JSBSim_GetPitchDegrees();
JSB_API double JSBSim_GetRollDegrees();
JSB_API double JSBSim_GetHeadingDegrees();

// Aero
JSB_API double JSBSim_GetAlphaDegrees();
JSB_API double JSBSim_GetBetaDegrees();

}