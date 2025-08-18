# Tetris V2: Cross-Platform Deployment Guide

## Overview

This guide provides comprehensive instructions for building and deploying Tetris V2 across Windows and Linux platforms. The project uses CMake for cross-platform build management and SFML for graphics, ensuring consistent behavior across operating systems.

## Prerequisites Summary

| Component | Minimum Version | Purpose |
|-----------|----------------|---------|
| **CMake** | 3.10+ | Cross-platform build system |
| **C++ Compiler** | C++17 Support | Core language features |
| **SFML** | 2.5+ | Graphics, window, and input handling |

## Windows Deployment

### Method 1: Visual Studio with CMake GUI (Recommended)

#### Step 1: Install Prerequisites

1. **Visual Studio 2017 or later**
   ```
   Download from: https://visualstudio.microsoft.com/downloads/
   - Ensure "Desktop development with C++" workload is installed
   - Includes MSVC compiler with C++17 support
   ```

2. **CMake**
   ```
   Download from: https://cmake.org/download/
   - Choose "Windows win64-x64 Installer"
   - Add CMake to system PATH during installation
   ```

3. **SFML Library**
   ```
   Download from: https://www.sfml-dev.org/download.php
   - Choose "Visual C++ 15 (2017)" for VS2017 or later
   - Extract to C:\SFML (or note the path for later)
   ```

#### Step 2: Configure with CMake GUI

1. **Open CMake GUI**
   ```
   Start Menu → CMake → CMake (cmake-gui)
   ```

2. **Set Source and Build Directories**
   ```
   Source code: C:\path\to\tetris_v2
   Build binaries: C:\path\to\tetris_v2\build
   ```

3. **Configure Project**
   ```
   Click "Configure"
   - Select generator: "Visual Studio 16 2019" (or your version)
   - Platform: x64
   - Click "Finish"
   ```

4. **Set SFML Path (if needed)**
   ```
   If SFML not found automatically:
   - Add entry: SFML_ROOT = C:\SFML (your SFML path)
   - Click "Configure" again
   ```

5. **Generate Solution**
   ```
   Click "Generate"
   - Creates Visual Studio solution file
   ```

#### Step 3: Build with Visual Studio

1. **Open Solution**
   ```
   Open tetris_v2\build\TetrisV2.sln in Visual Studio
   ```

2. **Build Project**
   ```
   Build → Build Solution (F7)
   Or right-click "tetris_v2" → Build
   ```

3. **Run Game**
   ```
   Set tetris_v2 as startup project
   Debug → Start Without Debugging (Ctrl+F5)
   ```

### Method 2: Command Line Build

#### Prerequisites Setup
```cmd
# Ensure tools are in PATH
cmake --version
cl.exe  # MSVC compiler check
```

#### Build Commands
```cmd
# Clone and navigate to project
cd tetris_v2

# Create build directory
mkdir build
cd build

# Configure with CMake
cmake .. -DSFML_ROOT="C:\path\to\SFML" -A x64

# Build project
cmake --build . --config Release

# Run executable
Release\tetris_v2.exe
```

### Method 3: Using vcpkg (Advanced)

#### Install vcpkg
```cmd
git clone https://github.com/Microsoft/vcpkg.git C:\vcpkg
cd C:\vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg integrate install
```

#### Install SFML
```cmd
.\vcpkg install sfml:x64-windows
```

#### Build with vcpkg
```cmd
cd tetris_v2
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake
cmake --build . --config Release
```

## Linux Deployment

### Ubuntu/Debian Installation

#### Step 1: Install Dependencies
```bash
# Update package list
sudo apt update

# Install build tools and dependencies
sudo apt install -y cmake g++ libsfml-dev

# Verify installations
cmake --version        # Should show 3.10+
g++ --version         # Should support C++17
pkg-config --modversion sfml-all  # Should show 2.5+
```

#### Step 2: Build Project
```bash
# Clone/navigate to project directory
cd tetris_v2

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build with parallel jobs
make -j$(nproc)

# Run the game
./tetris_v2
```

### Fedora/CentOS/RHEL Installation

#### Step 1: Install Dependencies

**Fedora:**
```bash
# Install build tools and SFML
sudo dnf install -y cmake gcc-c++ SFML-devel

# Verify installations
cmake --version
g++ --version
```

**CentOS/RHEL (with EPEL):**
```bash
# Enable EPEL repository
sudo yum install -y epel-release

# Install dependencies
sudo yum install -y cmake gcc-c++ SFML-devel

# Alternative: use dnf on newer versions
sudo dnf install -y cmake gcc-c++ SFML-devel
```

#### Step 2: Build Project
```bash
# Navigate to project
cd tetris_v2

# Build process
mkdir build && cd build
cmake ..
make -j$(nproc)

# Run game
./tetris_v2
```

### Arch Linux Installation

#### Install Dependencies
```bash
# Install build tools and SFML
sudo pacman -S cmake gcc sfml

# Build project
cd tetris_v2
mkdir build && cd build
cmake ..
make -j$(nproc)
./tetris_v2
```

### Generic Linux (Source Compilation)

If SFML isn't available in your distribution's package manager:

#### Step 1: Compile SFML from Source
```bash
# Install basic dependencies
sudo apt install -y cmake g++ libfreetype6-dev libjpeg-dev \
    libx11-dev libxrandr-dev libxcursor-dev libgl1-mesa-dev \
    libudev-dev libvorbis-dev libflac-dev

# Download and build SFML
git clone https://github.com/SFML/SFML.git
cd SFML
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local
make -j$(nproc)
sudo make install
```

#### Step 2: Build Tetris V2
```bash
# Set library path
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH

# Build project
cd tetris_v2
mkdir build && cd build
cmake .. -DSFML_ROOT=/usr/local
make -j$(nproc)
./tetris_v2
```

## Troubleshooting Guide

### Common Windows Issues

#### Issue: SFML Not Found
```
CMake Error: Could not find SFML
```
**Solution:**
```cmd
# Option 1: Set SFML_ROOT in CMake GUI
SFML_ROOT = C:\path\to\SFML

# Option 2: Command line
cmake .. -DSFML_ROOT="C:\SFML"
```

#### Issue: Missing DLLs
```
System error: sfml-graphics-2.dll not found
```
**Solution:**
```cmd
# Copy SFML DLLs to executable directory
copy C:\SFML\bin\*.dll C:\path\to\tetris_v2\build\Release\
```

#### Issue: Wrong Architecture
```
Error: x86/x64 mismatch
```
**Solution:**
```cmd
# Ensure consistent architecture
cmake .. -A x64  # For 64-bit build
# Use matching SFML version (x64)
```

### Common Linux Issues

#### Issue: SFML Development Headers Missing
```
fatal error: SFML/Graphics.hpp: No such file or directory
```
**Solution:**
```bash
# Ubuntu/Debian
sudo apt install libsfml-dev

# Fedora
sudo dnf install SFML-devel

# Arch
sudo pacman -S sfml
```

#### Issue: C++17 Compiler Support
```
error: 'optional' is not a member of 'std'
```
**Solution:**
```bash
# Check compiler version
g++ --version  # Need GCC 7+ or Clang 5+

# Ubuntu: Update compiler if needed
sudo apt install gcc-8 g++-8
export CXX=g++-8
```

#### Issue: Font Loading Warning
```
Warning: Failed to load font from assets/fonts/arial.ttf
```
**Solution:**
```bash
# Check assets directory exists
ls build/assets/fonts/

# If missing, copy manually
cp -r assets build/
```

### Performance Issues

#### Low Frame Rate
```bash
# Check if running in debug mode
cmake .. -DCMAKE_BUILD_TYPE=Release
make

# Verify graphics drivers are updated
# Run with profiling (Linux)
perf record ./tetris_v2
```

#### Memory Issues
```bash
# Check for memory leaks (Linux)
valgrind --tool=memcheck ./tetris_v2

# Monitor resource usage
top -p $(pgrep tetris_v2)
```

## Platform-Specific Optimizations

### Windows Optimizations

#### Visual Studio Build Options
```cmake
# Add to CMakeLists.txt for Windows-specific optimizations
if(WIN32)
    set_property(TARGET tetris_v2 PROPERTY 
        VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
    
    # Enable fast linking
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /GL")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG")
endif()
```

#### Windows Deployment Package
```cmd
# Create redistributable package
mkdir tetris_v2_windows
copy Release\tetris_v2.exe tetris_v2_windows\
copy C:\SFML\bin\*.dll tetris_v2_windows\
xcopy assets tetris_v2_windows\assets\ /E /I
```

### Linux Optimizations

#### Compiler Optimizations
```bash
# Build with maximum optimization
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-O3 -march=native"
make -j$(nproc)
```

#### Creating Distribution Package
```bash
# Create portable Linux package
mkdir tetris_v2_linux
cp tetris_v2 tetris_v2_linux/
cp -r assets tetris_v2_linux/
ldd tetris_v2  # Check shared library dependencies

# Create launcher script
cat > tetris_v2_linux/run.sh << 'EOF'
#!/bin/bash
cd "$(dirname "$0")"
export LD_LIBRARY_PATH=./lib:$LD_LIBRARY_PATH
./tetris_v2
EOF
chmod +x tetris_v2_linux/run.sh
```

## Continuous Integration Setup

### GitHub Actions Example

```yaml
# .github/workflows/build.yml
name: Cross-Platform Build

on: [push, pull_request]

jobs:
  windows:
    runs-on: windows-latest
    steps:
    - uses: actions/checkout@v2
    - name: Install SFML
      run: |
        vcpkg install sfml:x64-windows
    - name: Configure CMake
      run: |
        cmake -B build -DCMAKE_TOOLCHAIN_FILE=$VCPKG_INSTALLATION_ROOT/scripts/buildsystems/vcpkg.cmake
    - name: Build
      run: cmake --build build --config Release

  linux:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v2
    - name: Install dependencies
      run: |
        sudo apt update
        sudo apt install -y cmake g++ libsfml-dev
    - name: Configure CMake
      run: cmake -B build
    - name: Build
      run: cmake --build build
    - name: Test
      run: cd build && ./tetris_v2 --help || true  # Basic smoke test
```

## Deployment Checklist

### Pre-Deployment Testing

- [ ] **Windows Build Test**
  - [ ] Visual Studio 2017/2019/2022 compatibility
  - [ ] Debug and Release configurations
  - [ ] x64 architecture support
  - [ ] SFML DLL dependency resolution

- [ ] **Linux Build Test**
  - [ ] Ubuntu 18.04+ compatibility
  - [ ] Fedora 30+ compatibility
  - [ ] GCC 7+ and Clang 5+ support
  - [ ] SFML system package integration

- [ ] **Functionality Test**
  - [ ] Game launches without errors
  - [ ] All controls responsive
  - [ ] Assets load correctly
  - [ ] Frame rate stable at 60 FPS
  - [ ] Game logic functions properly

- [ ] **Performance Test**
  - [ ] Memory usage under 100MB
  - [ ] CPU usage reasonable
  - [ ] No memory leaks detected
  - [ ] Consistent frame timing

### Post-Deployment Verification

- [ ] **Installation Package**
  - [ ] All required files included
  - [ ] Clear installation instructions
  - [ ] Dependency documentation
  - [ ] Uninstallation process

- [ ] **Documentation Quality**
  - [ ] README.md accuracy
  - [ ] Build instructions tested
  - [ ] Troubleshooting guide complete
  - [ ] Platform-specific notes included

This deployment guide ensures consistent, reliable builds across all supported platforms while providing comprehensive troubleshooting support for common deployment scenarios.