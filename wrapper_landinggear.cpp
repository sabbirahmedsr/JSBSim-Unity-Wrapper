#include "wrapper_landinggear.h"

// Static variable to track the last command state to avoid redundant calls
static int8_t lastGearCommand = -1;

void JSBSim_ProcessLandingGearCommand(LandingGearCommand* cmd) {
    if (!cmd) return;

    // Only send the command to JSBSim if the state has changed
    if (cmd->gearDownEnable != lastGearCommand) {
        // 1.0 for Down, 0.0 for Up
        JSBSim_SafeSet("gear/gear-cmd-norm", cmd->gearDownEnable ? 1.0 : 0.0);
        lastGearCommand = cmd->gearDownEnable;
    }
}

void JSBSim_GetLandingGearData(LandingGearData* data) {
    if (!data) return;

    // 1. Operational Status
    data->isGearDown = JSBSim_SafeGet("gear/gear-pos-norm") > 0.95;
    data->gearPosNorm = (float)JSBSim_SafeGet("gear/gear-pos-norm");

    // 2. Ground Interaction & WOW (Weight On Wheels)
    data->noseWOWState = JSBSim_SafeGet("gear/unit[0]/WOW") > 0.5;
    data->leftWOWState = JSBSim_SafeGet("gear/unit[1]/WOW") > 0.5;
    data->rightWOWState = JSBSim_SafeGet("gear/unit[2]/WOW") > 0.5;
    
    // Logic: If any wheel has weight, the plane is on the ground
    data->isOnGround = (data->noseWOWState || data->leftWOWState || data->rightWOWState);

    // 3. Structural Health (Assuming properties exist in your JSBSim model)
    data->isNoseGearBroken = JSBSim_SafeGet("gear/unit[0]/broken") > 0.5;
    data->isLeftGearBroken = JSBSim_SafeGet("gear/unit[1]/broken") > 0.5;
    data->isRightGearBroken = JSBSim_SafeGet("gear/unit[2]/broken") > 0.5;

    // 4. Dynamics (Converting Feet to Meters: * 0.3048)
    data->noseGearCompression = (float)(JSBSim_SafeGet("gear/unit[0]/compression-ft") * 0.3048);
    data->leftGearCompression = (float)(JSBSim_SafeGet("gear/unit[1]/compression-ft") * 0.3048);
    data->rightGearCompression = (float)(JSBSim_SafeGet("gear/unit[2]/compression-ft") * 0.3048);

    // 5. Kinematics & Control Feedback
    data->noseWheelSteeringDeg = (float)JSBSim_SafeGet("gear/unit[0]/steering-pos-deg");
    data->noseWheelSpeedFPS = (float)JSBSim_SafeGet("gear/unit[0]/wheel-speed-fps");
    data->leftWheelSpeedFPS = (float)JSBSim_SafeGet("gear/unit[1]/wheel-speed-fps");
    data->rightWheelSpeedFPS = (float)JSBSim_SafeGet("gear/unit[2]/wheel-speed-fps");
}