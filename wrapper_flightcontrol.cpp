// wrapper_flightcontrol.cpp
#include "wrapper_flightcontrol.h"
#include <cmath>
#include <algorithm>

static FlightControlCommand lastFcc = { 0 };

static bool HasChanged(float val1, float val2) {
    return std::abs(val1 - val2) > 0.001f;
}

void JSBSim_ProcessFlightControlCommand(FlightControlCommand* cmd) {
    if (!cmd) return;

    // 1. Primary Surfaces (Always Update)
    JSBSim_SafeSet("fcs/aileron-cmd-norm", cmd->aileron);
    JSBSim_SafeSet("fcs/elevator-cmd-norm", cmd->elevator);
    JSBSim_SafeSet("fcs/rudder-cmd-norm", cmd->rudder);

    // 2. Trim Controls (Always Update for maximum responsiveness)
    JSBSim_SafeSet("fcs/pitch-trim-cmd-norm", cmd->pitchTrim);
    JSBSim_SafeSet("fcs/roll-trim-cmd-norm", cmd->rollTrim);
    JSBSim_SafeSet("fcs/yaw-trim-cmd-norm", cmd->yawTrim);

    // 3. Secondary Surfaces (Always Update)
    JSBSim_SafeSet("fcs/flap-cmd-norm", cmd->flaps);
    JSBSim_SafeSet("fcs/speedbrake-cmd-norm", cmd->speedBrake);
    JSBSim_SafeSet("fcs/steer-cmd-norm", cmd->noseWheelSteering);

    // 4. Brakes (Updated via Dirty Flag for performance)
    if (HasChanged(cmd->leftBrake, lastFcc.leftBrake)) {
        JSBSim_SafeSet("fcs/left-brake-cmd-norm", cmd->leftBrake);
        lastFcc.leftBrake = cmd->leftBrake;
    }
    if (HasChanged(cmd->rightBrake, lastFcc.rightBrake)) {
        JSBSim_SafeSet("fcs/right-brake-cmd-norm", cmd->rightBrake);
        lastFcc.rightBrake = cmd->rightBrake;
    }

    // 5. Parking Brake (Event-based)
    if (cmd->parkingBrake != lastFcc.parkingBrake) {
        JSBSim_SafeSet("fcs/center-brake-cmd-norm", (double)cmd->parkingBrake);
        lastFcc.parkingBrake = cmd->parkingBrake;
    }
}

void JSBSim_GetFlightControlData(FlightControlData* fcd) {
    if (!fcd) return;

    fcd->aileronPos = (float)JSBSim_SafeGet("fcs/left-aileron-pos-norm");
    fcd->elevatorPos = (float)JSBSim_SafeGet("fcs/elevator-pos-norm");
    fcd->rudderPos = (float)JSBSim_SafeGet("fcs/rudder-pos-norm");
    
    fcd->pitchTrimPos = (float)JSBSim_SafeGet("fcs/pitch-trim-cmd-norm");
    fcd->rollTrimPos = (float)JSBSim_SafeGet("fcs/roll-trim-cmd-norm");
    fcd->yawTrimPos = (float)JSBSim_SafeGet("fcs/yaw-trim-cmd-norm");   
    
    fcd->flapsPos = (float)JSBSim_SafeGet("fcs/flap-pos-norm");
    fcd->speedBrakePos = (float)JSBSim_SafeGet("fcs/speedbrake-pos-norm");
    fcd->noseWheelSteeringPos = (float)JSBSim_SafeGet("fcs/steer-pos-norm");
    
    fcd->leftBrakePos = (float)JSBSim_SafeGet("fcs/left-brake-pos-norm");
    fcd->rightBrakePos = (float)JSBSim_SafeGet("fcs/right-brake-pos-norm");
    
    fcd->parkingBrakeState = (JSBSim_SafeGet("fcs/center-brake-cmd-norm") > 0.5) ? 1 : 0;
}

/*
// --- Set Flight Controls ---
void JSBSim_SetFlightControls(FlightControlCommand* cmd) {
    if (!cmd) return;

    // Primary Surfaces
    JSBSim_SafeSet("fcs/aileron-cmd-norm", JSB_Clamp(cmd->aileron, -1.0, 1.0));
    JSBSim_SafeSet("fcs/elevator-cmd-norm", JSB_Clamp(cmd->elevator, -1.0, 1.0));
    JSBSim_SafeSet("fcs/rudder-cmd-norm", JSB_Clamp(cmd->rudder, -1.0, 1.0));

    // Trims
    JSBSim_SafeSet("fcs/pitch-trim-cmd-norm", JSB_Clamp(cmd->pitchTrim, -1.0, 1.0));
    JSBSim_SafeSet("fcs/roll-trim-cmd-norm", JSB_Clamp(cmd->rollTrim, -1.0, 1.0));
    JSBSim_SafeSet("fcs/yaw-trim-cmd-norm", JSB_Clamp(cmd->yawTrim, -1.0, 1.0));

    // Flaps, Speedbrake, Steering
    JSBSim_SafeSet("fcs/flap-cmd-norm", JSB_Clamp(cmd->flaps, 0.0, 1.0));
    JSBSim_SafeSet("fcs/speedbrake-cmd-norm", JSB_Clamp(cmd->speedBrake, 0.0, 1.0));
    JSBSim_SafeSet("fcs/steer-cmd-norm", JSB_Clamp(cmd->noseWheelSteering, -1.0, 1.0));

    // Brakes
    JSBSim_SafeSet("fcs/left-brake-cmd-norm", JSB_Clamp(cmd->leftBrake, 0.0, 1.0));
    JSBSim_SafeSet("fcs/right-brake-cmd-norm", JSB_Clamp(cmd->rightBrake, 0.0, 1.0));
    JSBSim_SafeSet("fcs/center-brake-cmd-norm", cmd->parkingBrake ? 1.0 : 0.0);
}

// --- Get Flight Control Data ---
void JSBSim_GetFlightControlData(FlightControlData* fcd) {
    if (!fcd) return;

    // Existing struct pointer is updated directly
    fcd->aileronPos = (float)JSBSim_SafeGet("fcs/left-aileron-pos-norm");
    fcd->elevatorPos = (float)JSBSim_SafeGet("fcs/elevator-pos-norm");
    fcd->rudderPos = (float)JSBSim_SafeGet("fcs/rudder-pos-norm");
    
    fcd->pitchTrimPos = (float)JSBSim_SafeGet("fcs/pitch-trim-cmd-norm");
    fcd->rollTrimPos = (float)JSBSim_SafeGet("fcs/roll-trim-cmd-norm");
    fcd->yawTrimPos = (float)JSBSim_SafeGet("fcs/yaw-trim-cmd-norm");    
    
    fcd->flapsPos = (float)JSBSim_SafeGet("fcs/flap-pos-norm");
    fcd->speedBrakePos = (float)JSBSim_SafeGet("fcs/speedbrake-pos-norm");
    fcd->noseWheelSteeringPos = (float)JSBSim_SafeGet("fcs/steer-pos-norm");
    
    fcd->leftBrakePos = (float)JSBSim_SafeGet("fcs/left-brake-pos-norm");
    fcd->rightBrakePos = (float)JSBSim_SafeGet("fcs/right-brake-pos-norm");

    double pBrake = JSBSim_SafeGet("fcs/center-brake-cmd-norm");
    fcd->parkingBrakeState = (pBrake > 0.5) ? 1 : 0;
}

*/