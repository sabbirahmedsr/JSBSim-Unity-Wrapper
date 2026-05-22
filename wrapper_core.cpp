// wrapper_core.cpp
#include "wrapper_core.h"

// --- Global Variables ---
JSBSim::FGFDMExec* g_fdm = nullptr;
std::string g_dataPath, g_lastError, g_loadedAircraft;
bool g_initialized = false, g_aircraftLoaded = false;

// --- Utility Functions ---
void JSBSim_NormalizePath(std::string& path) {
    std::replace(path.begin(), path.end(), '\\', '/');
    while (!path.empty() && path.back() == '/') path.pop_back();
}

bool JSBSim_IsReady() { return g_fdm != nullptr; }

bool JSBSim_HasPropertyInternal(const char* property) {
    if (!g_fdm || !property || property[0] == '\0') return false;
    return g_fdm->GetPropertyManager()->GetNode(property) != nullptr;
}

double JSBSim_SafeGet(const char* property) {
    if (!JSBSim_HasPropertyInternal(property)) return 0.0;
    double value = g_fdm->GetPropertyValue(property);
    return (std::isnan(value) || std::isinf(value)) ? 0.0 : value;
}

void JSBSim_SafeSet(const char* property, double value) {
    if (JSBSim_IsReady()) g_fdm->SetPropertyValue(property, value);
}

// --- Lifecycle Management ---
bool JSBSim_Init() {
    if (g_fdm) return true;
    try {
        g_fdm = new JSBSim::FGFDMExec();
        g_fdm->SetDebugLevel(0);
        g_initialized = true;
        return true;
    } catch (...) {
        g_lastError = "Failed to initialize JSBSim.";
        return false;
    }
}

void JSBSim_Shutdown() {
    if (g_fdm) { delete g_fdm; g_fdm = nullptr; }
    g_initialized = g_aircraftLoaded = false;
    g_lastError.clear(); g_loadedAircraft.clear(); g_dataPath.clear();
}

// --- Configuration & Loading ---
void JSBSim_SetDataPath(const char* path) {
    if (!path) return;
    g_dataPath = path;
    JSBSim_NormalizePath(g_dataPath);
    if (g_fdm) g_fdm->SetRootDir(SGPath(g_dataPath));
}

bool JSBSim_LoadAircraft(const char* aircraftName) {
    if (!g_fdm || !aircraftName) return false;
    g_fdm->SetAircraftPath(SGPath(g_dataPath + "/aircraft"));
    g_fdm->SetEnginePath(SGPath(g_dataPath + "/engine"));
    g_fdm->SetSystemsPath(SGPath(g_dataPath + "/systems"));
    if (!g_fdm->LoadModel(aircraftName)) {
        g_lastError = "Failed to load aircraft.";
        return false;
    }
    g_loadedAircraft = aircraftName;
    g_aircraftLoaded = true;
    return true;
}

// --- Simulation Control ---
bool JSBSim_RunIC() { return g_fdm ? g_fdm->RunIC() : false; }
bool JSBSim_RunFrame() { return g_fdm ? g_fdm->Run() : false; }
void JSBSim_Reset() { if (g_fdm) g_fdm->ResetToInitialConditions(true); }
void JSBSim_Pause(bool pause) {
    if (!g_fdm) return;
    pause ? g_fdm->SuspendIntegration() : g_fdm->ResumeIntegration();
}
void JSBSim_SetDeltaTime(double dt) { if (g_fdm) g_fdm->Setdt(JSB_Clamp(dt, 0.0001, 0.5)); }

// --- Getters ---
double JSBSim_GetSimTime() { return JSBSim_SafeGet("simulation/sim-time-sec"); }
bool JSBSim_GetInitialized() { return g_initialized; }
bool JSBSim_GetAircraftLoaded() { return g_aircraftLoaded; }
const char* JSBSim_GetLoadedAircraftName() { return g_loadedAircraft.c_str(); }