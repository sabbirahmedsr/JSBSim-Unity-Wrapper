#include "wrapper.h"
#include <FGFDMExec.h>
#include <simgear/misc/sg_path.hxx>
#include <algorithm>
#include <cmath>
#include <string>

template<typename T> static T MyClamp(T v, T lo, T hi) { return (v < lo) ? lo : (v > hi) ? hi : v; }

static JSBSim::FGFDMExec* g_fdm = nullptr;
static std::string g_dataPath, g_lastError, g_lastModel;
static bool g_initialized = false, g_aircraftLoaded = false;
static const char* g_quatPaths[4] = {"attitude/q0", "attitude/q1", "attitude/q2", "attitude/q3"};

static void NormalizePath(std::string& p) { std::replace(p.begin(), p.end(), '\\', '/'); while (!p.empty() && p.back() == '/') p.pop_back(); }
static bool IsValidProperty(const char* p) { return (g_fdm && p && p[0] != '\0'); }

// Property Access
void JSBSim_SetProperty(const char* p, double v) { if (IsValidProperty(p)) g_fdm->SetPropertyValue(p, v); }
double JSBSim_GetProperty(const char* p) { if (!IsValidProperty(p)) return 0.0; double v = g_fdm->GetPropertyValue(p); return (std::isnan(v) || std::isinf(v)) ? 0.0 : v; }
bool JSBSim_HasProperty(const char* p) { if (!IsValidProperty(p)) return false; return (g_fdm->GetPropertyManager()->GetNode(p) != nullptr); }

// Engine & Fuel
void JSBSim_SetThrottle(double v) { JSBSim_SetProperty("fcs/throttle-cmd-norm", MyClamp(v, 0.0, 1.0)); }
void JSBSim_SetMixture(double v) { JSBSim_SetProperty("fcs/mixture-cmd-norm", MyClamp(v, 0.0, 1.0)); }
void JSBSim_SetStarter(bool v) { JSBSim_SetProperty("propulsion/starter_cmd", v ? 1.0 : 0.0); }
void JSBSim_SetMagnetos(int v) { JSBSim_SetProperty("propulsion/magneto_cmd", (double)v); }
void JSBSim_SetEngineRunning(bool v) { JSBSim_SetProperty("propulsion/set-running", v ? 1.0 : 0.0); }
void JSBSim_SetFuelSelector(int v) { JSBSim_SetProperty("propulsion/fuel_selector_cmd", (double)v); }
double JSBSim_GetRPM() { return JSBSim_GetProperty("propulsion/engine[0]/rpm"); }
double JSBSim_GetEnginePower() { return JSBSim_GetProperty("propulsion/engine[0]/power-hp"); }
double JSBSim_GetFuelQuantity() { return JSBSim_GetProperty("propulsion/total-fuel-lbs"); }
double JSBSim_GetFuelLeft() { return JSBSim_HasProperty("propulsion/tank[0]/contents-lbs") ? JSBSim_GetProperty("propulsion/tank[0]/contents-lbs") : 0.0; }
double JSBSim_GetFuelRight() { return JSBSim_HasProperty("propulsion/tank[1]/contents-lbs") ? JSBSim_GetProperty("propulsion/tank[1]/contents-lbs") : 0.0; }
double JSBSim_GetOilTemperature() { return JSBSim_GetProperty("propulsion/engine[0]/oil-temp-degf"); }
double JSBSim_GetEGT() { return JSBSim_GetProperty("propulsion/engine[0]/EGT-degf"); }

// Flight Controls
void JSBSim_SetAileron(double v) { JSBSim_SetProperty("fcs/aileron-cmd-norm", MyClamp(v, -1.0, 1.0)); }
void JSBSim_SetElevator(double v) { JSBSim_SetProperty("fcs/elevator-cmd-norm", MyClamp(v, -1.0, 1.0)); }
void JSBSim_SetRudder(double v) { JSBSim_SetProperty("fcs/rudder-cmd-norm", MyClamp(v, -1.0, 1.0)); }
void JSBSim_SetTrim(double v) { JSBSim_SetProperty("fcs/pitch-trim-cmd-norm", MyClamp(v, -1.0, 1.0)); }
void JSBSim_SetFlaps(double v) { JSBSim_SetProperty("fcs/flap-cmd-norm", MyClamp(v, 0.0, 1.0)); }
void JSBSim_SetSteering(double v) { JSBSim_SetProperty("fcs/steer-cmd-norm", MyClamp(v, -1.0, 1.0)); }
void JSBSim_SetParkingBrake(bool v) { JSBSim_SetProperty("fcs/center-brake-cmd-norm", v ? 1.0 : 0.0); }
void JSBSim_SetLeftBrake(double v) { JSBSim_SetProperty("fcs/left-brake-cmd-norm", MyClamp(v, 0.0, 1.0)); }
void JSBSim_SetRightBrake(double v) { JSBSim_SetProperty("fcs/right-brake-cmd-norm", MyClamp(v, 0.0, 1.0)); }
double JSBSim_GetElevatorTrim() { return JSBSim_GetProperty("fcs/pitch-trim-cmd-norm"); }
double JSBSim_GetAileronPosition() { return JSBSim_GetProperty("fcs/left-aileron-pos-norm"); }
double JSBSim_GetElevatorPosition() { return JSBSim_GetProperty("fcs/elevator-pos-norm"); }
double JSBSim_GetRudderPosition() { return JSBSim_GetProperty("fcs/rudder-pos-norm"); }

// Aircraft State
bool JSBSim_GetEngineRunning() { return JSBSim_HasProperty("propulsion/engine[0]/running") ? JSBSim_GetProperty("propulsion/engine[0]/running") > 0.5 : JSBSim_GetRPM() > 100.0; }
bool JSBSim_GetNoseWOW() { return JSBSim_GetProperty("gear/unit[0]/WOW") > 0.5; }
bool JSBSim_GetLeftWOW() { return JSBSim_GetProperty("gear/unit[1]/WOW") > 0.5; }
bool JSBSim_GetRightWOW() { return JSBSim_GetProperty("gear/unit[2]/WOW") > 0.5; }
bool JSBSim_GetWOW() { return JSBSim_GetNoseWOW() || JSBSim_GetLeftWOW() || JSBSim_GetRightWOW(); }
bool JSBSim_GetParkingBrake() { return JSBSim_GetProperty("fcs/center-brake-cmd-norm") > 0.5; }
bool JSBSim_IsFlying() { return !JSBSim_GetWOW(); }
bool JSBSim_IsOnRunway() { return JSBSim_GetProperty("gear/unit[0]/on-runway") > 0.5; }
bool JSBSim_IsCrashed() { return JSBSim_GetProperty("simulation/crash-state") > 0.5; }

// Telemetry
double JSBSim_GetAirspeed() { return JSBSim_GetProperty("velocities/vc-kts"); }
double JSBSim_GetGroundSpeed() { return JSBSim_GetProperty("velocities/vg-kts"); }
double JSBSim_GetAltitude() { return JSBSim_GetProperty("position/h-sl-ft"); }
double JSBSim_GetAGL() { return JSBSim_GetProperty("position/h-agl-ft"); }
double JSBSim_GetPitch() { return JSBSim_GetProperty("attitude/theta-deg"); }
double JSBSim_GetRoll() { return JSBSim_GetProperty("attitude/phi-deg"); }
double JSBSim_GetHeading() { return JSBSim_GetProperty("attitude/heading-true-deg"); }
double JSBSim_GetVerticalSpeed() { return -JSBSim_GetProperty("velocities/v-down-fps"); }
double JSBSim_GetLatitude() { return JSBSim_GetProperty("position/lat-gc-deg"); }
double JSBSim_GetLongitude() { return JSBSim_GetProperty("position/long-gc-deg"); }
double JSBSim_GetAlpha() { return JSBSim_GetProperty("aero/alpha-deg"); }
double JSBSim_GetBeta() { return JSBSim_GetProperty("aero/beta-deg"); }
double JSBSim_GetNorthPosition() { return JSBSim_GetProperty("position/distance-from-start-lat-mt"); }
double JSBSim_GetEastPosition() { return JSBSim_GetProperty("position/distance-from-start-lon-mt"); }
double JSBSim_GetAltitudeMeters() { return JSBSim_GetProperty("position/h-sl-meters"); }
double JSBSim_GetDownPosition() { return -JSBSim_GetAltitudeMeters(); }
double JSBSim_GetVelocityX() { return JSBSim_GetProperty("velocities/v-east-fps"); }
double JSBSim_GetVelocityY() { return -JSBSim_GetProperty("velocities/v-down-fps"); }
double JSBSim_GetVelocityZ() { return JSBSim_GetProperty("velocities/v-north-fps"); }

// Quaternions
static double GetRawQuat(int i, double fallback) { return JSBSim_HasProperty(g_quatPaths[i]) ? JSBSim_GetProperty(g_quatPaths[i]) : fallback; }
double JSBSim_GetRawQuaternionW() { return GetRawQuat(0, 1.0); }
double JSBSim_GetRawQuaternionX() { return GetRawQuat(1, 0.0); }
double JSBSim_GetRawQuaternionY() { return GetRawQuat(2, 0.0); }
double JSBSim_GetRawQuaternionZ() { return GetRawQuat(3, 0.0); }
double JSBSim_GetUnityQuaternionW() { return JSBSim_GetRawQuaternionW(); }
double JSBSim_GetUnityQuaternionX() { return JSBSim_GetRawQuaternionY(); }
double JSBSim_GetUnityQuaternionY() { return -JSBSim_GetRawQuaternionZ(); }
double JSBSim_GetUnityQuaternionZ() { return -JSBSim_GetRawQuaternionX(); }

// Electrical & Systems
void JSBSim_SetMasterBattery(bool v) { JSBSim_SetProperty("systems/electrical/battery-switch", v ? 1.0 : 0.0); }
void JSBSim_SetMasterAlternator(bool v) { JSBSim_SetProperty("systems/electrical/alternator-switch", v ? 1.0 : 0.0); }
void JSBSim_SetAvionicsMaster(bool v) { JSBSim_SetProperty("systems/electrical/avionics-switch", v ? 1.0 : 0.0); }
bool JSBSim_GetMasterBattery() { return JSBSim_GetProperty("systems/electrical/battery-switch") > 0.5; }
bool JSBSim_GetAvionicsMaster() { return JSBSim_GetProperty("systems/electrical/avionics-switch") > 0.5; }
void JSBSim_SetBeaconLight(bool v) { JSBSim_SetProperty("lighting/beacon-switch", v ? 1.0 : 0.0); }
void JSBSim_SetLandingLight(bool v) { JSBSim_SetProperty("lighting/landing-light-switch", v ? 1.0 : 0.0); }
void JSBSim_SetTaxiLight(bool v) { JSBSim_SetProperty("lighting/taxi-light-switch", v ? 1.0 : 0.0); }
void JSBSim_SetNavLight(bool v) { JSBSim_SetProperty("lighting/nav-light-switch", v ? 1.0 : 0.0); }
void JSBSim_SetStrobeLight(bool v) { JSBSim_SetProperty("lighting/strobe-light-switch", v ? 1.0 : 0.0); }

// Initial Conditions
void JSBSim_SetInitialCondition(const char* p, double v) { JSBSim_SetProperty(p, v); }
void JSBSim_SetLatitude(double v) { JSBSim_SetProperty("ic/lat-gc-deg", v); }
void JSBSim_SetLongitude(double v) { JSBSim_SetProperty("ic/long-gc-deg", v); }
void JSBSim_SetAltitude(double v) { JSBSim_SetProperty("ic/h-sl-ft", v); }
void JSBSim_SetInitialPitch(double v) { JSBSim_SetProperty("ic/theta-deg", v); }
void JSBSim_SetInitialRoll(double v) { JSBSim_SetProperty("ic/phi-deg", v); }
void JSBSim_SetInitialHeading(double v) { JSBSim_SetProperty("ic/psi-true-deg", v); }

// Landing Gear
double JSBSim_GetNoseGearCompression() { return JSBSim_GetProperty("gear/unit[0]/compression-ft"); }
double JSBSim_GetLeftGearCompression() { return JSBSim_GetProperty("gear/unit[1]/compression-ft"); }
double JSBSim_GetRightGearCompression() { return JSBSim_GetProperty("gear/unit[2]/compression-ft"); }

// Simulation & Lifecycle
void JSBSim_Reset() { if (g_fdm) g_fdm->ResetToInitialConditions(true); }
void JSBSim_Pause(bool v) { if (g_fdm) (v ? g_fdm->SuspendIntegration() : g_fdm->ResumeIntegration()); }
void JSBSim_SetDeltaTime(double v) { if (g_fdm) g_fdm->Setdt(MyClamp(v, 0.0001, 0.5)); }
double JSBSim_GetSimTime() { return JSBSim_GetProperty("simulation/sim-time-sec"); }
bool JSBSim_RunFrame() { return g_fdm ? g_fdm->Run() : false; }
const char* JSBSim_GetLastError() { return g_lastError.c_str(); }
const char* JSBSim_GetLoadedAircraftName() { return g_lastModel.c_str(); }
const char* JSBSim_GetNextMessage() { return ""; }
bool JSBSim_Init() { if (g_fdm) return true; try { g_fdm = new JSBSim::FGFDMExec(); } catch (...) { g_lastError = "Failed to initialize JSBSim."; return false; } if (!g_fdm) { g_lastError = "FGFDMExec allocation failed."; return false; } g_fdm->SetDebugLevel(0); g_initialized = true; return true; }
void JSBSim_SetDataPath(const char* path) { if (!path) return; g_dataPath = path; NormalizePath(g_dataPath); if (g_fdm) g_fdm->SetRootDir(SGPath(g_dataPath)); }
bool JSBSim_LoadAircraft(const char* name) { if (!g_fdm || !name || g_dataPath.empty()) { g_lastError = "Data path not set."; return false; } g_aircraftLoaded = false; g_fdm->SetAircraftPath(SGPath(g_dataPath + "/aircraft")); g_fdm->SetEnginePath(SGPath(g_dataPath + "/engine")); g_fdm->SetSystemsPath(SGPath(g_dataPath + "/systems")); if (!g_fdm->LoadModel(name)) { g_lastError = "Failed to load aircraft."; return false; } g_lastModel = name; g_aircraftLoaded = true; return true; }
bool JSBSim_RunIC() { return g_fdm ? g_fdm->RunIC() : false; }
bool JSBSim_GetInitialized() { return g_initialized; }
bool JSBSim_GetAircraftLoaded() { return g_aircraftLoaded; }
void JSBSim_Shutdown() { if (g_fdm) { delete g_fdm; g_fdm = nullptr; } g_initialized = false; g_aircraftLoaded = false; g_lastError.clear(); g_lastModel.clear(); g_dataPath.clear(); }