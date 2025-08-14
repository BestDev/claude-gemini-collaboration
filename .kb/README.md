# Knowledge Base (KB) 사용 가이드

## 개요
이 디렉토리는 Claude Code와 Gemini CLI 간의 협업 과정에서 생성되는 모든 지식과 경험을 체계적으로 보존하고 관리하는 공간입니다.

## 폴더 구조

### 📋 ADR (Architecture Decision Records)
**경로**: `.kb/adr/`
**목적**: 중요한 기술적 결정사항과 그 배경을 기록
**예시**: ADR-001-user-centered-collaboration.md

### 🏗️ Design (설계 문서)
**경로**: `.kb/design/`
**하위 구조**:
- `api-specs/`: API 명세서
- `database/`: 데이터베이스 스키마 설계
- `architecture/`: 시스템 아키텍처 문서

### 🔄 Workflows (워크플로우)
**경로**: `.kb/workflows/`
**하위 구조**:
- `project-types/`: 프로젝트 유형별 가이드라인
- `templates/`: 협업용 템플릿들

### 🔧 Problem Solving (문제 해결)
**경로**: `.kb/problem-solving/`
**하위 구조**:
- `bugs/`: 버그 수정 과정 기록
- `performance/`: 성능 최적화 기록

### 📝 Sessions (세션 기록)
**경로**: `.kb/sessions/`
**하위 구조**:
- `daily/`: 일일 작업 세션 기록
- `milestones/`: 주요 마일스톤 달성 기록

### 📋 Templates (템플릿)
**경로**: `.kb/templates/`
**목적**: 다양한 문서 작성을 위한 표준 템플릿

## 문서 명명 규칙

### ADR (Architecture Decision Records)
```
ADR-[번호]-[제목].md
예: ADR-001-user-centered-collaboration.md
```

### 일반 문서
```
YYYY-MM-DD-[주제].md
예: 2025-08-14-stripe-integration.md
```

### 프로젝트별 문서
```
[프로젝트명]-[문서타입]-[상세].md
예: payment-module-api-spec.md
```

## 자동 문서화 트리거

### 즉시 문서화
- ✅ 중요한 아키텍처 결정
- ✅ 주요 기술 스택 선택
- ✅ 보안 관련 결정사항

### 세션 종료 시
- ✅ 일일 작업 요약
- ✅ 주요 결정사항 정리
- ✅ 다음 단계 계획

### 마일스톤 달성 시
- ✅ 전체 진행 상황 요약
- ✅ 학습된 점 정리
- ✅ 개선사항 도출

### 문제 해결 완료 시
- ✅ 문제 분석 과정
- ✅ 해결 방법 및 결과
- ✅ 예방 조치 방안

## 사용 방법

### 1. 새로운 프로젝트 시작 시
```bash
# 관련 문서 검색
grep -r "similar-technology" .kb/
# 또는 Gemini CLI 활용
echo ".kb 폴더에서 [기술명] 관련 문서를 찾아주세요" | gemini
```

### 2. 의사결정 시
```bash
# ADR 템플릿 사용
cp .kb/templates/adr-template.md .kb/adr/ADR-XXX-new-decision.md
```

### 3. 세션 시작 시  
```bash
# 세션 로그 템플릿 사용
cp .kb/templates/session-log-template.md .kb/sessions/daily/$(date +%Y-%m-%d)-session.md
```

### 4. 명세서 작성 시
```bash
# 명세서 템플릿 사용
cp .kb/templates/specification-template.md work-specification.md
```

## 검색 및 활용

### 키워드 검색
```bash
# 특정 기술이나 문제에 대한 과거 경험 검색
grep -r "authentication" .kb/
grep -r "performance" .kb/problem-solving/
```

### 유형별 검색
```bash
# ADR에서 특정 결정 검색
grep -r "database" .kb/adr/

# 워크플로우에서 프로젝트 유형 확인
ls .kb/workflows/project-types/
```

### Gemini CLI 활용 검색
```bash
echo ".kb 폴더에서 '결제 시스템' 관련 모든 문서를 요약해주세요" | gemini
```

## 품질 관리

### 문서 품질 기준
- ✅ 명확하고 구체적인 제목
- ✅ 날짜와 작성자 정보 포함
- ✅ 구조화된 내용 (헤딩, 리스트 활용)
- ✅ 실행 가능한 정보 포함

### 정기 점검 (주간)
- ✅ 중복 문서 정리
- ✅ 오래된 정보 업데이트
- ✅ 링크 유효성 검사
- ✅ 카테고리 재분류

### 보관 정책
- **활성 문서**: 현재 프로젝트 관련 (무제한 보관)
- **참고 문서**: 과거 프로젝트 관련 (1년 보관 후 아카이브)
- **임시 문서**: 실험적 내용 (3개월 후 검토)

## 협업 가이드

### Gemini CLI의 역할
- 📝 문서 초안 작성
- 🔍 기존 문서 검색 및 분석  
- 📊 경향 분석 및 인사이트 제공
- ✍️ 문서 스타일 개선

### Claude Code의 역할
- 💾 파일 생성 및 저장
- 🗂️ 폴더 구조 관리
- 🔗 문서 간 링크 생성
- 🔄 자동화 스크립트 실행

### 사용자의 역할
- ✅ 최종 승인 및 검토
- 🎯 우선순위 및 방향성 결정
- 📋 품질 기준 설정
- 🔄 정기 점검 지시

---

**이 Knowledge Base는 살아있는 문서입니다. 지속적인 업데이트와 개선을 통해 협업의 질을 높여나가세요.**