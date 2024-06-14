# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(RayTracer LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files (replace these with your actual source files)
add_executable(raytracer
    src/main.cpp
    # Add all other source files
)

# Include directories (if needed)
# target_include_directories(raytracer PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Find and link OpenMP
find_package(OpenMP REQUIRED)

if(OpenMP_CXX_FOUND)
    target_link_libraries(raytracer PUBLIC OpenMP::OpenMP_CXX)
endif()

# Link other libraries if necessary
# target_link_libraries(raytracer PRIVATE some_library)
