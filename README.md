# JSBSim Unity Wrapper

Native JSBSim plugin for Unity.

---


## 🛠 Build DLL

Open **x64 Native Tools Command Prompt for VS**:

```cmd

cd "C:\Users\SabbirAhmedSR\Desktop\JSBSim\JSBSimUnityWrapper"
if exist build rmdir /s /q build
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

## 🚀 Initialization

```cpp
JSBSim_Init();
JSBSim_SetDataPath("path/to/JSBSim");
JSBSim_LoadAircraft("c172x");
JSBSim_RunIC();
```

---

## ⚠️ Notes

- Call `JSBSim_Shutdown()` before closing Unity.
- `JSBSim_RunIC()` must be called after loading aircraft.
- Invalid or NaN properties safely return `0.0`.

---
