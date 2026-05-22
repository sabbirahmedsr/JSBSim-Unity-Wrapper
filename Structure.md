# JSBSim Unity Wrapper Structure

This project connects the JSBSim physics engine to Unity. Below is the simplified module structure and a quick reference for the contents of each file.

## 📂 Source Code Modules

```

JSBSimUnityWrapper/
│
├── wrapper_core.h/cpp           // Lifecycle & Loop: Init, Shutdown, RunFrame, TimeStep
├── wrapper_setup.h/cpp          // FDM Config: LoadAircraft, RunInitialConditions, Reset
├── wrapper_engine.h/cpp         // Propulsion: Throttle, RPM, Fuel, Mixture, Magnetos
├── wrapper_flightcontrol.h/cpp  // Pilot Inputs: Ailerons, Elevators, Rudder, Flaps, Brakes
├── wrapper_telemetry.h/cpp      // Data Output: Airspeed, Altitude, VSI, Heading, AOA
├── wrapper_transform.h/cpp      // Spatial Data: Position, NED-to-EUN conversion, Quaternions
├── wrapper_aircraft.h/cpp       // State Tracking: WOW (Weight on Wheels), Gear, Crash
├── wrapper_avionic.h/cpp        // Systems: Battery, Alternator, Avionics, Lighting
├── wrapper_debug.h/cpp          // Diagnostics: GetLastError, Validation, SafetyChecks
│
├── wrapper_global.h             // Utilities: JSB_API macros, Shared helper functions
└── wrapper.h/cpp                // Public API: Aggregates all modules for Unity access

```

## 🔍 Module Details

* **Core:** Manages the simulation's heart—starting, stopping, and keeping the frame rate synchronized.
* **Setup:** Handles the initial setup (loading the aircraft XML) and resetting the physics state.
* **Engine:** Controls engine power, starting, and fuel consumption.
* **Flight Control:** Maps joystick or keyboard input to physical flight surfaces.
* **Telemetry:** Provides all the flight metrics needed for your dashboard or HUD.
* **Transform:** Translates JSBSim's "North-East-Down" physics coordinates to Unity's coordinate system.
* **Aircraft:** Tracks critical status flags like "are we on the ground?" or "did we crash?".
* **Avionic:** Controls the electrical bus, cockpit electronics, and external lights.
* **Debug:** A safety net to catch errors and inspect properties if something goes wrong.
* **Wrapper/Globals:** The bridge that makes all these C++ functions visible and callable from Unity C#.