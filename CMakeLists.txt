cmake_minimum_required(VERSION 3.20)

project(FluidSim)

# Find GLFW package
find_package(glfw3 REQUIRED)

# Add the executable target
add_executable(FluidSim main.cpp external/glad.c src/Shader.cpp)

# Set C++ standard to C++17
target_compile_features(FluidSim PRIVATE cxx_std_17)

# Include directory containing glad.h
target_include_directories(FluidSim PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external include)

# Link GLFW
target_link_libraries(FluidSim PRIVATE glfw)
