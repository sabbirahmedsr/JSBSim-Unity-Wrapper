// wrapper_telemetry.cpp

#include "wrapper_telemetry.h"

JSB_API void JSBSim_GetTelemetryData(TelemetryData* outData) {
    if (!outData) return;

    // GEOGRAPHIC DATA
    outData->latitudeDegrees    = JSBSim_SafeGet("position/lat-gc-deg");
    outData->longitudeDegrees   = JSBSim_SafeGet("position/long-gc-deg");

    // VELOCITY & AIR DATA
    outData->airspeedKTS        = static_cast<float>(JSBSim_SafeGet("velocities/vc-kts"));
    outData->groundSpeedKTS     = static_cast<float>(JSBSim_SafeGet("velocities/vg-kts"));
    outData->verticalSpeedFPS   = static_cast<float>(-JSBSim_SafeGet("velocities/v-down-fps"));

    // POSITION & ORIENTATION DATA
    outData->altitudeFeet       = static_cast<float>(JSBSim_SafeGet("position/h-sl-ft"));
    outData->altitudeMeters     = static_cast<float>(JSBSim_SafeGet("position/h-sl-meters"));
    outData->alphaDegrees       = static_cast<float>(JSBSim_SafeGet("aero/alpha-deg"));
    outData->betaDegrees        = static_cast<float>(JSBSim_SafeGet("aero/beta-deg"));

    // ATTITUDE & HEADING
    outData->pitchDegrees       = static_cast<float>(JSBSim_SafeGet("attitude/theta-deg"));
    outData->rollDegrees        = static_cast<float>(JSBSim_SafeGet("attitude/phi-deg"));
    outData->headingDegrees     = static_cast<float>(JSBSim_SafeGet("attitude/psi-deg"));
}

// --- Attitude ---
double JSBSim_GetPitchDegrees()       { return JSBSim_SafeGet("attitude/theta-deg"); }
double JSBSim_GetRollDegrees()        { return JSBSim_SafeGet("attitude/phi-deg"); }
double JSBSim_GetHeadingDegrees()     { return JSBSim_SafeGet("attitude/psi-deg"); }
