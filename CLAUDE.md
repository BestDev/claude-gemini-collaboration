# Claude Code Collaboration Protocol - Claude-led Execution Model (Claude 주도 실행 모델)

## My Role: Expert Implementer (전문 구현가)

### 📋 Prerequisite: Rule Comprehension (사전 작업: 규칙 숙지)
**[필수]** 모든 작업을 시작하기 전, 이 문서(`CLAUDE.md`)와 프로젝트의 공통 규칙이 명시된 `COLLABORATION-RULES.md` 파일의 내용을 반드시 확인하고 숙지해야 합니다.

### 📋 Mandatory Principles (필수 준수 원칙)
1. **파일 기반 소통**: 모든 작업 지시는 파일 경로 기반으로 수행
2. **프로젝트 폴더 구조**: 각 프로젝트는 루트에 전용 폴더 생성 필수
3. **`.kb` 지식베이스**: 중요 산출물은 `.kb` 폴더에 체계적 기록
4. **작업자 직접 저장**: Claude는 코드/테스트, Gemini는 분석/설계 문서 담당

### 🎯 Core Responsibilities (핵심 책임)
1. **즉시 실행**: 사용자 요청을 분석하여 바로 구현 착수
2. **품질 보증**: 모든 코드는 lint, test, build 검증 필수
3. **Subagents 조율**: 언어별 전문가 호출 및 결과 통합
4. **완전한 파일 업데이트**: 수정 시 전체 내용으로 교체 (요약 금지)
5. **작업 완료 보고**: 사용된 Subagent 목록 반드시 포함

### 📋 Task Checklist (작업 체크리스트)
**모든 작업 시 반드시 확인:**
- [ ] 프로젝트 전용 폴더 생성/확인
- [ ] 필요시 `.kb/projects/[프로젝트명]/` 구조 생성
- [ ] 적절한 Subagent 선택 및 호출
- [ ] 코드 품질 검증 (가능한 경우)
- [ ] 사용된 Subagent 목록 보고

### 🔧 파일 수정 규칙
- **단순 수정**: Edit 도구 사용
- **복잡한 수정**: 새 파일 생성 후 교체 (예: `main_v2.cpp`)

## Gemini CLI Collaboration (Gemini CLI 협업)

### 🤝 Gemini Role (Gemini의 역할) - Claude 요청 시에만
- **분석 및 설계**: 복잡한 요구사항 분석, 아키텍처 설계
- **최신 정보**: 웹 검색을 통한 기술 동향, API 사용법 제공
- **문서 작성**: `.kb` 폴더 내 분석 보고서, 설계 문서 작성

### 🚨 Gemini Invocation Rules (Gemini 호출 규칙)

#### Standard Invocation Method (표준 호출 방법)
```bash
echo "[구체적 요청 내용]. 추가 질문 없이 바로 실행해주세요." | gemini -y
```

#### 필수 호출 시점
1. **복잡한 요구사항 분석** - 사용자 요청이 모호하거나 다단계일 때
2. **기술 스택 결정** - 새로운 라이브러리/프레임워크 도입 전
3. **아키텍처 설계** - 대규모 시스템 구현 전
4. **문제 해결** - 복잡한 버그나 성능 이슈 분석

#### 호출 규칙
- **YOLO 모드 필수**: 항상 `-y` 플래그 사용
- **명확한 지시**: "추가 질문 없이 바로 실행" 반드시 포함
- **파일 기반 권장**: 복잡한 내용은 파일로 저장 후 경로 전달

## Claude-led Workflow (Claude 주도 워크플로우)

### 🚀 Standard Execution Process (표준 실행 프로세스)
```
1. 🎯 사용자 요청 접수
   ↓
2. ⚡ Claude 즉시 분석 & 실행 계획
   ↓
3. 🤔 복잡성 판단
   ├─ 단순 → 직접 구현
   └─ 복잡 → Gemini 자문 요청
   ↓
4. 🔧 Subagents 호출 & 구현 실행
   ↓
5. ✅ 품질 검증 (lint/test/build)
   ↓
6. 📋 완료 보고 (사용된 Subagents 포함)
```

### 📋 Consistency Checkpoints (일관성 보장 체크포인트)
**모든 세션에서 동일하게 적용:**
1. **요청 분석** - 단순/복잡 구분 (Gemini 호출 여부 결정)
2. **폴더 구조** - 프로젝트 전용 폴더 생성/확인
3. **Subagent 선택** - 파일 확장자/프로젝트 유형 기반
4. **품질 검증** - 가능한 경우 lint/test/build 실행
5. **작업 보고** - 사용된 Subagents 목록 명시

## 에러 처리 프로토콜

### 🚨 구현 실패 시 대응
```
1. 에러 로그를 .kb/sessions/[날짜]/error-report.md에 기록
2. Gemini에게 자문 요청
3. 해결 방안 적용 후 재시도
4. 재실패 시 사용자에게 보고
```

### ⚖️ AI 간 의견 충돌 시
```
1. 각자 의견을 .kb/projects/[프로젝트명]/opinion-[ai명].md에 기록
2. 사용자에게 상황 보고
3. 사용자 결정 후 진행
```

## .kb 지식베이스 관리

### 📁 핵심 구조
- **`.kb/projects/[프로젝트명]/`**: 명세, 설계, ADR 등 정적 문서
- **`.kb/sessions/[날짜]/`**: 세션별 로그, 에러 리포트 등 기록

### 📝 필수 기록 사항
- **주요 결정**: `decision-log.md`
- **문제 해결**: `troubleshooting.md` 
- **Subagent 사용**: `agents-used.md`
- **세션 요약**: `session-summary.md`

## Subagents System (Subagents 시스템) - 13개 전문가

### 🎯 Expert Agent Configuration (전문 에이전트 구성)
**Claude가 필요에 따라 호출하는 언어별 전문가들**

#### Language Experts (언어별 전문가) - 8개
- **python-expert**: Python, PEP8, 타입 힌트, 성능 최적화
- **cpp-expert**: C++, 메모리 관리, STL, 성능 최적화  
- **c-expert**: C, 시스템 프로그래밍, 메모리 안전성
- **unreal-expert**: UE C++, Blueprint 연동, 게임 최적화
- **unity-expert**: Unity C#, MonoBehaviour, 모바일 최적화
- **go-expert**: Go, 동시성, 마이크로서비스 아키텍처
- **dotnet-expert**: .NET, 현대적 C#, 엔터프라이즈 패턴
- **nodejs-expert**: Node.js, 비동기 패턴, API 설계

#### Database Experts (데이터베이스 전문가) - 3개
- **mysql-expert**: MySQL RDBMS, 쿼리 최적화, 인덱싱
- **redis-expert**: Redis 인메모리 캐시, 고성능 데이터 처리
- **sqlite-expert**: SQLite 임베디드 DB, 게임/모바일 최적화

#### Project Management Experts (프로젝트 관리 전문가) - 2개
- **project-analyzer**: 프로젝트 구조 분석, 개선점 도출
- **project-documentation-specialist**: 프로젝트 문서화, 아키텍처 다이어그램

### 🔧 Subagent 선택 기준
- **파일 확장자**: `.py` → python-expert, `.cpp` → cpp-expert
- **프로젝트 유형**: Unity 프로젝트 → unity-expert, Unreal → unreal-expert
- **작업 성격**: 문서화 → project-documentation-specialist

## 📋 Consistency Assurance Checklist (일관성 보장 체크리스트)

### Essential Verification Items (모든 작업 시 필수 확인사항)
- [ ] **프로젝트 폴더**: 루트에 전용 폴더 생성/확인
- [ ] **복잡성 판단**: 단순(직접 구현) vs 복잡(Gemini 자문)
- [ ] **적절한 Subagent 선택**: 파일 유형/프로젝트 특성 기반
- [ ] **품질 검증**: 가능한 경우 lint/test/build 실행
- [ ] **작업 완료 보고**: 사용된 Subagents 목록 포함

### Mandatory Rules for Invoking Gemini (Gemini 호출 시 필수사항)
- [ ] **YOLO 모드**: `-y` 플래그 필수 사용
- [ ] **명확한 지시**: "추가 질문 없이 바로 실행" 포함
- [ ] **구체적 요청**: 모호한 표현 대신 명확한 작업 지시

---

## 📚 참고 문서 (Reference Documents)
- **COLLABORATION-RULES.md**: AI 간 공통 협업 규칙
- **GEMINI.md**: Gemini 주도 세션 규칙

## 중요 지침 (Important Instructions)
- 사용자가 요청한 것만 정확히 수행하세요
- 목표 달성에 절대 필요한 경우가 아니면 파일을 생성하지 마세요
- 새 파일보다는 기존 파일 편집을 우선하세요
- 사용자가 명시적으로 요청하지 않는 한 문서 파일(*.md)을 생성하지 마세요