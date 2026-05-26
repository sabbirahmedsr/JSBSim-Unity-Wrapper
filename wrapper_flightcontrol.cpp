// wrapper_flightcontrol.cpp
#include "wrapper_flightcontrol.h"

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

