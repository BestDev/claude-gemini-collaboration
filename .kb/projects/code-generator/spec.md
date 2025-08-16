# 작업 명세서: Code Generator (v1.0)

## 기본 정보
- **작성자**: Gemini CLI
- **작성일**: 2025-08-16
- **대상**: Claude Code
- **프로젝트**: code-generator
- **요청자**: bestdev

## 작업 개요
### 목표
사용자의 자연어 요구사항을 바탕으로 Python 소스 코드를 생성하는 기본 스크립트를 구현한다.

### 배경
AI를 활용한 코드 자동 생성 기능의 첫 단계로, 핵심 로직의 프로토타입을 개발하여 기능의 실현 가능성을 검증하고자 한다.

## 상세 요구사항

### 기능 요구사항
1.  **CLI 실행**: Python 스크립트는 커맨드 라인에서 실행 가능해야 한다.
2.  **인자(Argument) 처리**: 다음 두 개의 커맨드 라인 인자를 받아야 한다.
    -   `--description`: 생성할 코드에 대한 자연어 설명 (문자열)
    -   `--output_file`: 생성된 코드를 저장할 파일 경로 (문자열)
3.  **코드 생성 함수**: `generate_code(description: str) -> str` 함수를 구현한다.
    -   **초기 버전**: 실제 AI 모델 대신, 입력된 `description`을 포함하는 간단한 "Hello World" Python 코드를 문자열로 반환하는 **목(mock) 함수**로 구현한다.
4.  **파일 저장**: `generate_code` 함수가 반환한 문자열을 `--output_file` 인자로 지정된 경로에 파일로 저장한다.

### 비기능 요구사항
- **문서화 (Documentation):** **Tier 1**
    - 코드 내 상세한 주석.
    - 프로젝트 설명, 빌드 및 실행 방법이 포함된 `README.md` 파일 생성.

## 기술적 제약사항
- **언어**: Python 3.9 이상
- **외부 의존성 (External Dependencies):** 없음. Python 표준 라이브러리만 사용한다.

## 구현 가이드

### 파일 구조
```
code-generator/
├── src/
│   └── main.py
└── README.md
```

### `src/main.py` 구현 상세
- `argparse` 라이브러리를 사용하여 CLI 인자를 파싱한다.
- `generate_code` 함수는 아래와 같이 간단한 형태로 구현한다.
  ```python
  def generate_code(description: str) -> str:
      """
      주어진 설명을 바탕으로 Python 코드를 생성하는 목 함수.
      """
      return f"""
  # Auto-generated code based on: '{description}'
  
  def main():
      print("Hello, World!")
  
  if __name__ == "__main__":
      main()
  """
  ```
- 스크립트의 메인 실행 블록(`if __name__ == "__main__":`)에서 인자를 파싱하고, 위 함수를 호출하여 결과 파일을 생성하는 로직을 포함한다.

## 테스트 요구사항
- 별도의 자동화된 테스트 코드는 요구되지 않음.
- 단, 아래의 수동 테스트 케이스를 실행하여 정상 동작을 확인해야 함.
  - `python src/main.py --description "hello world program" --output_file "hello.py"` 실행 후 `hello.py` 파일 내용 확인.

## 완료 기준
- [ ] `code-generator/src/main.py` 파일이 생성됨.
- [ ] `code-generator/README.md` 파일이 생성됨.
- [ ] `README.md`에는 프로젝트 설명과 실행 방법이 명시되어 있음.
- [ ] 스크립트가 커맨드 라인 인자를 통해 정상적으로 실행되고, 명세에 맞는 출력 파일을 생성함.

## 예상 영향 범위
- **신규 파일**: 
  - `code-generator/src/main.py`
  - `code-generator/README.md`

---
**승인 후 Claude Code에서 구현을 시작합니다.**
