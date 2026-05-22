// wrapper_debug.cpp
#include "wrapper_debug.h"

// --- Generic Property Access ---
void JSBSim_SetProperty(const char* p, double v) { JSBSim_SafeSet(p, v); }
double JSBSim_GetProperty(const char* p)         { return JSBSim_SafeGet(p); }
bool JSBSim_HasProperty(const char* p)           { return JSBSim_HasPropertyInternal(p); }

// --- Debug ---
const char* JSBSim_GetLastError() { return g_lastError.c_str(); }