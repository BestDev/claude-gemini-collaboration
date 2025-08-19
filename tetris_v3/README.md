# Tetris v3

현대적인 C++17로 구현된 클래식 테트리스 게임입니다.

## 설명 (Description)

C++17로 개발된 크로스 플랫폼 테트리스 게임으로, Windows와 Linux에서 실행 가능합니다.

## 주요 기능 (Features)

- 표준 테트리스 7가지 조각 (I, O, T, S, Z, J, L)
- 자동 낙하 및 회전 시스템 포함
- 라인 클리어 시 중력 시스템
- 조각 보관 기능
- 유령 조각 미리보기
- 레벨 시스템
- 점수 시스템 (라인별 보너스)

## 게임 조작법 (Controls)

- **←/→**: 조각 좌우 이동
- **↓**: 조각 빠른 낙하
- **↑**: 조각 회전
- **Space**: 조각 즉시 낙하
- **C**: 조각 보관
- **ESC**: 게임 종료
- **P**: 일시정지

## 빌드 방법 (Build Instructions)

### Linux에서 빌드

```bash
mkdir build
cd build
cmake ..
make
```

### Windows에서 빌드

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

또는 Visual Studio를 사용할 경우:

```bash
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022"
# 생성된 .sln 파일을 Visual Studio로 열어 빌드
```

## 사용법 (Usage)

빌드 완료 후 실행:

```bash
# Linux
./tetris_v3

# Windows
tetris_v3.exe
```

## 프로젝트 폴더 구조

```
tetris_v3/
├── CMakeLists.txt          # CMake 빌드 설정
├── README.md               # 프로젝트 설명
├── include/                # 헤더 파일
│   ├── Board.h             # 게임 보드 클래스
│   ├── Game.h              # 메인 게임 클래스
│   ├── Input.h             # 입력 처리 클래스
│   ├── Renderer.h          # 렌더링 처리 클래스
│   └── Tetromino.h         # 테트로미노 조각 클래스
└── src/                    # 소스 파일
    ├── Board.cpp           # 게임 보드 구현
    ├── Game.cpp            # 메인 게임 로직 구현
    ├── Input.cpp           # 플랫폼별 입력 처리
    ├── main.cpp            # 프로그램 진입점
    ├── Renderer.cpp        # 플랫폼별 렌더링
    └── Tetromino.cpp       # 테트로미노 조각 구현
```

## 의존성 (Dependencies)

- **언어**: C++17
- **빌드 시스템**: CMake 3.10+
- **플랫폼**: Windows, Linux
- **외부 라이브러리**: 표준 라이브러리만 사용

## 게임 점수 시스템

### 점수 시스템
- 단일 라인: 100점 기본
- 더블 라인: 300점 기본
- 트리플 라인: 500점 기본
- 테트리스 라인 (4줄): 800점 기본

### 레벨 시스템
- 10라인 클리어 시 레벨 상승
- 레벨이 높아질수록 조각 낙하 속도 증가
- 최대 레벨: 15

## 시스템 요구사항

- Ubuntu 20.04+ (GCC 9+)
- Windows 10+ (Visual Studio 2019+)
- CMake 3.10+

## 라이선스 (License)

이 프로젝트는 MIT 라이선스 하에 공개됩니다.