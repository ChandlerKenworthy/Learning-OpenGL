cmake_minimum_required(VERSION 3.20)

project(FluidSim)

# Find GLFW package
find_package(glfw3 REQUIRED)

# Add the executable target
add_executable(FluidSim main.c external/glad.c)

# Include directory containing glad.h
target_include_directories(FluidSim PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external)

# Link GLFW
target_link_libraries(FluidSim PRIVATE glfw)
