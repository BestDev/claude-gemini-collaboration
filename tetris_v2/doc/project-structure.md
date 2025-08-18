# Tetris V2: Project Structure Documentation

## Complete Project Structure Overview

This document provides a comprehensive visual representation of the Tetris V2 project structure, file organization, and relationships between different components.

### Root Directory Structure

```
tetris_v2/
├── 📁 assets/                     # Game assets and resources
│   ├── 📁 fonts/                 # Font files for text rendering
│   │   ├── 📄 README.md          # Font usage documentation
│   │   └── 📄 arial.ttf          # Primary game font (if available)
│   └── 📁 sounds/                # Audio files (future expansion)
│       ├── 📄 README.md          # Sound documentation
│       ├── 🔊 clear.wav          # Line clear sound effect (planned)
│       └── 🔊 gameover.wav       # Game over sound effect (planned)
├── 📁 include/TetrisV2/          # Public header files
│   ├── 📄 Board.h               # Game board interface
│   ├── 📄 Constants.h           # Game configuration constants
│   ├── 📄 Game.h                # Main game engine interface
│   ├── 📄 Renderer.h            # Rendering system interface
│   └── 📄 Tetromino.h           # Tetris piece interface
├── 📁 src/                       # Implementation source files
│   ├── 📄 Board.cpp             # Game board implementation
│   ├── 📄 Game.cpp              # Main game engine implementation
│   ├── 📄 main.cpp              # Application entry point
│   ├── 📄 Renderer.cpp          # Rendering system implementation
│   └── 📄 Tetromino.cpp         # Tetris piece implementation
├── 📁 build/                     # CMake build directory (generated)
│   ├── 📁 Debug/                # Debug build artifacts
│   ├── 📁 Release/              # Release build artifacts
│   ├── 📁 assets/               # Copied asset files
│   └── ⚙️ CMakeCache.txt        # CMake configuration cache
├── 📄 CMakeLists.txt            # Cross-platform build configuration
├── 📄 README.md                 # User documentation and setup guide
├── 📄 .gitignore               # Git ignore patterns
└── 📄 LICENSE                   # Project license (if applicable)
```

### Knowledge Base Integration

```
.kb/projects/tetris_v2/           # Project knowledge base
├── 📄 project-overview.md       # Comprehensive project description
├── 📄 spec.md                   # Technical implementation specification
├── 📄 architecture.md           # System architecture with diagrams
├── 📄 deployment-guide.md       # Platform deployment instructions
├── 📄 development-guide.md      # Developer contribution guide
├── 📄 project-structure.md      # This document
├── 📁 adr/                      # Architecture Decision Records
│   └── 📄 ADR-001-sfml-choice.md
├── 📁 design/                   # Design documents and diagrams
│   ├── 📄 class-diagrams.md    # UML class relationships
│   ├── 📄 game-flow.md         # Game state flow documentation
│   └── 📄 visual-design.md     # UI/UX design specifications
└── 📁 sessions/                 # Development session logs
    └── 📁 2024-08-18-initial-implementation/
        ├── 📄 session-log.md
        └── 📄 collaboration-notes.md
```

## File Dependencies and Relationships

### Header Dependency Graph

```mermaid
graph TD
    subgraph "Application Layer"
        Main[main.cpp]
        Game[Game.h/cpp]
    end
    
    subgraph "Game Logic Layer"
        Board[Board.h/cpp]
        Tetromino[Tetromino.h/cpp]
        Constants[Constants.h]
    end
    
    subgraph "Presentation Layer"
        Renderer[Renderer.h/cpp]
    end
    
    subgraph "External Dependencies"
        SFML[SFML Headers]
        STL[STL Headers]
    end
    
    Main --> Game
    Game --> Board
    Game --> Tetromino
    Game --> Renderer
    Game --> Constants
    Board --> Constants
    Tetromino --> Constants
    Renderer --> Constants
    
    Game --> SFML
    Renderer --> SFML
    Board --> STL
    Tetromino --> STL
    
    style Constants fill:#fffacd
    style SFML fill:#e6f3ff
    style STL fill:#f0f8ff
```

### Include Hierarchy Visualization

```
Constants.h (Base Level)
├── Used by: Board.h
├── Used by: Tetromino.h
├── Used by: Renderer.h
└── Used by: Game.h

Board.h (Game Logic)
├── Includes: Constants.h
├── Includes: <SFML/Graphics.hpp>
├── Includes: <vector>
└── Used by: Game.h

Tetromino.h (Game Logic)
├── Includes: Constants.h
├── Includes: <SFML/Graphics.hpp>
├── Includes: <vector>
└── Used by: Game.h

Renderer.h (Presentation)
├── Includes: Constants.h
├── Includes: Board.h
├── Includes: Tetromino.h
├── Includes: <SFML/Graphics.hpp>
└── Used by: Game.h

Game.h (Application)
├── Includes: Constants.h
├── Includes: Board.h
├── Includes: Tetromino.h
├── Includes: Renderer.h
├── Includes: <SFML/Graphics.hpp>
├── Includes: <random>
├── Includes: <optional>
└── Used by: main.cpp
```

## Component Size and Complexity Analysis

### Lines of Code Distribution

```mermaid
pie title Source Code Distribution (Approximate)
    "Game.cpp (Main Logic)" : 350
    "Board.cpp (Grid Logic)" : 200
    "Tetromino.cpp (Piece Logic)" : 180
    "Renderer.cpp (Drawing)" : 250
    "main.cpp (Entry Point)" : 20
    "Headers (Documentation)" : 300
```

### Component Responsibility Matrix

| Component | Primary Responsibility | Secondary Responsibility | Complexity |
|-----------|----------------------|-------------------------|------------|
| **main.cpp** | Application bootstrap | Exception handling | Low |
| **Game.h/cpp** | Game loop coordination | State management | High |
| **Board.h/cpp** | Grid state management | Collision detection | Medium |
| **Tetromino.h/cpp** | Piece representation | Rotation logic | Medium |
| **Renderer.h/cpp** | Graphics rendering | UI presentation | Medium |
| **Constants.h** | Configuration values | Type definitions | Low |

## Build System Architecture

### CMake Build Flow

```mermaid
flowchart TD
    CMakeLists[CMakeLists.txt] --> Configure[CMake Configure]
    Configure --> FindSFML[Find SFML Package]
    FindSFML --> IncludeDirs[Set Include Directories]
    IncludeDirs --> CollectSources[Collect Source Files]
    CollectSources --> CreateTarget[Create Executable Target]
    CreateTarget --> LinkLibraries[Link SFML Libraries]
    LinkLibraries --> CopyAssets[Copy Assets to Build Dir]
    CopyAssets --> GenerateBuild[Generate Build Files]
    
    subgraph "Platform Specific"
        GenerateBuild --> WindowsBuild[Visual Studio Solution]
        GenerateBuild --> LinuxBuild[Makefiles]
    end
    
    WindowsBuild --> Compile[Compile & Link]
    LinuxBuild --> Compile
    Compile --> Executable[tetris_v2 Executable]
    
    style CMakeLists fill:#e1f5fe
    style FindSFML fill:#f3e5f5
    style Executable fill:#e8f5e8
```

### Build Artifact Organization

```
build/                            # CMake build directory
├── 📁 CMakeFiles/               # CMake internal files
│   ├── 📁 3.22.1/              # CMake version specific
│   ├── 📁 tetris_v2.dir/       # Target specific build files
│   └── ⚙️ Makefile              # Generated Makefile (Linux)
├── 📁 Debug/                    # Debug configuration (Windows)
│   ├── 🎮 tetris_v2.exe       # Debug executable
│   └── 📄 tetris_v2.pdb       # Debug symbols
├── 📁 Release/                  # Release configuration (Windows)
│   ├── 🎮 tetris_v2.exe       # Optimized executable
│   └── 📄 *.dll               # SFML runtime libraries
├── 📁 assets/                   # Copied game assets
│   ├── 📁 fonts/
│   └── 📁 sounds/
├── 🎮 tetris_v2                # Linux executable
├── ⚙️ CMakeCache.txt           # CMake configuration cache
├── ⚙️ Makefile                 # Top-level Makefile (Linux)
└── 🔧 compile_commands.json    # Compilation database
```

## Asset Management Structure

### Asset Organization Strategy

```mermaid
graph TB
    subgraph "Source Assets"
        SourceFonts[assets/fonts/]
        SourceSounds[assets/sounds/]
    end
    
    subgraph "Build Process"
        CMakeCopy[CMake File Copy]
        AssetValidation[Asset Validation]
    end
    
    subgraph "Runtime Assets"
        BuildFonts[build/assets/fonts/]
        BuildSounds[build/assets/sounds/]
    end
    
    subgraph "Asset Loading"
        FontLoader[Font Loader]
        SoundLoader[Sound Loader]
        AssetManager[Asset Manager]
    end
    
    SourceFonts --> CMakeCopy
    SourceSounds --> CMakeCopy
    CMakeCopy --> AssetValidation
    AssetValidation --> BuildFonts
    AssetValidation --> BuildSounds
    
    BuildFonts --> FontLoader
    BuildSounds --> SoundLoader
    FontLoader --> AssetManager
    SoundLoader --> AssetManager
    
    style SourceFonts fill:#fff3cd
    style BuildFonts fill:#d4edda
    style AssetManager fill:#e1f5fe
```

### Asset Loading Strategy

```cpp
// Asset path resolution strategy
namespace TetrisV2 {
    class AssetManager {
    public:
        static std::string getAssetPath(const std::string& category, 
                                       const std::string& filename) {
            // Check relative to executable first
            std::string relativePath = "assets/" + category + "/" + filename;
            if (std::filesystem::exists(relativePath)) {
                return relativePath;
            }
            
            // Check system paths as fallback
            std::vector<std::string> systemPaths = {
                "/usr/share/tetris_v2/assets/" + category + "/",
                "/usr/local/share/tetris_v2/assets/" + category + "/",
                "C:/Program Files/TetrisV2/assets/" + category + "/"
            };
            
            for (const auto& path : systemPaths) {
                std::string fullPath = path + filename;
                if (std::filesystem::exists(fullPath)) {
                    return fullPath;
                }
            }
            
            return "";  // Asset not found
        }
    };
}
```

## Cross-Platform File Structure

### Platform-Specific Considerations

```mermaid
graph TB
    subgraph "Windows Structure"
        WinExe[tetris_v2.exe]
        WinDLLs[SFML DLLs]
        WinAssets[assets/]
        WinConfig[User Config<br/>%APPDATA%/TetrisV2/]
    end
    
    subgraph "Linux Structure"
        LinuxExe[tetris_v2]
        LinuxLibs[System Libraries<br/>/usr/lib/]
        LinuxAssets[assets/]
        LinuxConfig[User Config<br/>~/.config/tetris_v2/]
    end
    
    subgraph "Common Elements"
        CommonAssets[Game Assets]
        CommonConfig[Configuration Format]
        CommonSave[Save Game Format]
    end
    
    WinAssets --> CommonAssets
    LinuxAssets --> CommonAssets
    WinConfig --> CommonConfig
    LinuxConfig --> CommonConfig
    
    style WinExe fill:#e3f2fd
    style LinuxExe fill:#f1f8e9
    style CommonAssets fill:#fff3e0
```

## Documentation Structure Integration

### Documentation Ecosystem

```mermaid
mindmap
  root((Tetris V2 Documentation))
    User Documentation
      README.md
      Quick Start Guide
      Installation Instructions
      Game Controls
      Troubleshooting
    Developer Documentation
      Architecture Guide
      API Reference
      Coding Standards
      Contribution Guidelines
      Build System Guide
    Project Documentation
      Project Overview
      Technical Specifications
      Deployment Guide
      Development Guide
      Project Structure
    AI Collaboration Documentation
      Collaboration Protocols
      Session Logs
      Decision Records
      Knowledge Transfer
```

### Documentation Cross-References

| Document | References | Referenced By |
|----------|------------|---------------|
| **project-overview.md** | spec.md, architecture.md | All other docs |
| **spec.md** | Constants.h, CMakeLists.txt | development-guide.md |
| **architecture.md** | All header files | deployment-guide.md |
| **deployment-guide.md** | CMakeLists.txt, README.md | development-guide.md |
| **development-guide.md** | All source files | Future contributors |
| **project-structure.md** | All project files | New team members |

## Version Control Structure

### Git Repository Organization

```
.git/                             # Git repository metadata
├── 📁 hooks/                    # Git hooks for automation
├── 📁 objects/                  # Git object database
├── 📁 refs/                     # Git references
└── ⚙️ config                    # Repository configuration

.gitignore                        # Git ignore patterns
├── build/                       # Ignore build artifacts
├── *.user                       # Ignore IDE user files
├── .vs/                         # Ignore Visual Studio temp files
├── CMakeCache.txt               # Ignore CMake cache
└── *.exe                        # Ignore executables

README.md                         # Primary project documentation
├── Project description
├── Build instructions
├── Usage examples
└── License information
```

### Branch Strategy Visualization

```mermaid
gitgraph
    commit id: "Initial commit"
    commit id: "Add CMake config"
    commit id: "Implement basic structure"
    
    branch feature/game-logic
    checkout feature/game-logic
    commit id: "Add Board class"
    commit id: "Add Tetromino class"
    commit id: "Implement collision detection"
    
    checkout main
    merge feature/game-logic
    commit id: "Merge game logic"
    
    branch feature/rendering
    checkout feature/rendering
    commit id: "Add Renderer class"
    commit id: "Implement SFML integration"
    
    checkout main
    merge feature/rendering
    commit id: "Merge rendering system"
    
    commit id: "Add documentation"
    commit id: "Release v1.0"
```

## Memory Layout and Performance Structure

### Runtime Memory Organization

```mermaid
graph TB
    subgraph "Stack Memory"
        GameInstance[Game Instance]
        LocalVariables[Local Variables]
        FunctionCalls[Function Call Stack]
    end
    
    subgraph "Heap Memory"
        SFMLObjects[SFML Objects]
        STLContainers[STL Containers]
        AssetData[Loaded Assets]
    end
    
    subgraph "Static Memory"
        Constants[Constant Data]
        GlobalState[Global State]
        ClassDefinitions[Class Definitions]
    end
    
    GameInstance --> SFMLObjects
    LocalVariables --> STLContainers
    Constants --> ClassDefinitions
    
    style GameInstance fill:#e1f5fe
    style SFMLObjects fill:#f3e5f5
    style Constants fill:#e8f5e8
```

This comprehensive project structure documentation provides a complete visual and textual representation of how the Tetris V2 project is organized, making it easy for new developers, AI systems, and project stakeholders to understand the codebase organization and architectural decisions.