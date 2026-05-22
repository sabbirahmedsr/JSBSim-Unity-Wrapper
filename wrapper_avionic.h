// wrapper_avionic.h
#pragma once
#include "wrapper_global.h"

extern "C" {

#define JSB_FUNC JSB_API

// --- Electrical Controls & State ---
JSB_FUNC void JSBSim_SetMasterBattery(bool value);
JSB_FUNC void JSBSim_SetMasterAlternator(bool value);
JSB_FUNC void JSBSim_SetAvionicsMaster(bool value);

JSB_FUNC bool JSBSim_GetMasterBattery();
JSB_FUNC bool JSBSim_GetMasterAlternator();
JSB_FUNC bool JSBSim_GetAvionicsMaster();

// --- Lighting Controls & State ---
JSB_FUNC void JSBSim_SetBeaconLight(bool value);
JSB_FUNC void JSBSim_SetLandingLight(bool value);
JSB_FUNC void JSBSim_SetTaxiLight(bool value);
JSB_FUNC void JSBSim_SetNavigationLight(bool value);
JSB_FUNC void JSBSim_SetStrobeLight(bool value);

JSB_FUNC bool JSBSim_GetBeaconLight();
JSB_FUNC bool JSBSim_GetLandingLight();
JSB_FUNC bool JSBSim_GetTaxiLight();
JSB_FUNC bool JSBSim_GetNavigationLight();
JSB_FUNC bool JSBSim_GetStrobeLight();

#undef JSB_FUNC
}