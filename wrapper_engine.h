// wrapper_engine.h
#pragma once
#include "wrapper_global.h"

extern "C" {

#define JSB_FUNC JSB_API

// --- Engine Controls ---
JSB_FUNC void JSBSim_SetThrottle(double value);
JSB_FUNC void JSBSim_SetMixture(double value);
JSB_FUNC void JSBSim_SetStarter(bool value);
JSB_FUNC void JSBSim_SetMagnetos(int value);
JSB_FUNC void JSBSim_SetFuelSelector(int value);
JSB_FUNC void JSBSim_SetEngineRunning(bool value);

// --- Engine Data ---
JSB_FUNC bool JSBSim_GetEngineRunning();
JSB_FUNC double JSBSim_GetRPM();
JSB_FUNC double JSBSim_GetEnginePowerHP();
JSB_FUNC double JSBSim_GetFuelTotalLBS();
JSB_FUNC double JSBSim_GetFuelLeftLBS();
JSB_FUNC double JSBSim_GetFuelRightLBS();
JSB_FUNC double JSBSim_GetOilTemperatureF();
JSB_FUNC double JSBSim_GetEGTF();

#undef JSB_FUNC
}