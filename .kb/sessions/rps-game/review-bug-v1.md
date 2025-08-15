# 코드 리뷰 및 버그 리포트: rps_game.cpp

## 버전
- **대상 파일**: `rps_game.cpp` (v1)

## 문제점
- **현상**: 비대화형 환경(예: 스크립트 실행)에서 프로그램을 실행하면, `std::cin`이 파일 끝(EOF)을 만난 후 무한 루프에 빠진다.
- **원인**: 현재의 `while(true)` 루프는 `std::cin >> input;` 작업이 실패했는지 확인하는 로직이 없다. `std::cin`은 EOF에 도달하면 에러 상태가 되고, 이후의 모든 읽기 시도가 즉시 실패하면서 루프가 무한정 반복된다.

## 수정 요구사항
`playRound()` 함수 내부의 `std::cin >> input;` 라인을 수정하여, 입력 스트림이 닫혔거나(EOF) 에러가 발생했을 때 루프를 정상적으로 종료하도록 변경해야 한다.

## 제안하는 해결책
아래와 같이 `std::cin`의 상태를 직접 확인하는 조건문을 추가한다.

```cpp
// 기존 코드
std::cin >> input;

// 수정 제안
if (!(std::cin >> input)) {
    std::cout << "\nInput stream closed. Exiting." << std::endl;
    showFinalScore();
    exit(0);
}
```

또는 `run()` 함수의 `while(true)` 루프를 `while(std::cin)`과 유사한 형태로 변경하는 것도 가능하다.

## 요청
위 분석 내용을 바탕으로 `rps_game.cpp`의 버그를 수정한 후, 수정된 파일을 `rps_game_v2.cpp`로 저장해주십시오.

```