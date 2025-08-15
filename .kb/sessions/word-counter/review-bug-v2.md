# 코드 리뷰 및 버그 리포트 2: `word_counter` 기능 회귀

## 버전
- **대상 파일**: `word_counter/src/main.cpp` (v2)

## 문제점
- **심각한 기능 회귀**: 이전 버그 리포트(`review-bug-v1.md`)는 '글자 수' 계산 오류만 수정하도록 요청했으나, 제출된 코드는 **기존의 줄(line)과 단어(word) 계산 기능을 전부 삭제**하고 출력 형식까지 변경하는 심각한 오류를 포함하고 있다.

## 수정 요구사항
- **핵심 지시:** **줄과 단어를 세는 기존 기능은 반드시 유지**하면서, 글자 수를 세는 로직만 정확하게 수정해야 한다.
- **출력 형식 준수:** 최종 출력은 반드시 `[줄 수] [단어 수] [글자 수] [파일 경로]` 형식을 따라야 한다.

## 제안하는 해결책
- 현재의 `getline` 기반 구조는 복잡하고 오류가 많으니, 파일을 한 글자씩 읽는 방식으로 전체 로직을 재구성하는 것을 강력히 권장한다. 아래는 검증된 로직 예시이다.

```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <cctype> // isspace()를 위해 추가

// ... main 함수 내부 ...

    size_t line_count = 0;
    size_t word_count = 0;
    size_t char_count = 0;
    char c;
    char prev_c = ' '; // 단어 계산을 위해 이전 문자를 저장

    while (file.get(c)) {
        char_count++;
        if (c == '\n') {
            line_count++;
        }
        // 현재 문자가 공백이고 이전 문자가 공백이 아닐 때 단어 수 증가
        if (std::isspace(c) && !std::isspace(prev_c)) {
            word_count++;
        }
        prev_c = c;
    }

    // 파일이 공백으로 끝나지 않는 경우, 마지막 단어를 계산
    if (char_count > 0 && !std::isspace(prev_c)) {
        word_count++;
        // 파일 끝에 개행이 없는 경우, 마지막 줄을 계산
        if (line_count == 0) line_count = 1;
    }

// ... 파일 닫고 결과 출력 ...
```

## 요청
**위 제안 로직을 참고하여, 줄/단어/글자 수를 모두 정확히 계산하고 올바른 형식으로 출력하도록 `word_counter/src/main.cpp` 파일을 다시 수정해주십시오.** 기존 파일을 덮어써야 합니다.
