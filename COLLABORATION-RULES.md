# AI Collaboration Common Rules (AI 협업 공통 규칙)

## 🎯 Core Philosophy: User-Centric Collaboration Model (사용자 중심 협업 모델)

### Collaborative Design Principle (협업 설계 원칙)
이 협업 규칙은 **사용자 중심 협업 모델**을 기반으로 설계되었습니다. 여러 협업 모델을 검토한 결과, 다음과 같은 이유로 이 모델을 채택했습니다:

**선택 이유:**
- **투명성**: 모든 과정이 사용자에게 명확히 보고됨
- **제어권**: 사용자가 언제든 과정에 개입하고 방향을 수정할 수 있음
- **실용성**: 현재 AI 기술 수준에서 가장 현실적인 접근법

**핵심 구조:**
```
사용자 요청 → Gemini 분석&계획 → [사용자 승인] → 
Gemini 명세서 작성 → Claude 구현 → [사용자 검토] → 완료
```

### Clear Role Separation (명확한 역할 분리)

```
.kb/ → AI 간 협업 소통 기록 (Internal AI Communication)
[프로젝트]/doc/ → 사용자 문서 (User Documentation)
[프로젝트]/README.md → 프로젝트 소개 (Project Introduction) - 예외
```

## 📋 Documentation Triggers (문서 생성 조건)

### ✅ 자동 생성 (Automatic Creation) - 반드시 만들어야 함

#### 1. 프로젝트 시작 시 (Project Start)
```
✅ .kb/projects/[프로젝트명]/spec.md (Gemini 작성)
✅ [프로젝트명]/README.md (Claude 작성)
```

#### 2. 복잡한 협업 세션 시 (Complex Collaboration) - 다음 조건 중 하나라도 해당
```
조건 (Conditions):
- 2개 이상 AI가 협업하는 경우
- 구현 시간이 30분 이상 예상되는 경우  
- 사용자가 "세션 기록해줘" 요청하는 경우

생성 (Create):
✅ .kb/sessions/YYYY-MM-DD-작업명/session-log.md
```

### 📝 선택적 생성 (Optional Creation) - 요청 시에만

#### 3. 고급 문서화 요청 시 (Advanced Documentation Request)
```
사용자가 명시적으로 "자세한 문서 만들어줘" 요청 시:
📝 [프로젝트명]/doc/user-guide.md
📝 [프로젝트명]/doc/developer-guide.md  
📝 [프로젝트명]/doc/architecture.md
```

## 🤖 AI Responsibility Areas (AI별 담당 영역)

- **Gemini CLI**: 요구사항 분석, 아키텍처 설계, 작업 명세서 작성
- **Claude Code**: 코드 구현, 프로젝트 README 작성, 구현 보고서 작성
- **Documentation Specialist**: 사용자 가이드, 개발자 문서 등 고급 문서화 (요청 시에만)

## 📁 Folder Structure (폴더 구조)

### `.kb/` (For AI Collaboration)
```
.kb/
├── sessions/                    # 세션별 작업 기록
│   └── YYYY-MM-DD-작업명/
│       ├── session-log.md       # 세션 진행 기록
│       ├── ai-collaboration.md  # AI 간 소통 내역
│       └── decisions.md         # 주요 결정 사항
└── projects/                    # 프로젝트별 AI 소통 기록
    └── [프로젝트명]/
        ├── spec.md              # Gemini → Claude 작업 명세
        ├── implementation.md    # Claude 구현 보고서
        └── review.md            # 상호 리뷰 기록
```

### `[Project Name]/` (Project Code & Docs)
```
tetris_v2/
├── README.md                       # 프로젝트 소개 (Claude 작성)
├── src/, include/, CMakeLists.txt   # 실제 코드
└── doc/                            # 추가 사용자 문서
    ├── implementation.md           # 구현 보고서 (Claude 작성)
    ├── user-guide.md               # 사용자 가이드
    ├── developer-guide.md          # 개발자 가이드
    └── architecture.md             # 시스템 아키텍처
```

## 📝 Document Standards (문서 작성 표준)

### Gemini's spec.md Format
```markdown
# [프로젝트명] 작업 명세서
## 목표 (Goal)
[구체적인 목표]

## 요구사항 (Requirements)  
[기능 요구사항 나열]

## 기술 스택 (Tech Stack)
[사용할 기술/라이브러리]

## 구현 가이드 (Implementation Guide)
[Claude가 따라야 할 구현 순서]

## 중요 규칙 재확인 (Key Rule Reminder)
- **언어/인코딩**: 모든 파일명은 영문, 내용은 한글로 작성하며, 파일 인코딩은 UTF-8로 통일합니다.
- **(기타 이 작업에 특히 중요한 규칙 명시)**

## 완료 조건 (Completion Criteria)
[작업 완료 판단 기준]
```

### Claude's README.md Format (Project Root)
```markdown
# [프로젝트명]
## 설명 (Description)
[프로젝트 한 줄 설명]

## 빌드 방법 (Build Instructions)
[설치 및 빌드 명령어]

## 사용법 (Usage)
[기본 사용법]

## 의존성 (Dependencies)
[필요한 라이브러리/도구]
```

### Session Log Format
```markdown
# 세션 기록: [작업명]
- 날짜 (Date): YYYY-MM-DD
- 참여 AI (Participants): Claude, Gemini 등
- 목표 (Goal): [이 세션의 목표]

## 진행 과정 (Process)
1. [단계별 진행 사항]

## 주요 결정사항 (Key Decisions)
- [중요한 기술적 결정들]

## 결과 (Results)
- [완료된 작업들]
- [미완료/다음 단계]
```

### ✍️ Document Metadata Rule (문서 메타데이터 규칙)

`.kb` 디렉토리 내의 모든 문서는 최상단에 아래 형식의 메타데이터를 포함해야 한다.

> - **요청자 (Requester):** `User` | `Gemini` | `Claude`
> - **작성자 (Author):** `Gemini` | `Claude (Subagent 이름)`
> - **생성일시 (Timestamp):** `YYYY-MM-DD HH:MM:SS`
> - **목적 (Purpose):** [문서 생성의 핵심 목적 한 줄 요약]

*참고: `작성자`가 Claude일 경우, 실제 작업을 수행한 전문가 Subagent의 이름을 괄호 안에 명시합니다.*

**예시:**
> - **요청자 (Requester):** `User`
> - **작성자 (Author):** `Gemini`
> - **생성일시 (Timestamp):** `2025-08-18 14:30:00`
> - **목적 (Purpose):** `tetris_v3` 프로젝트의 초기 기능 명세 정의.

## 🔄 Inter-AI Communication (AI 간 소통 원칙)

### 1. 파일 기반 소통 (File-Based Communication)
- **원칙**: 모든 작업 지시는 파일 경로를 통해 이루어짐
- **예시**: `echo "파일 '.kb/projects/game/spec.md'를 참조하여 구현해주세요" | gemini -y`

### 2. 프로젝트 폴더 구조 (Project Folder Structure)
- **규칙**: 모든 개별 프로젝트는 루트 디렉토리에 자신의 이름을 딴 전용 폴더 생성
- **구조**: 모든 관련 파일은 해당 폴더 내에 위치
- **예외**: README.md는 각 프로젝트 루트에 위치 (다른 사용자 접근성 우선)

### 3. 작업자 직접 저장 (Direct Worker Storage)
- **Gemini**: 분석 보고서, 명세서, 설계 문서 등을 직접 파일로 저장
- **Claude**: 코드, 테스트, README.md, 빌드 결과물 등을 직접 파일로 저장
- **효율성**: 중간 전달 과정 없이 바로 저장으로 시간 단축

## ✅ 작업 시작 체크리스트 (Pre-Task Checklist)

복잡하거나 2개 이상의 AI가 협업하는 작업을 시작하기 전, 담당 AI는 아래 항목을 사용자에게 보고해야 한다.

1.  **규칙 확인:** `COLLABORATION-RULES.md`의 최신 내용을 숙지했는가?
2.  **세션 기록:** '복잡한 협업 세션'에 해당하여 `.kb/sessions/`에 로그 디렉토리를 생성했는가?
3.  **목표 명확화:** 사용자의 최종 목표와 완료 조건이 명확한가?

## 🔬 Unit Test Rule (유닛 테스트 규칙)

시스템의 핵심 로직 검증을 위해 유닛 테스트를 도입하며, 모든 AI는 아래의 절차를 따른다.

1.  **PM (Gemini)의 책임:**
    *   **명세 작성:** `spec.md`에 테스트가 필요한 **핵심 로직**과 **테스트 케이스(정상, 경계, 예외 포함)**를 명확히 정의한다.
    *   **최종 검증:** **(A) 유닛 테스트 실행**과 **(B) 소스 코드 리뷰**를 모두 수행하여, 기능의 정확성과 코드 품질을 함께 검증한다.

2.  **구현 (Claude)의 책임:**
    *   **코드 작성:** `spec.md`에 명시된 기능 코드와 유닛 테스트 코드를 함께 작성한다.
    *   **파일 분리:** 모든 테스트 코드는 `tests/` 디렉토리에, 소스 코드와 분리된 별도 파일로 작성한다.

3.  **빌드 시스템의 요구사항:**
    *   빌드 스크립트(`CMakeLists.txt` 등)는 실제 애플리케이션과 테스트 실행 파일을 **별개의 타겟**으로 빌드해야 한다.

## 🚀 기능 추가/변경 제안 규칙 (Feature Proposal Rule)

`spec.md`에 명시되지 않은 기능은 아래 절차를 통해서만 제안하고 구현할 수 있다.

1.  **구현 AI:** 새 기능을 직접 구현하는 대신, `.kb/projects/[프로젝트명]/feature-proposal.md`에 제안서를 작성하고 PM에게 검토를 요청한다.
2.  **PM:** 제안을 검토 후 `승인/보류/거절`을 결정하여 제안서에 기록한다.
3.  **PM (승인 시):** **반드시 `spec.md`를 수정**하여 승인된 기능을 요구사항에 추가한다.
4.  **구현 AI:** `spec.md`가 수정된 것을 확인한 후에만 기능 구현을 시작한다.

## 🚨 에러 처리 및 의사결정 프로토콜 (Error Handling & Decision Protocol)

### 구현 실패 시 대응 (Response to Implementation Failure)
1. **실패 AI**: 실패 원인과 상세한 에러 로그를 `.kb/sessions/[세션명]/error-report.md`에 기록
2. **실패 AI**: 상대 AI에게 자문 요청
3. **자문 AI**: 문제 분석 후 해결 방안을 `.kb/sessions/[세션명]/solution-proposal.md`에 작성
4. **실패 AI**: 자문 AI 제안 방안으로 재시도
5. **재시도 실패 시**: 사용자에게 실패 사실과 파일 경로들 보고 후 결정 요청

### 보안 문제 발생 시 (Response to Security Issue)
1. **감지 AI**: 보안 위험 감지 즉시 작업 중단
2. **감지 AI**: 보안 문제 상세 내용을 `.kb/sessions/[세션명]/security-alert.md`에 기록
3. **감지 AI**: 사용자에게 즉시 보안 위험 경고 및 파일 경로 보고
4. **사용자**: 보안 위험 평가 후 조치 결정

### AI 간 의견 불일치 해결 (Resolving AI Disagreements)
1. **각 AI**: 자신의 의견과 근거를 `.kb/projects/[프로젝트명]/opinion-[ai명].md`에 기록
2. **양측**: 사용자에게 의견 불일치 상황과 파일 경로들 보고
3. **사용자**: 양측 의견 검토 후 최종 결정
4. **결정된 AI**: 사용자 결정 내용을 `.kb/projects/[프로젝트명]/final-decision.md`에 기록

## 🛡️ 보안 및 권한 승인 프로토콜 (Security & Permission Protocol)

### 파일 시스템 접근 권한 (File System Access Permissions)
- **규칙**: AI 에이전트가 파일 시스템 접근, 네트워크 요청 등 민감한 작업을 수행하기 위해 권한 상승을 필요로 하는 경우, 반드시 사용자에게 명시적인 승인을 받아야 함

### Claude 파일 작업 실행 (Executing Claude File Operations)
- **중요**: `claude`가 파일을 생성/수정하도록 지시할 때는, 반드시 `--dangerously-skip-permissions` 플래그를 포함해야 함
- **예시**: `claude -p "피드백을 feedback.md 파일로 작성해줘." --dangerously-skip-permissions`
- **경고**: 이 플래그는 Claude에게 파일 시스템에 대한 직접적인 권한을 부여하므로, 사용 전 항상 사용자에게 목적과 위험성을 설명하고 명시적인 동의를 얻어야 함

## 🚫 금지사항 (Prohibited Actions)

### 하지 말아야 할 것들 (Don'ts)
```
❌ .kb에 사용자 문서 작성
❌ 프로젝트 폴더에 AI 소통 기록 작성  
❌ 중복 문서 생성 (같은 내용 여러 곳)
❌ 모든 세션에 대해 기록 생성 (복잡한 것만)
❌ 파일 수정 시 내용 요약/생략 (항상 완전한 내용으로 업데이트)
```

### 해야 할 것들 (Do's)
```
✅ AI는 자신의 담당 영역에만 문서 작성
✅ 복잡한 작업만 세션 기록
✅ 사용자가 요청할 때만 고급 문서화
✅ **언어 및 인코딩 (UTF-8 통일)**: 모든 **파일명은 영문**으로, **내용은 한글**로 작성합니다. 모든 파일의 **인코딩은 UTF-8**로 통일합니다.
✅ 파일 수정 시 전체 내용으로 교체
✅ README.md는 각 프로젝트 루트에 위치 (다른 사용자 접근성 우선)
```

## 🎯 성공 기준 (Success Criteria)

이 규칙이 성공적으로 작동하는 기준:
1. **명확성 (Clarity)**: 어느 AI가 어떤 문서를 작성할지 즉시 판단 가능
2. **일관성 (Consistency)**: 다른 세션에서도 동일한 구조로 문서 생성
3. **단순성 (Simplicity)**: 사용자가 규칙을 이해하고 예측 가능
4. **실용성 (Practicality)**: AI가 실제로 규칙을 준수할 수 있음
5. **접근성 (Accessibility)**: 다른 사용자가 프로젝트를 쉽게 이해할 수 있음

---

**이 규칙은 모든 AI 협업의 기본 원칙입니다. 작업 시작 전 반드시 확인하세요.**

---

## 🔎 Gemini Fact-Verification Rule (Gemini 사실 검증 규칙)

Gemini는 답변의 신뢰도를 보장하기 위해 아래 규칙을 따른다.

1.  **외부 정보 우선:** 최신 정보, API 등 사실 확인이 필요한 모든 요청에 대해, 내부 지식보다 `google_web_search`를 우선적으로 사용한다.
2.  **내부 지식 근거 제시:** 일반적인 개념을 설명할 경우, 그 근거가 되는 원칙을 함께 제시한다.
3.  **검증 요청 시 검색 필수:** 사용자가 "검색해줘", "확인해줘" 등의 키워드로 요청 시, 반드시 `google_web_search`를 실행한다.