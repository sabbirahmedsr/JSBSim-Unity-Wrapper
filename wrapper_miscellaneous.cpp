#include "wrapper_miscellaneous.h"

void JSBSim_GetMiscellaneousData(MiscellaneousData* md) {
    if (!md) return;

    // --- ENVIRONMENT DATA MAPPING ---
    // Note: JSBSim properties may need unit conversion (e.g., Rankine to Fahrenheit)
    md->outsideAirTempF = (float)JSBSim_SafeGet("atmosphere/T-R") - 459.67f;
    md->windSpeedKts    = (float)JSBSim_SafeGet("atmosphere/wind-speed-kt");
    md->windDirDeg      = (float)JSBSim_SafeGet("atmosphere/wind-direction-deg");

    // --- INSTRUMENTS & WARNINGS MAPPING ---
    md->stallWarning    = (JSBSim_SafeGet("warnings/stall-warning") > 0.5f) ? 1 : 0;
    md->suctionInHg     = (float)JSBSim_SafeGet("instrumentation/vacuum-gauge/suction-inhg");
    md->altimeterSetting = (float)JSBSim_SafeGet("instrumentation/altimeter/setting-inhg");
}