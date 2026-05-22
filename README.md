# JSBSim Unity Wrapper

Native JSBSim plugin for Unity.

---


## 🛠 Build DLL

Open **x64 Native Tools Command Prompt for VS**:

```cmd

cd "C:\Users\SabbirAhmedSR\Desktop\JSBSim\JSBSimUnityWrapper"
mkdir build
cd build
cmake ..
cmake --build . --config Release

```

Generated DLL:

```text
build/Release/JSBSimUnityWrapper.dll
```

Move the DLL into:

```text
Assets/Plugins/x86_64/
```

---

## 🌍 Coordinate System

| JSBSim (NED) | Unity (EUN) |
|---|---|
| North | +Z |
| East | +X |
| Down | -Y |

JSBSim uses a right-handed NED system.  
Unity uses a left-handed EUN system.

The wrapper automatically converts vectors and Unity quaternion outputs.

---

## 🔄 Quaternion Functions

### Raw JSBSim Quaternion

Original NED quaternion values:

```cpp
JSBSim_GetRawQuaternionW();
JSBSim_GetRawQuaternionX();
JSBSim_GetRawQuaternionY();
JSBSim_GetRawQuaternionZ();
```

### Unity Quaternion

Converted Unity-ready quaternion values:

```cpp
JSBSim_GetUnityQuaternionW();
JSBSim_GetUnityQuaternionX();
JSBSim_GetUnityQuaternionY();
JSBSim_GetUnityQuaternionZ();
```

Current conversion:

```cpp
Unity X =  Raw Y
Unity Y = -Raw Z
Unity Z = -Raw X
Unity W =  Raw W
```

---

## 🚀 Initialization

```cpp
JSBSim_Init();
JSBSim_SetDataPath("path/to/JSBSim");
JSBSim_LoadAircraft("c172x");
JSBSim_RunIC();
```

---

## 📏 Units

- Position → Meters
- Angles → Degrees
- Velocity → Feet/sec
- Airspeed → Knots

---

## ⚠️ Notes

- Call `JSBSim_Shutdown()` before closing Unity.
- `JSBSim_RunIC()` must be called after loading aircraft.
- Invalid or NaN properties safely return `0.0`.

---
