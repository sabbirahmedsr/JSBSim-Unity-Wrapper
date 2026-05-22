// wrapper_debug.h
#pragma once
#include "wrapper_global.h"

extern "C" {

#define JSB_FUNC JSB_API

// --- Generic Property Access ---
JSB_FUNC void JSBSim_SetProperty(const char* property, double value);
JSB_FUNC double JSBSim_GetProperty(const char* property);
JSB_FUNC bool JSBSim_HasProperty(const char* property);

// --- Debug ---
JSB_FUNC const char* JSBSim_GetLastError();

#undef JSB_FUNC
}