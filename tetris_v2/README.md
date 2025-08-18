# Tetris V2 - Cross-Platform C++ Tetris Game

A modern implementation of the classic Tetris game built with C++17 and SFML for cross-platform compatibility.

## Features

- **Classic Tetris Gameplay**: All 7 standard tetrominoes (I, O, T, S, Z, J, L) with proper rotation mechanics
- **Modern Game Features**: 
  - Ghost piece preview showing where pieces will land
  - Next piece preview
  - Progressive difficulty (increasing speed with levels)
  - Line clearing with score bonuses for multiple lines
  - Soft drop and hard drop mechanics
- **Cross-Platform**: Runs on Windows and Linux
- **Clean Architecture**: Well-structured C++ code with clear separation of concerns

## Screenshots

*Note: Screenshots would go here in a real release*

## Controls

| Key | Action |
|-----|--------|
| **A** / **Left Arrow** | Move piece left |
| **D** / **Right Arrow** | Move piece right |
| **W** / **Up Arrow** | Rotate piece clockwise |
| **S** / **Down Arrow** | Soft drop (faster fall) |
| **Space** | Hard drop (instant drop) |
| **P** | Pause/Resume game |
| **R** | Restart game |
| **ESC** | Exit to menu / Quit game |

## Dependencies

- **CMake** 3.10 or higher
- **C++17 compliant compiler** (GCC 7+, Clang 5+, MSVC 2017+)
- **SFML 2.5 or higher** (graphics, window, system modules)

## Installation

### Linux (Ubuntu/Debian)

1. **Install dependencies:**
   ```bash
   sudo apt update
   sudo apt install cmake g++ libsfml-dev
   ```

2. **Clone and build:**
   ```bash
   git clone <repository-url>
   cd tetris_v2
   mkdir build && cd build
   cmake ..
   make -j$(nproc)
   ```

3. **Run the game:**
   ```bash
   ./tetris_v2
   ```

### Linux (Fedora/CentOS/RHEL)

1. **Install dependencies:**
   ```bash
   # Fedora
   sudo dnf install cmake gcc-c++ SFML-devel
   
   # CentOS/RHEL (with EPEL)
   sudo yum install cmake gcc-c++ SFML-devel
   ```

2. **Build and run:**
   ```bash
   mkdir build && cd build
   cmake ..
   make -j$(nproc)
   ./tetris_v2
   ```

### Windows

1. **Install dependencies:**
   - Download and install [CMake](https://cmake.org/download/)
   - Install Visual Studio 2017 or later with C++ support
   - Download [SFML 2.5+](https://www.sfml-dev.org/download.php) and extract it

2. **Build with CMake GUI:**
   - Open CMake GUI
   - Set source folder to the tetris_v2 directory
   - Set build folder to tetris_v2/build
   - Click "Configure" and select your Visual Studio version
   - If SFML is not found automatically, set `SFML_ROOT` to your SFML directory
   - Click "Generate"
   - Open the generated solution file in Visual Studio
   - Build the project (F7)

3. **Build with Command Line:**
   ```cmd
   mkdir build && cd build
   cmake .. -DSFML_ROOT="C:/path/to/SFML"
   cmake --build . --config Release
   ```

4. **Run the game:**
   ```cmd
   Release/tetris_v2.exe
   ```

### Alternative: Using vcpkg (Windows/Linux)

1. **Install vcpkg and SFML:**
   ```bash
   git clone https://github.com/Microsoft/vcpkg.git
   cd vcpkg
   ./bootstrap-vcpkg.sh  # or bootstrap-vcpkg.bat on Windows
   ./vcpkg install sfml
   ```

2. **Build with vcpkg:**
   ```bash
   mkdir build && cd build
   cmake .. -DCMAKE_TOOLCHAIN_FILE=path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
   cmake --build .
   ```

## Project Structure

```
tetris_v2/
├── assets/                 # Game assets
│   ├── fonts/             # Font files
│   └── sounds/            # Sound effects (future)
├── include/TetrisV2/      # Header files
│   ├── Board.h           # Game board logic
│   ├── Constants.h       # Game constants
│   ├── Game.h            # Main game engine
│   ├── Renderer.h        # Rendering system
│   └── Tetromino.h       # Tetris piece logic
├── src/                   # Source files
│   ├── Board.cpp
│   ├── Game.cpp
│   ├── main.cpp          # Entry point
│   ├── Renderer.cpp
│   └── Tetromino.cpp
├── CMakeLists.txt         # Build configuration
└── README.md             # This file
```

## Troubleshooting

### SFML Not Found
- **Linux**: Make sure libsfml-dev is installed
- **Windows**: Set the SFML_ROOT CMake variable to your SFML installation directory
- **Both**: Ensure you have SFML 2.5 or later

### Font Loading Warning
The game will display a warning if it can't load the font file but will still run with the system default font. This is normal and doesn't affect gameplay.

### Build Errors
- Ensure you're using a C++17 compatible compiler
- Check that all dependencies are properly installed
- On Windows, make sure the correct Visual Studio version is selected in CMake

### Performance Issues
- The game is capped at 60 FPS by default
- Ensure your graphics drivers are up to date
- Try building in Release mode for better performance

## Game Rules

### Scoring
- **Single line**: 100 × level
- **Double lines**: 300 × level  
- **Triple lines**: 500 × level
- **Tetris (4 lines)**: 800 × level
- **Soft drop**: 1 point per cell
- **Hard drop**: 2 points per cell

### Level Progression
- Start at level 1
- Advance one level every 10 lines cleared
- Each level increases the falling speed
- Maximum practical level depends on player skill

## Development

### Code Style
- Modern C++17 features are used throughout
- Comprehensive Doxygen-style documentation
- Clear separation between game logic, rendering, and input
- RAII principles for resource management

### Architecture
- **Game**: Main game loop and state management
- **Board**: Grid logic, collision detection, line clearing
- **Tetromino**: Piece representation and rotation logic  
- **Renderer**: All drawing operations using SFML
- **Constants**: Centralized game configuration

## License

This project is open source. See LICENSE file for details.

## Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues for bugs and feature requests.

## Future Enhancements

- Sound effects and background music
- High score persistence
- Different game modes (Marathon, Sprint, etc.)
- Improved graphics and animations
- Online multiplayer support
- Mobile platform support