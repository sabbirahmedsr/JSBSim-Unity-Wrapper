cmake_minimum_required(VERSION 3.10)

project(JSBSimUnityWrapper)

# Add all source file
add_library(JSBSimUnityWrapper SHARED
    wrapper.cpp
    wrapper_core.cpp
    wrapper_setup.cpp
    wrapper_engine.cpp
    wrapper_electrical.cpp
    wrapper_flightcontrol.cpp
    wrapper_landinggear.cpp
    wrapper_telemetry.cpp
    wrapper_transform.cpp     
    wrapper_miscellaneous.cpp
    wrapper_debug.cpp
)

# MSVC Specific: Ignore C4251 warning
if(MSVC)
    target_compile_options(JSBSimUnityWrapper PRIVATE /wd4251)
    # Optional: Ensure modern C++ features
    target_compile_features(JSBSimUnityWrapper PRIVATE cxx_std_17)
endif()

# Header files are in the current directory
target_include_directories(JSBSimUnityWrapper PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../jsbsim/src
)

# Link JSBSim library
# Note: It is better to use a variable for the path or find_library
target_link_libraries(JSBSimUnityWrapper PRIVATE
    "C:/Users/SabbirAhmedSR/Desktop/JSBSim/jsbsim/build/src/Release/JSBSim.lib"
)