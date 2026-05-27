@echo off
echo Setting up Visual Studio 2022 environment...
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

echo Navigating to project directory...
cd /d "C:\Users\SabbirAhmedSR\Desktop\JSBSim\JSBSimUnityWrapper"

echo Cleaning and recreating build directory...
if exist build rmdir /s /q build
mkdir build
cd build

echo Running CMake configuration...
cmake ..

echo Building the project in Release mode...
cmake --build . --config Release

echo Checking for the generated DLL...
if exist "Release\JSBSimUnityWrapper.dll" (
    echo DLL found. Copying to Unity plugins folder...
    copy /Y "Release\JSBSimUnityWrapper.dll" "E:\Unity\Client Project\++BAF++\BAF Pilot Simulator JSBSim BIRP\Assets\Plugins\x86_64\"
    echo --- Success: DLL copied successfully ---
) else (
    echo --- Error: DLL Not Found in Release folder ---
)

echo.
echo Process complete.
pause