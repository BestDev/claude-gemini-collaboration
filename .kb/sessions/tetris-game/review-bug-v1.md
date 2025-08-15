# 코드 리뷰 및 버그 리포트: src/main.cpp

## 버전
- **대상 파일**: `src/main.cpp` (v1)

## 문제점
`make` 명령어로 ncurses 버전 컴파일 시, 세 가지 주요 컴파일 오류가 발생함.

### 1. `mvaddstr` 매크로의 잘못된 사용
- **오류**: `error: macro "mvaddstr" passed 4 arguments, but takes just 3`
- **원인**: `mvaddstr` 함수는 `printf`와 같이 포맷팅을 지원하지 않는데, `"Final Score: %d"`와 같은 형식 지정자를 사용하여 여러 인자를 전달하려고 시도함.
- **수정 제안**: `std::string`과 `std::to_string`을 사용하거나, `snprintf`를 사용하여 문자열을 미리 만든 후, 완성된 문자열을 `mvaddstr`에 전달해야 함.
  ```cpp
  // 예시
  std::string score_str = "Final Score: " + std::to_string(board_.getScore());
  mvaddstr(13, info_start_x, score_str.c_str());
  ```

### 2. `exit` 함수 미선언
- **오류**: `error: ‘exit’ was not declared in this scope`
- **원인**: `exit()` 함수를 사용하기 위한 `<cstdlib>` 헤더가 포함되지 않음.
- **수정 제안**: 파일 상단에 `#include <cstdlib>`를 추가해야 함.

### 3. `info_start_x` 변수 미선언
- **오류**: `error: ‘info_start_x’ was not declared in this scope` in `run()` function.
- **원인**: `run()` 함수 내에서 `info_start_x` 변수가 선언 및 초기화되지 않은 채 사용됨.
- **수정 제안**: `render()` 함수에서 사용된 것과 유사하게, `run()` 함수 내에서도 `info_start_x` 변수를 적절히 선언하고 값을 할당해야 함. (예: `int info_start_x = board_.getWidth() + 3;`)

## 요청
위 세 가지 오류를 모두 수정하여, `make` 명령어로 컴파일이 성공적으로 완료되도록 `src/main.cpp` 파일을 직접 수정해주십시오. (새 파일을 만들 필요 없습니다.)
