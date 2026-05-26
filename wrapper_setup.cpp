// wrapper_setup.cpp
#include "wrapper_setup.h"

JSB_API void JSBSim_SetInitialConditions(InitialStateParameter* ic) {
    if (!ic) return;

    // GEOGRAPHIC & ATTITUDE
    JSBSim_SafeSet("ic/lat-gc-deg", ic->latitudeDegrees);
    JSBSim_SafeSet("ic/long-gc-deg", ic->longitudeDegrees);
    JSBSim_SafeSet("ic/h-sl-ft", ic->altitudeFeet);
    
    JSBSim_SafeSet("ic/psi-true-deg", ic->headingDegrees);
    JSBSim_SafeSet("ic/theta-deg", ic->pitchDegrees);
    JSBSim_SafeSet("ic/phi-deg", ic->rollDegrees);

    // VELOCITY VECTORS
    JSBSim_SafeSet("ic/v-north-fps", ic->northVelocityFPS);
    JSBSim_SafeSet("ic/v-east-fps", ic->eastVelocityFPS);
    JSBSim_SafeSet("ic/v-down-fps", ic->downVelocityFPS);
    JSBSim_SafeSet("ic/u-fps", ic->forwardVelocityFPS);
    JSBSim_SafeSet("ic/vt-kts", ic->airspeedKTS);

    // ENGINE & SYSTEMS
    JSBSim_SafeSet("fcs/throttle-cmd-norm", ic->throttle);
    JSBSim_SafeSet("fcs/mixture-cmd-norm", ic->mixture); 
       
    // Boolean mapping to float (1.0 for true, 0.0 for false)
    JSBSim_SafeSet("gear/parkbrake-cmd", ic->parkingBrake ? 1.0 : 0.0);
    JSBSim_SafeSet("propulsion/set-running", ic->engineRunning ? 1.0 : 0.0);
}