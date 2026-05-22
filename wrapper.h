#pragma once

#ifdef _WIN32
#define JSB_API __declspec(dllexport)
#else
#define JSB_API
#endif

extern "C" {
    // Property Access
    JSB_API void JSBSim_SetProperty(const char* p, double v);
    JSB_API double JSBSim_GetProperty(const char* p);
    JSB_API bool JSBSim_HasProperty(const char* p);

    // Engine & Fuel
    JSB_API void JSBSim_SetThrottle(double v);
    JSB_API void JSBSim_SetMixture(double v);
    JSB_API void JSBSim_SetStarter(bool v);
    JSB_API void JSBSim_SetMagnetos(int v);
    JSB_API void JSBSim_SetEngineRunning(bool v);
    JSB_API void JSBSim_SetFuelSelector(int v);
    JSB_API double JSBSim_GetRPM();
    JSB_API double JSBSim_GetEnginePower();
    JSB_API double JSBSim_GetFuelQuantity();
    JSB_API double JSBSim_GetFuelLeft();
    JSB_API double JSBSim_GetFuelRight();
    JSB_API double JSBSim_GetOilTemperature();
    JSB_API double JSBSim_GetEGT();

    // Flight Controls
    JSB_API void JSBSim_SetAileron(double v);
    JSB_API void JSBSim_SetElevator(double v);
    JSB_API void JSBSim_SetRudder(double v);
    JSB_API void JSBSim_SetTrim(double v);
    JSB_API void JSBSim_SetFlaps(double v);
    JSB_API void JSBSim_SetSteering(double v);
    JSB_API void JSBSim_SetParkingBrake(bool v);
    JSB_API void JSBSim_SetLeftBrake(double v);
    JSB_API void JSBSim_SetRightBrake(double v);
    JSB_API double JSBSim_GetElevatorTrim();
    JSB_API double JSBSim_GetAileronPosition();
    JSB_API double JSBSim_GetElevatorPosition();
    JSB_API double JSBSim_GetRudderPosition();

    // Aircraft State
    JSB_API bool JSBSim_GetEngineRunning();
    JSB_API bool JSBSim_GetWOW();
    JSB_API bool JSBSim_GetParkingBrake();
    JSB_API bool JSBSim_IsFlying();
    JSB_API bool JSBSim_IsOnRunway();
    JSB_API bool JSBSim_IsCrashed();

    // Telemetry
    JSB_API double JSBSim_GetAirspeed();
    JSB_API double JSBSim_GetGroundSpeed();
    JSB_API double JSBSim_GetAltitude();
    JSB_API double JSBSim_GetAGL();
    JSB_API double JSBSim_GetPitch();
    JSB_API double JSBSim_GetRoll();
    JSB_API double JSBSim_GetHeading();
    JSB_API double JSBSim_GetVerticalSpeed();
    JSB_API double JSBSim_GetLatitude();
    JSB_API double JSBSim_GetLongitude();
    JSB_API double JSBSim_GetAlpha();
    JSB_API double JSBSim_GetBeta();

    // Position & Velocity
    JSB_API double JSBSim_GetNorthPosition();
    JSB_API double JSBSim_GetEastPosition();
    JSB_API double JSBSim_GetAltitudeMeters();
    JSB_API double JSBSim_GetDownPosition();
    JSB_API double JSBSim_GetVelocityX();
    JSB_API double JSBSim_GetVelocityY();
    JSB_API double JSBSim_GetVelocityZ();

    // Quaternions
    JSB_API double JSBSim_GetRawQuaternionW();
    JSB_API double JSBSim_GetRawQuaternionX();
    JSB_API double JSBSim_GetRawQuaternionY();
    JSB_API double JSBSim_GetRawQuaternionZ();
    JSB_API double JSBSim_GetUnityQuaternionW();
    JSB_API double JSBSim_GetUnityQuaternionX();
    JSB_API double JSBSim_GetUnityQuaternionY();
    JSB_API double JSBSim_GetUnityQuaternionZ();

    // Electrical & Lighting
    JSB_API void JSBSim_SetMasterBattery(bool v);
    JSB_API void JSBSim_SetMasterAlternator(bool v);
    JSB_API void JSBSim_SetAvionicsMaster(bool v);
    JSB_API bool JSBSim_GetMasterBattery();
    JSB_API bool JSBSim_GetAvionicsMaster();
    JSB_API void JSBSim_SetBeaconLight(bool v);
    JSB_API void JSBSim_SetLandingLight(bool v);
    JSB_API void JSBSim_SetTaxiLight(bool v);
    JSB_API void JSBSim_SetNavLight(bool v);
    JSB_API void JSBSim_SetStrobeLight(bool v);

    // Initial Conditions
    JSB_API void JSBSim_SetInitialCondition(const char* p, double v);
    JSB_API void JSBSim_SetLatitude(double v);
    JSB_API void JSBSim_SetLongitude(double v);
    JSB_API void JSBSim_SetAltitude(double v);
    JSB_API void JSBSim_SetInitialPitch(double v);
    JSB_API void JSBSim_SetInitialRoll(double v);
    JSB_API void JSBSim_SetInitialHeading(double v);

    // Landing Gear
    JSB_API double JSBSim_GetNoseGearCompression();
    JSB_API double JSBSim_GetLeftGearCompression();
    JSB_API double JSBSim_GetRightGearCompression();
    JSB_API bool JSBSim_GetNoseWOW();
    JSB_API bool JSBSim_GetLeftWOW();
    JSB_API bool JSBSim_GetRightWOW();

    // Simulation & Lifecycle
    JSB_API void JSBSim_Reset();
    JSB_API void JSBSim_Pause(bool v);
    JSB_API void JSBSim_SetDeltaTime(double v);
    JSB_API double JSBSim_GetSimTime();
    JSB_API bool JSBSim_RunFrame();
    JSB_API const char* JSBSim_GetLastError();
    JSB_API const char* JSBSim_GetLoadedAircraftName();
    JSB_API const char* JSBSim_GetNextMessage();
    JSB_API bool JSBSim_Init();
    JSB_API void JSBSim_SetDataPath(const char* path);
    JSB_API bool JSBSim_LoadAircraft(const char* name);
    JSB_API bool JSBSim_RunIC();
    JSB_API bool JSBSim_GetInitialized();
    JSB_API bool JSBSim_GetAircraftLoaded();
    JSB_API void JSBSim_Shutdown();
}