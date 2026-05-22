cmake_minimum_required(VERSION 3.10)

project(JSBSimUnityWrapper)

add_library(JSBSimUnityWrapper SHARED
    wrapper.cpp
)

# MSVC Specific: Ignore C4251 warning
if(MSVC)
    target_compile_options(JSBSimUnityWrapper PRIVATE /wd4251)
endif()

target_include_directories(JSBSimUnityWrapper PRIVATE
    ../jsbsim/src
)

target_link_libraries(JSBSimUnityWrapper PRIVATE
    "C:/Users/SabbirAhmedSR/Desktop/JSBSim/jsbsim/build/src/Release/JSBSim.lib"
)