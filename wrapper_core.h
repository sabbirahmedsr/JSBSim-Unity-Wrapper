// wrapper_core.h
#pragma once
#include "wrapper_global.h"

extern "C" {
    
    #define JSB_FUNC JSB_API

    JSB_FUNC bool JSBSim_Init();
    JSB_FUNC void JSBSim_Shutdown();
    JSB_FUNC void JSBSim_SetDataPath(const char* path);
    JSB_FUNC bool JSBSim_LoadAircraft(const char* name);
    JSB_FUNC bool JSBSim_RunIC();
    JSB_FUNC bool JSBSim_RunFrame();
    JSB_FUNC void JSBSim_Reset();
    JSB_FUNC void JSBSim_Pause(bool pause);
    JSB_FUNC void JSBSim_SetDeltaTime(double dt);
    JSB_FUNC double JSBSim_GetSimTime();
    JSB_FUNC bool JSBSim_GetInitialized();
    JSB_FUNC bool JSBSim_GetAircraftLoaded();
    JSB_FUNC const char* JSBSim_GetLoadedAircraftName();

    #undef JSB_FUNC
}