#include "wrapper_transform.h"
#include "wrapper_telemetry.h"

static constexpr double F2M = 0.3048;

JSB_API void JSBSim_GetTransformData(TransformData* outData) {
    if (!outData) return;

    // Fetching data from JSBSim
    double lat = JSBSim_SafeGet("position/distance-from-start-lat-mt");
    double lon = JSBSim_SafeGet("position/distance-from-start-lon-mt");
    double mag = JSBSim_SafeGet("position/distance-from-start-mag-mt");

    double n   = JSBSim_SafeGet("position/from-start-neu-n-ft");
    double e   = JSBSim_SafeGet("position/from-start-neu-e-ft");
    double u   = JSBSim_SafeGet("position/from-start-neu-u-ft");

    double vN  = JSBSim_SafeGet("velocities/v-north-fps");
    double vE  = JSBSim_SafeGet("velocities/v-east-fps");
    double vD  = JSBSim_SafeGet("velocities/v-down-fps");

    double pitch = JSBSim_GetPitchDegrees();
    double head  = JSBSim_GetHeadingDegrees();
    double roll  = JSBSim_GetRollDegrees();

    // Mapping with unit conversion (Double to Float)
    outData->rawGEOPosition     = { (float)lat, (float)lon, (float)mag };
    outData->unityGEOPosition   = { (float)lon, 0.0f, (float)lat };
    
    outData->rawNEUPosition     = { (float)(n * F2M), (float)(e * F2M), (float)(u * F2M) };
    outData->unityNEUPosition   = { (float)(e * F2M), (float)(u * F2M), (float)(n * F2M) };
    
    outData->rawVelocityFPS     = { (float)vN, (float)vE, (float)vD };
    outData->unityVelocityFPS   = { (float)vE, (float)(-vD), (float)vN };
    
    outData->rawEulerAngles     = { (float)pitch, (float)head, (float)roll };
    outData->unityEulerAngles   = { (float)(-pitch), (float)head, (float)(-roll) };

    outData->geoDistanceMeters  = (float)mag;
    
    // Unity speed calculation in FPS
    float vX = outData->unityVelocityFPS.x;
    float vY = outData->unityVelocityFPS.y;
    float vZ = outData->unityVelocityFPS.z;
    outData->unitySpeedFPS      = sqrtf(vX * vX + vY * vY + vZ * vZ);
}