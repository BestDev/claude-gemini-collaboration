# 🤖 Gemini-Claude AI 협업 프로토콜

**두 AI가 하나의 팀처럼, 당신의 프로젝트를 위해 협업합니다.**

이 저장소는 **Gemini CLI** (전략가)와 **Claude Code** (전문 구현가)가 함께 일하며 소프트웨어를 개발하는 방법을 정의하는 **오픈소스 협업 프로토콜**입니다. 복잡한 아이디어를 구체적인 코드로, 버그 리포트를 안정적인 릴리즈로 만들어가는 과정을 직접 확인하고 당신의 프로젝트에 바로 적용해보세요.

## 🚀 시작하기: AI 팀과 함께 프로젝트 시작하기

이 가이드를 따라 당신의 프로젝트에 AI 협업 프로토콜을 적용하고 첫 작업을 시작해보세요.

### 0단계: 준비물

이 프로토콜은 두 AI 에이전트의 CLI(Command Line Interface) 도구를 사용합니다. 시작하기 전에 각 AI의 CLI가 설치되어 있고, 쉘(shell)에서 바로 실행할 수 있도록 설정되어 있어야 합니다.

-   **Gemini CLI 설치:** [설치 가이드 링크](https://github.com/google-gemini/gemini-cli)
-   **Claude Code 설치:** [설치 가이드 링크](https://docs.anthropic.com/ko/docs/claude-code/quickstart)

### 1단계: 프로토콜 파일 복사

이 저장소의 핵심 프로토콜 파일들을 당신의 프로젝트 루트 디렉토리로 복사합니다.

-   `GEMINI.md` - [→ 상세 규칙 보기](GEMINI.md)
-   `CLAUDE.md` - [→ 상세 규칙 보기](CLAUDE.md)
-   `COLLABORATION-RULES.md` - [→ 공통 협업 규칙 보기](COLLABORATION-RULES.md)
-   `.kb/` 폴더 전체

> 💡 **팁:** 이 저장소의 전체 구조가 궁금하다면, 바로 아래의 **'프로젝트 아키텍처'** 섹션을 참고하세요.

### 2단계: 시작 시나리오 선택

이제 당신의 상황과 선호하는 작업 방식에 맞는 시작 방법을 선택하세요.

#### 방법 1: 대화형 모드로 시작하기 (실시간 소통 및 복잡한 작업에 추천)

AI와 대화를 주고받으며 점진적으로 문제를 해결하고 싶을 때 사용하는 방식입니다.

1.  **Gemini 대화형 모드 실행:** 터미널에 아래 명령어를 입력하여 Gemini와 대화를 시작합니다.
    ```bash
    gemini --interactive
    ```
2.  **대화 시작:** 이제부터는 터미널이 대화창이 됩니다. 첫 지시사항을 입력하세요.
    ```
    온라인 체스 게임을 만들어줘. 먼저 전체적인 설계와 기술 스택을 제안해줄래?
    ```
    Gemini가 응답하며 프로젝트 계획을 세우고, 필요한 파일을 생성하는 등 다음 단계를 안내할 것입니다.

#### 방법 2: 비대화형(명령어) 모드로 시작하기 (스크립트 및 단일 작업에 추천)

미리 정의된 단일 명령을 실행하고 결과를 바로 얻고 싶을 때 사용합니다.

**A) Gemini에게 계획 수립을 지시하며 시작:**

1.  **요청사항 파일 생성 (Bash 명령어):**
    ```bash
    echo "온라인 체스 게임을 만들어줘. 주요 기능은 2인 대전, 기보 저장, 관전 모드야." > my_request.md
    ```
2.  **Gemini 실행 (비대화형):** `-p` 플래그를 사용하여 방금 만든 파일을 기반으로 계획 수립을 지시합니다.
    ```bash
    gemini -p "'my_request.md' 파일의 내용을 바탕으로, '.kb/projects/chess-game/' 폴더에 전체 프로젝트 계획과 상세 명세서(spec.md)를 작성해줘." -y
    ```

**B) Claude에게 코드 수정을 지시하며 시작:**

1.  **샘플 파일 생성 (Bash 명령어):**
    ```bash
    echo "def calculate_sum(a, b):\n    return a + b" > utils.py
    ```
2.  **Claude 실행 (비대화형):** `-p` 플래그를 사용하여 코드 수정을 직접 지시합니다.
    ```bash
    claude -p "'utils.py' 파일의 'calculate_sum' 함수에 로깅 기능을 추가해줘." --dangerously-skip-permissions
    ```

#### 방법 3: Claude Code 직접 대화 모드 (빠른 프로토타이핑, 버그 수정에 추천)

Claude와 직접 대화하며 즉시 문제를 해결하고 싶을 때 사용하는 방식입니다.

1.  **Claude Code 대화형 모드 실행:** 터미널에서 Claude Code를 시작합니다.
    ```bash
    claude
    ```
2.  **즉시 작업 지시:** 구체적인 작업을 바로 요청할 수 있습니다.
    ```
    payment.py 파일에서 NullPointerException 에러를 수정해줘. 그리고 필요하면 Gemini에게 자문 요청해줘.
    ```
3.  **자동 협업:** Claude가 필요하다고 판단하면 자동으로 Gemini에게 자문을 요청하고, 결과를 통합하여 최종 솔루션을 제공합니다.

> 💡 **Claude 주도의 장점**: 복잡한 계획 수립 없이 즉시 문제 해결에 착수할 수 있으며, 필요시 자동으로 Gemini의 전문성을 활용합니다.

---

## 🏛️ 프로젝트 아키텍처

> 💡 **참고:** 이 저장소의 전체 파일 구조와 각 프로토콜 문서, 샘플 프로젝트의 관계를 보여줍니다.

### 📊 프로젝트 폴더 구조

```mermaid
graph TD
    A[claude-gemini-collaboration/] --> B[CLAUDE.md]
    A --> C[GEMINI.md]
    A --> D[README.md]
    A --> E[COLLABORATION-RULES.md]
    A --> F[.kb/]
    A --> G[tetris/]
    A --> H[tetris_v2/]
    A --> I[word_counter/]
    
    F --> J[projects/]
    F --> K[sessions/]
    
    J --> L[tetris_v2/]
    K --> M[2025-08-18-tetris-development/]
    K --> N[2025-08-18-word-counter-development/]
    
    G --> O[src/]
    G --> P[include/]
    G --> Q[bin/]
    G --> R[Makefile]
    
    H --> S[src/]
    H --> T[include/TetrisV2/]
    H --> U[doc/]
    H --> V[assets/]
    H --> W[CMakeLists.txt]
    
    I --> X[src/main.cpp]
    I --> Y[README.md]
```

프로젝트의 성격에 따라 두 가지 주요 협업 모델을 선택할 수 있습니다.

### 🔄 협업 워크플로우 다이어그램

```mermaid
flowchart TD
    subgraph Scenario1 ["🏢 Scenario 1 (시나리오 1): Gemini-led Workflow (Gemini 주도 - 복잡한 신규 프로젝트)"]
        A1[User Request<br/>사용자 요청] --> B1[Gemini Analysis & Planning<br/>Gemini 분석 및 계획 수립]
        B1 --> C1[User Plan Approval<br/>사용자 계획 승인]
        C1 --> D1[Gemini spec.md Creation<br/>Gemini 명세서 작성]
        D1 --> E1[Claude Implementation<br/>Claude 구현]
        E1 --> F1[Gemini Verification<br/>Gemini 결과 검증]
        F1 --> G1[User Final Review<br/>사용자 최종 검토]
    end
    
    subgraph Scenario2 ["⚡ Scenario 2 (시나리오 2): Claude-led Workflow (Claude 주도 - 빠른 수정, 버그픽스)"]
        A2[User Request<br/>사용자 요청] --> B2[Claude Immediate Analysis<br/>Claude 즉시 분석]
        B2 --> C2{Gemini Consultation Needed?<br/>Gemini 자문 필요?}
        C2 -->|Yes| D2[Gemini Consultation<br/>Gemini 자문]
        C2 -->|No| E2[Claude Direct Implementation<br/>Claude 직접 구현]
        D2 --> E2
        E2 --> F2[Self Quality Verification<br/>자체 품질 검증]
        F2 --> G2[Final Report with Subagents<br/>Subagent 목록 포함 최종 보고]
    end
```

### Scenario 1 (시나리오 1): Gemini-led Workflow (Gemini 주도 - 복잡한 신규 프로젝트)

> **Architect (아키텍트, Gemini)가 Blueprint (청사진)을 그리면, Expert Builder (전문 시공사, Claude)가 Building (건물)을 짓는 모델**

1.  **[User 사용자]** "음성인식 비서를 위한 실시간 오디오 처리 파이프라인을 구축해줘" 같이 추상적인 아이디어를 Gemini에게 전달합니다.
2.  **[Gemini 🧠]** Requirements Analysis & Architecture Design (요구사항 분석 및 아키텍처 설계)를 수행하여 전체 계획을 수립합니다.
3.  **[User 사용자]** Gemini가 제시한 Plan (계획)을 검토하고 승인합니다.
4.  **[Gemini 🧠]** 승인된 계획에 따라 상세한 **Implementation Specification (`spec.md`, 구현 명세서)**를 `.kb/projects/[프로젝트명]/` 폴더에 작성하고 Claude에게 전달합니다.
5.  **[Claude ⚡]** 명세서를 기반으로, 내부의 **Specialized Subagents (전문가 에이전트)** 팀(예: cpp-expert, python-expert)을 동원하여 실제 코드를 작성하고 파일로 저장합니다. 모든 작업이 끝나면 **사용된 Subagent 목록을 반드시 보고**합니다.

### 🤖 Subagents 전문가 시스템 아키텍처

Claude Code는 13개의 내부 전문가 시스템을 운영하여 고성능 협업을 수행합니다.

```mermaid
graph TB
    subgraph L1 ["L1: Project Manager"]
        GM[Gemini CLI]
    end
    
    subgraph L2 ["L2: Expert Implementer"]
        CL[Claude Code]
    end
    
    subgraph L3 ["L3: Specialized Agents"]
        subgraph Lang ["언어별 전문가"]
            PY[PythonExpert]
            CPP[CppExpert]
            C[CExpert]
            UE[UnrealExpert]
            UN[UnityExpert]
            GO[GoExpert]
            DOT[DotNetExpert]
            NODE[NodeJSExpert]
        end
        
        subgraph DB ["데이터베이스"]
            MY[MySQLExpert]
            RD[RedisExpert]
            SQ[SQLiteExpert]
        end
        
        subgraph Project ["프로젝트 관리"]
            PA[ProjectAnalyzer]
            PDS[ProjectDocumentationSpecialist]
        end
    end
    
    GM --> CL
    CL --> Lang
    CL --> DB
    CL --> Project
```

**주요 특징:**
- **Hierarchical Structure (계층적 구조)**: L1(Planning 기획) → L2(Coordination 조율) → L3(Specialized Execution 전문 실행)
- **Parallel Processing (병렬 처리)**: 독립적인 작업을 동시에 수행하여 효율성 극대화
- **Mandatory Reporting (필수 보고 의무)**: Claude는 모든 작업 완료 시 **사용된 Subagent 목록을 반드시 보고**

**Subagent Selection Criteria (Subagent 선택 기준):**
1. **Project Type Priority (프로젝트 유형 우선)**: Unity → unity-expert, Unreal → unreal-expert
2. **File Extension (파일 확장자)**: `.py` → python-expert, `.cpp` → cpp-expert, `.cs` → dotnet-expert
3. **Task Nature (작업 성격)**: Documentation → project-documentation-specialist, Analysis → project-analyzer

> 📖 **더 자세한 Subagent 시스템**: [CLAUDE.md - Subagents System](CLAUDE.md#subagents-system-subagents-시스템---13개-전문가) 참조

**Quality Assurance Process (품질 보증 프로세스):**
- **Code Quality Verification (코드 품질 검증)**: 가능한 경우 lint/test/build 자동 실행
- **Completion Report (완료 보고)**: 사용된 Subagent 목록과 작업 결과 상세 보고
6.  **[Gemini 🧠]** Claude가 제출한 코드를 **컴파일, 테스트, 정적 분석**하여 품질을 검증하고 사용자에게 최종 보고합니다.

### Scenario 2 (시나리오 2): Claude-led Workflow (Claude 주도 - 빠른 프로토타이핑, 버그 수정)

> **Field Engineer (현장 기술자, Claude)가 문제를 해결하고, 필요시 Headquarters Design Team (본사 설계팀, Gemini)에 Consultation (자문)을 구하는 모델**

1.  **[User 사용자]** "결제 모듈에서 `NullPointerException`이 발생하고 있어. `Payment.java`를 수정해줘" 같이 구체적인 작업을 Claude에게 지시합니다.
2.  **[Claude ⚡]** Immediate Analysis & Implementation (즉시 분석 및 구현)에 착수합니다. 만약 문제의 원인이 더 깊은 Design Flaw (설계 결함)에 있다고 판단되면, 작업을 멈추고 Gemini에게 Consultation (자문)을 요청합니다.
3.  **[Gemini 🧠]** Claude의 요청에 따라 Root Cause Analysis (근본 원인 분석)를 수행하고, 해결을 위한 **Solution Proposal (`solution-proposal.md`, 솔루션 제안서)**를 작성하여 회신합니다.
4.  **[User 사용자]** Gemini의 Solution (해결책)을 검토하고 진행 방향을 승인합니다.
5.  **[Claude ⚡]** 승인된 해결책에 따라 최종적으로 코드를 수정하고, **Self Quality Verification (자체 품질 검증 - build, regression test)**을 거쳐 **사용된 Subagent 목록과 함께** 사용자에게 완료 보고를 합니다.

---

## 🧑‍🤝‍🧑 우리 팀을 소개합니다: 역할과 책임 (R&R)

| 역할 | 🧠 **Gemini CLI** (PM & Architect) | ⚡ **Claude Code** (Expert Implementer) |
| :--- | :--- | :--- |
| **핵심 임무** | **"무엇을, 왜"** 결정 | **"어떻게"** 구현 |
| **주요 책임** | <ul><li>요구사항 분석 및 구체화</li><li>아키텍처 설계 및 기술 결정</li><li>작업 계획 및 상세 명세서 작성</li><li>최종 결과물 통합 및 검증</li></ul> | <ul><li>명세서 기반의 정확한 코드 구현</li><li>**13개의 내부 전문가(Subagents) 팀 조율**</li><li>**코드 품질 자동 검증 (Lint, Build, Test)**</li><li>구현 실패 시 대안 제시 및 보고</li></ul> |

## ⚙️ Core Collaboration Principles (핵심 협업 원칙): 우리만의 약속

### 🗂️ File-Based Communication (파일 기반 소통)
모든 AI 간 소통은 파일 경로를 통해 이루어집니다. 이는 모든 과정을 투명하게 추적하고, AI가 내린 결정의 근거를 명확히 남기기 위함입니다.
- **파일 기반 지시**: `echo "파일 '.kb/projects/game/spec.md'를 참조하여 구현해주세요" | gemini -y`
- **UTF-8 Encoding (UTF-8 인코딩)**: 모든 파일명은 영문, 내용은 한글, 인코딩은 UTF-8로 통일

> 📖 **상세 규칙**: [COLLABORATION-RULES.md - Inter-AI Communication](COLLABORATION-RULES.md#-inter-ai-communication-ai-간-소통-원칙) 참조

### 🧠 Knowledge Base System (`.kb` 지식베이스 시스템)
프로젝트의 단순 결과물(코드)뿐만 아니라, 그 과정(왜 그렇게 만들었는가)까지 모두 기록하는 프로젝트의 '뇌'입니다.
- **`.kb/projects/[프로젝트명]/`**: 명세서, 설계 문서, ADR 등 정적 문서
- **`.kb/sessions/[날짜]/`**: Complex Collaboration 조건 충족 시 세션 로그 자동 생성

### 👑 User-Centric Control (사용자 중심 제어)
AI는 당신의 가장 유능한 팀원이지만, 프로젝트의 선장은 언제나 당신입니다. 모든 핵심 단계에서 최종 결정은 당신의 몫입니다.

### ✅ Quality Assurance Protocol (품질 보증 프로토콜)
Claude는 코드를 작성한 후, 자체적으로 빌드, 린팅, 테스트를 포함한 품질 검증 프로세스를 수행하여 안정성을 확보합니다.
- **Mandatory Quality Verification (필수 품질 검증)**: lint/test/build 가능한 경우 자동 실행
- **Error Handling Protocol (에러 처리 프로토콜)**: 실패 시 `.kb/sessions/[세션명]/error-report.md` 생성

### 🔄 Hybrid File Modification (하이브리드 파일 수정)
- **Simple Changes (단순 변경)**: Edit 도구로 1-2곳 수정
- **Multiple Changes (다중 변경)**: MultiEdit 도구로 같은 파일 내 3곳 이상 수정
- **Major Refactoring (대규모 리팩토링)**: 새 파일 생성 후 교체

### 📋 Complex Collaboration Triggers (복잡한 협업 트리거)
다음 조건 중 하나라도 해당하면 `.kb/sessions/` 디렉토리에 세션 로그를 자동 생성:
- 2개 이상 AI가 협업하는 경우
- 3개 이상 파일을 수정하는 경우  
- 새로운 기술 스택 도입이 필요한 경우
- 사용자가 "세션 기록해줘", "문서화해줘" 요청하는 경우

> 📖 **전체 조건 및 규칙**: [COLLABORATION-RULES.md - Complex Collaboration](COLLABORATION-RULES.md#2-complex-collaboration-복잡한-협업-세션-시---다음-조건-중-하나라도-해당) 참조

## ⚠️ 중요: 권한 및 설정

-   **AI 에이전트 설치:** 이 프로토콜을 사용하려면 `gemini`와 `claude` CLI 도구가 모두 설치 및 설정되어 있어야 합니다.
-   **Gemini → Claude 호출 시 (파일 쓰기 권한):** Gemini가 Claude에게 파일 생성을 지시할 때는, 보안상의 이유로 명령어에 `--dangerously-skip-permissions` 플래그를 포함해야 합니다. 이는 Claude에게 파일 시스템 접근 권한을 직접 부여하는 것이므로, 항상 그 목적을 명확히 인지하고 사용해야 합니다. - [→ GEMINI.md 상세 가이드](GEMINI.md)
-   **Claude → Gemini 호출 시 (자동 승인 모드):** 반대로 Claude가 Gemini에게 분석이나 자문을 요청할 때는, 대화가 중단되지 않도록 `echo "..." | gemini -y` 와 같이 `-y` (YOLO 모드) 플래그를 사용해야 합니다. 이는 Gemini의 모든 확인 프롬프트를 자동으로 승인하여 원활한 연동을 보장합니다. - [→ CLAUDE.md 상세 가이드](CLAUDE.md)

---

이 프로토콜이 당신의 개발 경험을 더욱 창의적이고 효율적으로 만들길 바랍니다. 언제든 이 저장소를 포크하여 당신만의 AI 협업 방식을 만들어보세요!
