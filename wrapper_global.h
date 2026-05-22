// wrapper_global.h
#pragma once

#ifdef _WIN32
#define JSB_API __declspec(dllexport)
#else
#define JSB_API __attribute__((visibility("default")))
#endif

#include <FGFDMExec.h>
#include <simgear/misc/sg_path.hxx>
#include <string>
#include <algorithm>

template<typename T>
static T JSB_Clamp(T v, T lo, T hi) { return std::max(lo, std::min(v, hi)); }

extern JSBSim::FGFDMExec* g_fdm;
extern std::string g_dataPath, g_lastError, g_loadedAircraft;
extern bool g_initialized, g_aircraftLoaded;

// --- Structs ---
struct JSBSimVector3 { double x, y, z; };
struct JSBSimQuaternion { double x, y, z, w; };

void JSBSim_NormalizePath(std::string& path);
bool JSBSim_IsReady();
double JSBSim_SafeGet(const char* property);
void JSBSim_SafeSet(const char* property, double value);
bool JSBSim_HasPropertyInternal(const char* property);

