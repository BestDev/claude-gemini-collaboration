# CMakeLists.txt for Tetris V2
# Cross-platform build configuration for C++17 Tetris game

cmake_minimum_required(VERSION 3.10)
project(TetrisV2)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable debug symbols in debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
endif()

# Find SFML package
# On Ubuntu/Debian: sudo apt-get install libsfml-dev
# On Windows: Install SFML and set SFML_ROOT if needed
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Include directories
include_directories(include)

# Collect all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

# Create the executable
add_executable(tetris_v2 ${SOURCES} ${HEADERS})

# Link SFML libraries
target_link_libraries(tetris_v2 sfml-graphics sfml-window sfml-system)

# Platform-specific configurations
if(WIN32)
    # On Windows, copy SFML DLLs to output directory
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(SFML_LIBS_DEBUG
            ${SFML_ROOT}/bin/sfml-graphics-d-2.dll
            ${SFML_ROOT}/bin/sfml-window-d-2.dll
            ${SFML_ROOT}/bin/sfml-system-d-2.dll
        )
        foreach(LIB ${SFML_LIBS_DEBUG})
            if(EXISTS ${LIB})
                configure_file(${LIB} ${CMAKE_BINARY_DIR} COPYONLY)
            endif()
        endforeach()
    else()
        set(SFML_LIBS_RELEASE
            ${SFML_ROOT}/bin/sfml-graphics-2.dll
            ${SFML_ROOT}/bin/sfml-window-2.dll
            ${SFML_ROOT}/bin/sfml-system-2.dll
        )
        foreach(LIB ${SFML_LIBS_RELEASE})
            if(EXISTS ${LIB})
                configure_file(${LIB} ${CMAKE_BINARY_DIR} COPYONLY)
            endif()
        endforeach()
    endif()
endif()

# Copy assets to build directory
if(EXISTS ${CMAKE_SOURCE_DIR}/assets)
    file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
    message(STATUS "Assets copied to build directory")
else()
    message(WARNING "Assets directory not found - game may not display fonts correctly")
endif()

# Installation (optional)
install(TARGETS tetris_v2 DESTINATION bin)
if(EXISTS ${CMAKE_SOURCE_DIR}/assets)
    install(DIRECTORY assets DESTINATION .)
endif()

# Display configuration summary
message(STATUS "")
message(STATUS "=== Tetris V2 Configuration Summary ===")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "SFML version: ${SFML_VERSION}")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "=====================================")
message(STATUS "")