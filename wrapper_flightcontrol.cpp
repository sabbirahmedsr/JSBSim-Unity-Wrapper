// wrapper_flightcontrol.cpp
#include "wrapper_flightcontrol.h"

// --- Primary Controls ---
void JSBSim_SetAileron(double v)      { JSBSim_SafeSet("fcs/aileron-cmd-norm", JSB_Clamp(v, -1.0, 1.0)); }
void JSBSim_SetElevator(double v)     { JSBSim_SafeSet("fcs/elevator-cmd-norm", JSB_Clamp(v, -1.0, 1.0)); }
void JSBSim_SetRudder(double v)       { JSBSim_SafeSet("fcs/rudder-cmd-norm", JSB_Clamp(v, -1.0, 1.0)); }
void JSBSim_SetElevatorTrim(double v) { JSBSim_SafeSet("fcs/pitch-trim-cmd-norm", JSB_Clamp(v, -1.0, 1.0)); }
void JSBSim_SetFlaps(double v)        { JSBSim_SafeSet("fcs/flap-cmd-norm", JSB_Clamp(v, 0.0, 1.0)); }
void JSBSim_SetSteering(double v)     { JSBSim_SafeSet("fcs/steer-cmd-norm", JSB_Clamp(v, -1.0, 1.0)); }

// --- Brakes ---
void JSBSim_SetParkingBrake(bool v)   { JSBSim_SafeSet("fcs/center-brake-cmd-norm", v ? 1.0 : 0.0); }
void JSBSim_SetLeftBrake(double v)    { JSBSim_SafeSet("fcs/left-brake-cmd-norm", JSB_Clamp(v, 0.0, 1.0)); }
void JSBSim_SetRightBrake(double v)   { JSBSim_SafeSet("fcs/right-brake-cmd-norm", JSB_Clamp(v, 0.0, 1.0)); }

// --- Get Positions ---
double JSBSim_GetAileronPosition()      { return JSBSim_SafeGet("fcs/left-aileron-pos-norm"); }
double JSBSim_GetElevatorPosition()     { return JSBSim_SafeGet("fcs/elevator-pos-norm"); }
double JSBSim_GetRudderPosition()       { return JSBSim_SafeGet("fcs/rudder-pos-norm"); }
double JSBSim_GetFlapsPosition()        { return JSBSim_SafeGet("fcs/flap-pos-norm"); }
double JSBSim_GetElevatorTrimPosition() { return JSBSim_SafeGet("fcs/pitch-trim-cmd-norm"); }