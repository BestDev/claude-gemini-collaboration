# Tetris V2: System Architecture Documentation

## Architecture Overview

Tetris V2 implements a clean, modular architecture that separates concerns across distinct system layers. The design follows modern C++ practices with clear interfaces, RAII resource management, and cross-platform compatibility.

### High-Level System Architecture

```mermaid
graph TB
    subgraph "Application Layer"
        Main[main.cpp<br/>Entry Point]
        Game[Game Class<br/>Main Game Loop]
    end
    
    subgraph "Game Logic Layer"
        Board[Board<br/>Grid Management]
        Tetromino[Tetromino<br/>Piece Logic]
        Constants[Constants<br/>Configuration]
    end
    
    subgraph "Presentation Layer"
        Renderer[Renderer<br/>Drawing System]
    end
    
    subgraph "External Dependencies"
        SFML[SFML Library<br/>Graphics/Window/Input]
        CMake[CMake<br/>Build System]
    end
    
    Main --> Game
    Game --> Board
    Game --> Tetromino
    Game --> Renderer
    Board --> Constants
    Tetromino --> Constants
    Renderer --> SFML
    Game --> SFML
    
    style Game fill:#e1f5fe
    style Board fill:#f3e5f5
    style Tetromino fill:#f3e5f5
    style Renderer fill:#e8f5e8
    style SFML fill:#fff3e0
```

## Core Class Architecture

### Class Relationship Diagram

```mermaid
classDiagram
    class Game {
        -sf::RenderWindow m_window
        -Board m_board
        -Renderer m_renderer
        -optional~Tetromino~ m_currentPiece
        -optional~Tetromino~ m_nextPiece
        -GameState m_gameState
        -int m_score, m_level, m_linesCleared
        -sf::Clock m_clock, m_dropClock
        +Game()
        +run() void
        -processInput() void
        -update(float deltaTime) void
        -render() void
        -spawnNewPiece() void
        -tryMovePiece(int dx, int dy) bool
        -tryRotatePiece() bool
        -hardDrop() int
        -placePieceAndClear() void
    }
    
    class Board {
        -vector~vector~sf::Color~~ m_grid
        -int m_width, m_height
        +Board()
        +isCollision(const Tetromino&) bool
        +placePiece(const Tetromino&) void
        +clearLines() int
        +getGrid() const vector~vector~sf::Color~~&
        +isEmpty(int x, int y) bool
        +isValidPosition(int x, int y) bool
    }
    
    class Tetromino {
        -TetrominoType m_type
        -sf::Vector2i m_position
        -vector~sf::Vector2i~ m_blocks
        -sf::Color m_color
        -int m_rotation
        +Tetromino(TetrominoType type)
        +rotate() void
        +move(int dx, int dy) void
        +getPosition() sf::Vector2i
        +getBlocks() const vector~sf::Vector2i~&
        +getColor() sf::Color
        +setPosition(sf::Vector2i pos) void
    }
    
    class Renderer {
        -sf::RenderWindow& m_window
        -sf::Font m_font
        -sf::Text m_text
        +Renderer(sf::RenderWindow& window)
        +drawBoard(const Board&) void
        +drawTetromino(const Tetromino&) void
        +drawGhostPiece(const Tetromino&, int ghostY) void
        +drawNextPiece(const Tetromino&) void
        +drawUI(int score, int level, int lines) void
        +clear() void
        +display() void
    }
    
    class Constants {
        <<enumeration>>
        +BOARD_WIDTH: const int
        +BOARD_HEIGHT: const int
        +BLOCK_SIZE: const int
        +WINDOW_WIDTH: const int
        +WINDOW_HEIGHT: const int
        +FRAME_RATE_LIMIT: const int
        +TetrominoType: enum
        +GameState: enum
        +TETROMINO_COLORS: const sf::Color[]
    }
    
    Game "1" --> "1" Board : owns
    Game "1" --> "0..1" Tetromino : current piece
    Game "1" --> "0..1" Tetromino : next piece
    Game "1" --> "1" Renderer : uses
    Board --> Constants : uses
    Tetromino --> Constants : uses
    Renderer --> Constants : uses
```

## Game State Management

### State Transition Diagram

```mermaid
stateDiagram-v2
    [*] --> Menu : Application Start
    
    Menu --> Playing : Start Game
    Menu --> [*] : Exit Application
    
    Playing --> Paused : P Key Pressed
    Playing --> GameOver : Collision at Spawn
    Playing --> Playing : Normal Gameplay
    
    Paused --> Playing : P Key Pressed
    Paused --> Menu : ESC Key
    
    GameOver --> Menu : Any Key
    GameOver --> Playing : R Key (Restart)
    
    state Playing {
        [*] --> PieceSpawning
        PieceSpawning --> PieceFalling : New Piece Created
        PieceFalling --> PieceMoving : User Input
        PieceMoving --> PieceFalling : Move Complete
        PieceFalling --> PieceLanded : Collision Detected
        PieceLanded --> LineClearing : Piece Placed
        LineClearing --> ScoreUpdate : Lines Cleared
        ScoreUpdate --> LevelCheck : Score Updated
        LevelCheck --> PieceSpawning : Check Complete
        
        PieceFalling --> PieceFalling : Time-based Drop
        PieceMoving --> PieceMoving : Continuous Input
    }
```

## Game Loop Architecture

### Main Game Loop Flow

```mermaid
flowchart TD
    Start([Game Start]) --> Init[Initialize Systems]
    Init --> GameLoop{Main Game Loop}
    
    GameLoop --> ProcessInput[Process Input Events]
    ProcessInput --> UpdateLogic[Update Game Logic]
    UpdateLogic --> Render[Render Frame]
    Render --> FrameLimit[Apply Frame Rate Limit]
    FrameLimit --> WindowOpen{Window Still Open?}
    
    WindowOpen -->|Yes| GameLoop
    WindowOpen -->|No| Cleanup[Cleanup Resources]
    Cleanup --> End([Application End])
    
    subgraph "Input Processing"
        ProcessInput --> KeyEvents[Handle Key Events]
        KeyEvents --> MovePiece[Move/Rotate Piece]
        MovePiece --> GameStateChange[Handle State Changes]
    end
    
    subgraph "Logic Update"
        UpdateLogic --> DropTimer[Check Drop Timer]
        DropTimer --> PieceDrop[Auto-Drop Piece]
        PieceDrop --> CollisionCheck[Check Collisions]
        CollisionCheck --> LineClear[Clear Completed Lines]
        LineClear --> ScoreCalc[Calculate Score]
        ScoreCalc --> LevelUpdate[Update Level]
    end
    
    subgraph "Rendering"
        Render --> ClearScreen[Clear Screen]
        ClearScreen --> DrawBoard[Draw Game Board]
        DrawBoard --> DrawPiece[Draw Current Piece]
        DrawPiece --> DrawGhost[Draw Ghost Piece]
        DrawGhost --> DrawUI[Draw UI Elements]
        DrawUI --> DisplayFrame[Display Frame]
    end
    
    style GameLoop fill:#e1f5fe
    style ProcessInput fill:#f3e5f5
    style UpdateLogic fill:#e8f5e8
    style Render fill:#fff3e0
```

## Tetromino System Architecture

### Piece Type and Rotation System

```mermaid
graph LR
    subgraph "Tetromino Types"
        I[I-Piece<br/>Cyan<br/>Line]
        O[O-Piece<br/>Yellow<br/>Square]
        T[T-Piece<br/>Magenta<br/>T-Shape]
        S[S-Piece<br/>Green<br/>S-Shape]
        Z[Z-Piece<br/>Red<br/>Z-Shape]
        J[J-Piece<br/>Blue<br/>J-Shape]
        L[L-Piece<br/>Orange<br/>L-Shape]
    end
    
    subgraph "Rotation System"
        R0[Rotation 0°<br/>Base Position]
        R90[Rotation 90°<br/>Clockwise]
        R180[Rotation 180°<br/>Inverted]
        R270[Rotation 270°<br/>Counter-Clockwise]
        
        R0 --> R90
        R90 --> R180
        R180 --> R270
        R270 --> R0
    end
    
    subgraph "Wall Kick System"
        WK[Wall Kick Attempts]
        WK1[Try Original Position]
        WK2[Try Left Offset]
        WK3[Try Right Offset]
        WK4[Try Up Offset]
        
        WK --> WK1
        WK1 -->|Fail| WK2
        WK2 -->|Fail| WK3
        WK3 -->|Fail| WK4
        WK4 -->|Fail| Cancel[Cancel Rotation]
    end
    
    I --> R0
    O --> R0
    T --> R0
    S --> R0
    Z --> R0
    J --> R0
    L --> R0
```

## Collision Detection System

### Collision Detection Flow

```mermaid
flowchart TD
    Start([Collision Check Request]) --> GetBlocks[Get Tetromino Block Positions]
    GetBlocks --> ForEachBlock{For Each Block}
    
    ForEachBlock --> CalcWorldPos[Calculate World Position]
    CalcWorldPos --> BoundaryCheck{Within Board Boundaries?}
    
    BoundaryCheck -->|No| Collision[Return Collision]
    BoundaryCheck -->|Yes| OccupiedCheck{Grid Cell Occupied?}
    
    OccupiedCheck -->|Yes| Collision
    OccupiedCheck -->|No| NextBlock[Next Block]
    
    NextBlock --> MoreBlocks{More Blocks?}
    MoreBlocks -->|Yes| ForEachBlock
    MoreBlocks -->|No| NoCollision[Return No Collision]
    
    Collision --> Return([Return Result])
    NoCollision --> Return
    
    style Collision fill:#ffebee
    style NoCollision fill:#e8f5e8
    style BoundaryCheck fill:#fff3e0
    style OccupiedCheck fill:#f3e5f5
```

## Rendering Pipeline

### Frame Rendering Architecture

```mermaid
sequenceDiagram
    participant Game
    participant Renderer
    participant SFML
    participant Display
    
    Game->>Renderer: render()
    Renderer->>SFML: clear()
    
    Note over Renderer: Render Background
    Renderer->>SFML: Draw Background
    
    Note over Renderer: Render Game Board
    Renderer->>SFML: Draw Grid Lines
    Renderer->>SFML: Draw Landed Pieces
    
    Note over Renderer: Render Active Pieces
    Renderer->>SFML: Draw Ghost Piece
    Renderer->>SFML: Draw Current Piece
    
    Note over Renderer: Render Next Piece Preview
    Renderer->>SFML: Draw Next Piece
    
    Note over Renderer: Render UI Elements
    Renderer->>SFML: Draw Score Text
    Renderer->>SFML: Draw Level Text
    Renderer->>SFML: Draw Lines Text
    
    Note over Renderer: Render Game State
    alt Game Over
        Renderer->>SFML: Draw Game Over Screen
    else Paused
        Renderer->>SFML: Draw Pause Overlay
    end
    
    Renderer->>SFML: display()
    SFML->>Display: Present Frame
```

## Memory Management Architecture

### Resource Lifecycle Management

```mermaid
graph TD
    subgraph "Application Lifecycle"
        AppStart[Application Start] --> InitResources[Initialize Resources]
        InitResources --> MainLoop[Main Game Loop]
        MainLoop --> Cleanup[Cleanup Resources]
        Cleanup --> AppEnd[Application End]
    end
    
    subgraph "RAII Resource Management"
        SFMLWindow[sf::RenderWindow<br/>Auto-managed]
        SFMLFont[sf::Font<br/>Auto-managed]
        SFMLClock[sf::Clock<br/>Auto-managed]
        GameBoard[Board Grid<br/>std::vector managed]
        TetrominoData[Tetromino Blocks<br/>std::vector managed]
    end
    
    subgraph "Memory Safety Features"
        SmartPtrs[Smart Pointers<br/>std::optional]
        RAII[RAII Principles<br/>Automatic Cleanup]
        NoRawPtrs[No Raw Pointers<br/>Stack Allocation]
        ContainerSafety[STL Containers<br/>Bounds Checking]
    end
    
    InitResources --> SFMLWindow
    InitResources --> SFMLFont
    InitResources --> GameBoard
    MainLoop --> TetrominoData
    
    SFMLWindow --> RAII
    GameBoard --> ContainerSafety
    TetrominoData --> SmartPtrs
    
    style RAII fill:#e8f5e8
    style SmartPtrs fill:#e1f5fe
    style ContainerSafety fill:#f3e5f5
```

## Cross-Platform Architecture

### Platform Abstraction Strategy

```mermaid
graph TB
    subgraph "Application Code"
        GameLogic[Game Logic<br/>Platform Independent]
        Rendering[Rendering Code<br/>SFML Abstracted]
        Input[Input Handling<br/>SFML Abstracted]
    end
    
    subgraph "SFML Abstraction Layer"
        SFMLGraphics[SFML Graphics<br/>Cross-Platform]
        SFMLWindow[SFML Window<br/>Cross-Platform]
        SFMLSystem[SFML System<br/>Cross-Platform]
    end
    
    subgraph "Platform Specific"
        WindowsAPI[Windows API<br/>Win32/DirectX]
        LinuxAPI[Linux API<br/>X11/OpenGL]
    end
    
    subgraph "Build System"
        CMake[CMake<br/>Cross-Platform Build]
        WindowsBuild[Visual Studio<br/>Windows Build]
        LinuxBuild[Make/Ninja<br/>Linux Build]
    end
    
    GameLogic --> SFMLGraphics
    Rendering --> SFMLGraphics
    Input --> SFMLWindow
    
    SFMLGraphics --> WindowsAPI
    SFMLGraphics --> LinuxAPI
    SFMLWindow --> WindowsAPI
    SFMLWindow --> LinuxAPI
    
    CMake --> WindowsBuild
    CMake --> LinuxBuild
    
    style SFMLGraphics fill:#e1f5fe
    style CMake fill:#e8f5e8
    style GameLogic fill:#f3e5f5
```

## Performance Optimization Architecture

### Frame Rate and Performance Management

```mermaid
graph LR
    subgraph "Performance Monitoring"
        FrameTimer[Frame Timer<br/>sf::Clock]
        FPSLimit[FPS Limiter<br/>60 FPS Target]
        DeltaTime[Delta Time<br/>Frame-Independent Logic]
    end
    
    subgraph "Optimization Strategies"
        BatchRender[Batch Rendering<br/>Minimize Draw Calls]
        MemoryPool[Object Reuse<br/>Tetromino Instances]
        EarlyExit[Early Exit<br/>Collision Detection]
    end
    
    subgraph "Resource Efficiency"
        TextureCache[Font Loading<br/>One-Time Initialization]
        StackAlloc[Stack Allocation<br/>Prefer Stack Objects]
        ContainerReuse[Container Reuse<br/>Avoid Allocations]
    end
    
    FrameTimer --> DeltaTime
    DeltaTime --> BatchRender
    FPSLimit --> BatchRender
    
    EarlyExit --> MemoryPool
    BatchRender --> TextureCache
    MemoryPool --> StackAlloc
    
    style DeltaTime fill:#e1f5fe
    style BatchRender fill:#e8f5e8
    style EarlyExit fill:#f3e5f5
```

## Architecture Principles

### Design Philosophy

1. **Separation of Concerns**: Each class has a single, well-defined responsibility
2. **Encapsulation**: Internal state is protected with clear public interfaces
3. **Resource Safety**: RAII principles ensure automatic resource management
4. **Performance**: Optimized for 60 FPS gameplay with minimal allocations
5. **Maintainability**: Clear code structure enables easy modification and extension
6. **Cross-Platform**: Single codebase works across Windows and Linux

### Architectural Benefits

- **Modularity**: Components can be modified independently
- **Testability**: Clear interfaces enable unit testing
- **Extensibility**: New features can be added without major refactoring
- **Performance**: Optimized data structures and algorithms
- **Reliability**: Robust error handling and resource management
- **Portability**: Platform-independent core with abstracted dependencies

This architecture provides a solid foundation for a production-quality Tetris implementation while serving as an excellent reference for modern C++ game development practices and AI collaboration methodologies.