cmake_minimum_required(VERSION 3.10)

project(tetris_v3)

# Set C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Source files
file(GLOB SOURCES "src/*.cpp")

# Create executable
add_executable(tetris_v3 ${SOURCES})

# Platform-specific libraries
if(WIN32)
    # Windows specific libraries if needed
    target_link_libraries(tetris_v3)
else()
    # Linux specific libraries if needed
    target_link_libraries(tetris_v3)
endif()