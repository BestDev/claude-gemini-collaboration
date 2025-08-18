# Tetris V2 Architecture Design Request

## Project Context
- **Purpose**: Test comprehensive collaboration rules between Claude and Gemini
- **Target**: Reference example for other users/sessions
- **Requirements**: Cross-platform C++ tetris game (Windows + Linux)

## Technical Requirements
1. **Language**: C++17 standard
2. **Platform Support**: Windows and Linux
3. **Game Features**: 
   - Classic tetris gameplay
   - Block rotation and movement
   - Line clearing mechanics
   - Score tracking
   - Game over detection

## Architecture Design Needed
Please provide detailed architecture design including:

1. **Technology Stack Selection**
   - Graphics library recommendations (SDL2, SFML, etc.)
   - Build system (CMake, Makefile)
   - Cross-platform considerations

2. **Project Structure**
   - Standard C++ folder organization
   - Header/source file organization
   - Asset management

3. **Core Classes/Components**
   - Game engine structure
   - Tetris-specific classes (Board, Piece, Game)
   - Input handling
   - Rendering system

4. **Build Configuration**
   - CMakeLists.txt structure
   - Platform-specific build instructions

5. **Documentation Requirements**
   - Code documentation level
   - README structure
   - Build/installation guide

Please create a comprehensive specification in `.kb/projects/tetris_v2/spec.md` that Claude can follow for implementation.