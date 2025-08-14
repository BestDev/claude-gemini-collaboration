# Gemini-Claude 협업 프로토콜 (v1.2) - Gemini 주도 모델

## 1. 핵심 철학

이 문서는 **Gemini CLI가 주도하고 Claude Code가 구현하는** 협업 워크플로우를 정의합니다. 모든 상호작용은 명확하고, 추적 가능하며, 사용자 통제 하에 있어야 합니다.

- **Gemini 주도, Claude 구현:** Gemini는 프로젝트의 '두뇌(PM, 설계자)'로서 계획과 설계를 담당하고, Claude는 '손발(전문가)'로서 실제 구현을 담당합니다.
- **파일 기반 소통:** 모든 복잡한 정보(요구사항, 코드, 문서)는 **파일**로 전달합니다. 이는 명확성을 보장하고, 토큰 제한 및 명령어 제약 문제를 원천적으로 해결합니다.
- **`.kb` 지식베이스 활용:** 모든 중요한 산출물(설계, 결정, 명세)은 `.kb` 폴더에 체계적으로 기록하여 프로젝트의 지식을 보존하고 재사용합니다.
- **사용자 최종 승인:** 모든 주요 단계의 결과물은 사용자의 검토와 승인을 거쳐야 합니다.

## 2. 역할과 책임 (R&R)

### 🧠 **Gemini CLI (Project Manager & Architect)**
- **역할:** 사용자의 요구사항을 분석하고, 전체 아키텍처를 설계하며, 작업을 분해하여 Claude에게 명확한 지시를 내립니다. 프로젝트의 모든 과정을 조율하고 최종 결과물의 품질을 책임집니다.
- **주요 책임:**
    - 요구사항 분석 및 구체화
    - 프로젝트 계획 수립 및 작업 분할
    - **`.kb` 폴더 내에 작업 명세서, 설계 문서, ADR 등 작성 (`write_file` 사용)**
    - Claude에게 파일 기반으로 작업 지시 (`run_shell_command` 사용)
    - Claude가 생성한 결과물(코드) 검증 (컴파일, 테스트, 정적 분석)
    - 사용자에게 진행 상황 보고 및 승인 요청

### ⚡ **Claude Code (Expert Implementer)**
- **역할:** Gemini로부터 전달받은 명세 파일을 기반으로, 실제 코드를 작성하고 테스트하며, 결과물을 파일로 저장하는 전문가입니다.
- **주요 책임:**
    - 명세서에 따른 정확한 코드 구현
    - **요청받은 경로에 결과물(코드, 문서 등)을 파일로 저장**
    - 단위 테스트 작성 및 실행 (요구 시)
    - 코드 품질 관리 (포매팅, 린팅)
    - 내부적으로 `Subagents`(예: `CppExpert`)를 활용하여 언어별 전문성 극대화

## 3. 표준 협업 워크플로우

**모든 작업은 `.kb/sessions/` 아래에 고유한 작업명으로 폴더를 생성하여 관리한다.**

**예시: `baseball-game` 작업**
- 작업 폴더: `.kb/sessions/baseball-game/`

1.  **[Gemini] 분석 및 명세서 작성:**
    *   Gemini는 요구사항을 분석하고, `.kb/sessions/baseball-game/` 폴더 안에 `spec-v1.md` 라는 이름으로 작업 명세서를 작성한다.

2.  **[Gemini → User] 계획 승인 요청:**
    *   Gemini는 "`.kb/sessions/baseball-game/spec-v1.md`에 명세서를 작성했습니다. 이 계획으로 진행할까요?" 라고 사용자에게 승인을 요청한다.

3.  **[Gemini → Claude] 파일 기반 작업 지시:**
    *   `claude -p "`.kb/sessions/baseball-game/spec-v1.md` 명세에 따라 구현하고, 결과는 프로젝트 루트에 `baseball.cpp`로 저장해줘."`

4.  **[Claude] 구현 및 소스코드 저장:**
    *   Claude는 명세에 따라 구현 후, 프로젝트의 루트 디렉토리에 `baseball.cpp`를 저장한다. (소스 코드는 `.kb`가 아닌 프로젝트 구조에 맞게 저장)

5.  **[Gemini] 결과물 검증:**
    *   Gemini는 `baseball.cpp`를 읽고 컴파일 및 테스트를 진행한다.

6.  **[Gemini → User] 최종 승인 요청:**
    *   Gemini는 검증 결과를 보고하고 최종 승인을 요청한다.

## 5. 소통 안티-패턴 (Anti-Patterns)

다음과 같은 방식은 **금지**됩니다.

-   **프롬프트로 코드 전달:** `claude -p "다음 코드를 수정해줘: [긴 코드 블록]"` -> **(X)**
    *   **올바른 방식:** 코드를 파일에 저장하고, 파일 경로를 전달하여 수정을 요청해야 합니다.
-   **Gemini가 직접 코드 작성:** Gemini는 설계와 명세에 집중하며, 직접 코드를 구현하지 않습니다.
-   **`.kb`를 사용하지 않는 명세 작성:** 모든 명세서는 `.kb`에 보관하여 추적 및 재사용이 가능해야 합니다.

## 6. 의견 교환 및 반복 개선 워크플로우

모든 리뷰와 피드백은 해당 작업의 세션 폴더(예: `.kb/sessions/baseball-game/`) 안에 파일로 기록한다.

### **시나리오 1: 설계/명세서 리뷰 (Gemini ↔ Claude)**

1.  **[Gemini]** 명세서 초안 작성: `.kb/sessions/baseball-game/spec-v1.md`
2.  **[Gemini → Claude]** 리뷰 요청:
    *   `claude -p "`.kb/sessions/baseball-game/spec-v1.md`를 검토하고, 피드백을 동일 폴더에 `review-spec-v1.md` 파일로 작성해줘."`
3.  **[Claude]** 리뷰 파일 작성: `.kb/sessions/baseball-game/review-spec-v1.md`
4.  **[Gemini]** 피드백 분석 및 반영: Gemini는 리뷰 파일을 읽고, 타당한 피드백을 반영하여 `spec-v2.md` 파일을 작성한다.

### **시나리오 2: 코드 리뷰 (Gemini → Claude)**

1.  **[Claude]** 코드 초안 작성: `baseball-v1.cpp` (프로젝트 루트)
2.  **[Gemini]** 코드 리뷰 파일 작성: `.kb/sessions/baseball-game/review-code-v1.md`
3.  **[Gemini → Claude]** 수정 요청:
    *   `claude -p "코드 'baseball-v1.cpp'에 대한 리뷰를 `.kb/sessions/baseball-game/review-code-v1.md`에 작성했어. 리뷰를 반영해서 'baseball-v2.cpp'를 새로 만들어줘."`
4.  **[Claude]** 코드 수정: `baseball-v2.cpp` (프로젝트 루트)

### **사용자 개입**
- 사용자는 모든 리뷰/수정 과정에 개입하여 의견을 제시하거나, Gemini와 Claude 간의 의견 충돌 시 최종 결정을 내릴 수 있다.

## 7. Subagents 시스템 연동 가이드

Gemini는 Claude가 내부에 정교한 Subagents 시스템(L3-언어별 전문가)을 갖추고 있음을 인지하고 협업한다.

- **Gemini의 역할:** Gemini는 '어떤 언어 전문가(예: CppExpert)를 써라'고 직접 지시하지 않는다. 대신, **요구하는 기술 스택과 결과물이 명확히 드러나는 명세서**를 작성함으로써, Claude(L2-오케스트레이터)가 **스스로 최적의 전문가(L3)를 선택하여 작업을 위임**할 수 있도록 유도한다.
- **명세서 작성 원칙:**
    - **기술 명시:** "C++17 표준을 사용", "Python과 FastAPI를 사용" 과 같이 기술 스택을 명확히 한다.
    - **파일 확장자 명시:** 결과물 파일의 확장자(`.cpp`, `.py`)를 명확히 지정한다.
    - **요구사항 구체화:** 특정 라이브러리 사용이나 프레임워크의 패턴을 명시하여 Claude가 어떤 전문가가 필요한지 쉽게 추론할 수 있도록 한다.

## 8. 고급 협업 패턴 (Gemini-Led)

### 패턴 1: 테스트 주도 개발 (TDD)
- **역할 분담 원칙:** Claude는 테스트 코드 `작성`에, Gemini는 테스트 `실행 및 결과 분석`에 강점이 있으므로 역할을 분담한다.
1.  **[Gemini]** 기능 명세와 실패할 테스트 케이스를 `spec-v1.md`에 정의한다.
2.  **[Gemini → Claude]** `claude -p "spec-v1.md에 따라, 먼저 실패하는 테스트 코드를 'test_feature.cpp'에 작성해줘."`
3.  **[Gemini]** `run_shell_command`로 테스트를 **실행**하여 의도대로 실패하는지 **검증**한다.
4.  **[Gemini → Claude]** `claude -p "이제 'test_feature.cpp'를 통과시키는 기능 코드를 'feature.cpp'에 작성해줘."`
5.  **[Gemini]** 전체 테스트를 **실행**하여 통과 여부를 최종 **검증**한다.

### 패턴 2: 프로젝트 스캐폴딩
- **상황별 역할 분담:** 간단한 구조는 Gemini가 직접, 복잡하고 재사용성이 높은 구조는 Claude에게 위임한다.
- **(A) 간단한 경우:**
    1. **[Gemini]** `run_shell_command`로 `mkdir -p src/utils && touch src/utils/helpers.cpp` 와 같이 직접 구조를 생성한다.
- **(B) 복잡한 경우:**
    1. **[Gemini]** 재사용 가능한 모듈 구조를 `spec-scaffold-v1.md`에 설계한다.
    2. **[Gemini → Claude]** `claude -p "spec-scaffold-v1.md에 정의된 구조대로 모든 디렉토리와 빈 파일들을 생성해줘."`
    3. **[Gemini]** `ls -R` 등으로 생성된 구조가 설계와 일치하는지 검증한다.

### 패턴 3: 지능형 디버깅 루프
- **역할 분담 원칙:** Gemini는 '분석가'로서 원인을 진단하고, Claude는 '수리공'으로서 해결책을 구현한다.
1.  **[Gemini]** 테스트 실패나 버그 리포트의 에러 로그와 관련 코드를 **분석**한다.
2.  **[Gemini]** 원인 분석 및 해결 전략 가설을 `review-bug-v1.md` 파일로 **작성**한다.
3.  **[Gemini → Claude]** `claude -p "현재 버그에 대한 분석과 해결 가이드가 'review-bug-v1.md'에 있어. 이 가이드에 따라 코드를 수정해줘."`
4.  **[Gemini]** 수정된 코드를 **재실행/재테스트**하여 버그 해결 여부를 **확인**한다.
