# Word Counter

## 설명
파일의 줄 수, 단어 수, 문자 수를 계산하는 C++ 프로그램입니다. Unix의 `wc` 명령어와 유사한 기능을 제공합니다.

## 빌드 방법
```bash
g++ -std=c++11 -o word_counter src/main.cpp
```

## 사용법
```bash
# 파일의 통계 정보 출력
./word_counter filename.txt

# 표준 입력에서 읽기
cat filename.txt | ./word_counter
```

## 출력 형식
```
   줄수   단어수   문자수 파일명
```

## 의존성
- C++11 이상 지원 컴파일러
- 표준 C++ 라이브러리