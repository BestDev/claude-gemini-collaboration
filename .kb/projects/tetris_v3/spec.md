# tetris_v3 작업 명세서

## 1. 목표 (Goal)
콘솔 환경에서 동작하는 크로스 플랫폼(Windows, Linux) 테트리스 게임을 제작한다.

## 2. 요구사항 (Requirements)
- C++ 언어를 사용하여 구현한다.
- CMake를 사용하여 크로스 플랫폼 빌드 시스템을 구성한다.
- 키보드 화살표 키로 블록을 조작할 수 있어야 한다. (왼쪽, 오른쪽, 아래, 회전)
- 블록이 한 줄 채워지면 해당 줄이 사라지고 점수가 올라간다.
- 블록이 화면 상단에 닿으면 게임이 종료된다.
- 기본적인 게임 정보(점수, 다음 블록 등)가 화면에 표시되어야 한다.

## 3. 기술 스택 (Tech Stack)
- **언어**: C++17
- **빌드 시스템**: CMake 3.10 이상

## 4. 구현 가이드 (Implementation Guide)

### 4.1. 폴더 및 파일 구조
아래 구조에 맞게 모든 디렉토리와 빈 파일을 먼저 생성해주세요.
```
tetris_v3/
├── CMakeLists.txt
├── README.md
├── include/
│   ├── Board.h
│   ├── Game.h
│   ├── Input.h
│   ├── Renderer.h
│   └── Tetromino.h
└── src/
    ├── Board.cpp
    ├── Game.cpp
    ├── Input.cpp
    ├── main.cpp
    ├── Renderer.cpp
    └── Tetromino.cpp
```

### 4.2. 플랫폼별 코드 처리
- 화면 출력(`Renderer.cpp`)과 키보드 입력(`Input.cpp`)은 플랫폼에 따라 다른 API를 사용해야 합니다.
- C++ 전처리기 지시문 (`#ifdef _WIN32` / `#else` / `#endif`)을 사용하여 각 OS에 맞는 코드를 작성해주세요.
  - **Windows**: `conio.h`의 `_kbhit()`, `_getch()` 및 Windows API (예: `SetConsoleCursorPosition`) 사용
  - **Linux**: `termios.h` 및 `unistd.h` 등을 사용하여 non-blocking 입력 처리 및 ANSI 이스케이프 시퀀스를 이용한 화면 제어

### 4.3. 클래스별 역할
- **`Tetromino`**: 블록의 형태, 회전, 위치 데이터 관리
- **`Board`**: 게임 판의 상태, 쌓인 블록, 줄 제거 로직 관리
- **`Renderer`**: `Board`와 `Tetromino`의 현재 상태를 받아 콘솔에 그리는 역할
- **`Input`**: 키보드 입력을 받아 게임 내 동작으로 변환하는 역할
- **`Game`**: 모든 요소를 총괄하며 게임의 메인 루프, 점수, 레벨, 게임 오버 로직 관리
- **`main`**: `Game` 객체를 생성하고 게임 시작

### 4.4. `CMakeLists.txt` 작성
- `tetris_v3` 프로젝트를 정의하고 C++17 표준을 사용하도록 설정해주세요.
- `src` 폴더의 모든 `.cpp` 파일을 컴파일하고, `include` 폴더를 헤더 검색 경로에 추가해주세요.
- 최종적으로 `tetris_v3`라는 이름의 실행 파일이 생성되도록 설정해주세요.

### 4.5. `README.md` 작성
- `COLLABORATION-RULES.md`에 명시된 형식에 따라 작성해주세요.
- **빌드 방법** 섹션에 Linux와 Windows 각각의 빌드 절차를 명확히 기재해야 합니다. (예: `mkdir build && cd build && cmake .. && make`)

## 5. 완료 조건 (Completion Criteria)
- `tetris_v3` 폴더 내에서 `CMake`와 각 플랫폼의 네이티브 빌드 도구(make, MSBuild 등)를 통해 컴파일이 성공해야 한다.
- 생성된 실행 파일이 Windows와 Linux에서 모두 정상적으로 실행되어 테트리스 게임을 플레이할 수 있어야 한다.
- 모든 요구사항이 구현되어야 한다.
