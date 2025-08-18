# Tetris

## 설명
크로스플랫폼 콘솔 기반 테트리스 게임. Windows와 Linux에서 동작하는 간단한 테트리스 구현입니다.

## 빌드 방법

### Linux/macOS
```bash
make
```

### Windows (Visual Studio)
```bash
make -f Makefile.console
```

## 사용법
```bash
# 콘솔 버전 실행
./bin/tetris_console

# ncurses 버전 실행 (Linux/macOS)
./bin/tetris_ncurses
```

## 조작법
- **A/좌측 화살표**: 왼쪽 이동
- **D/우측 화살표**: 오른쪽 이동  
- **S/아래 화살표**: 빠른 낙하
- **W/위쪽 화살표**: 블록 회전
- **Q**: 게임 종료

## 의존성
- **Linux/macOS**: ncurses 라이브러리 (ncurses 버전용)
- **Windows**: 표준 Windows API
- **공통**: C++11 이상 지원 컴파일러