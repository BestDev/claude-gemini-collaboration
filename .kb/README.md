# Knowledge Base (.kb) 가이드

이 폴더는 프로젝트의 모든 중요한 지식을 체계적으로 보존하고 활용하기 위한 Knowledge Base입니다.

## 📁 폴더 구조

### `/adr/` - Architecture Decision Records
**목적**: 아키텍처 및 기술적 결정의 배경과 이유를 기록
**내용**: 
- 기술 스택 선택 이유
- 디자인 패턴 결정
- 라이브러리/프레임워크 선택
- 인프라 구조 결정

**명명 규칙**: `ADR-XXX-결정제목.md`
**예시**: `ADR-001-fastapi-framework-choice.md`

### `/design/` - Core Design Documents  
**목적**: 시스템과 기능의 핵심 설계 문서
**내용**:
- 시스템 아키텍처 다이어그램
- 데이터베이스 스키마 설계
- API 설계 및 명세
- 핵심 비즈니스 로직 플로우
- UI/UX 설계 문서

**명명 규칙**: `YYYY-MM-DD-설계주제.md`
**예시**: `2025-08-13-user-authentication-system.md`

### `/problem-solving/` - Problem-Solving Logs
**목적**: 복잡한 문제 해결 과정과 솔루션 기록
**내용**:
- 버그 해결 과정
- 성능 최적화 과정  
- 기술적 난제 해결 방법
- 트러블슈팅 가이드

**명명 규칙**: `YYYY-MM-DD-문제제목.md`
**예시**: `2025-08-13-cors-configuration-issue.md`

### `/summaries/` - Collaboration Summaries
**목적**: 중요한 협업 세션과 논의 결과 요약
**내용**:
- 일일 협업 세션 요약
- 중요한 미팅 결과
- 기능 개발 과정 요약
- 프로젝트 마일스톤 기록

**명명 규칙**: `YYYY-MM-DD-세션주제.md`
**예시**: `2025-08-13-gemini-claude-collaboration-implementation.md`

## 🔄 사용 워크플로우

### 1. 지식 식별 (Gemini)
- 대화 중 중요한 내용 감지
- 보존 가치가 있는 지식 판단
- 적절한 카테고리 결정

### 2. 지식 저장 (Claude)
- Gemini의 요청에 따라 문서 작성
- 적절한 폴더에 마크다운 형식으로 저장
- 명명 규칙 준수

### 3. 지식 활용 (Both)
- 새 작업 시작 전 관련 문서 검색
- 기존 결정사항과 일관성 유지
- 중복 작업 방지

## 📋 템플릿 사용법

각 폴더에는 `TEMPLATE.md` 파일이 있습니다:
1. 해당 템플릿을 복사
2. 파일명을 명명 규칙에 맞게 변경
3. 내용을 채워넣기

## 🔍 검색 팁

```bash
# 특정 키워드로 KB 전체 검색
grep -r "키워드" .kb/

# 특정 폴더에서 검색
grep -r "API" .kb/design/

# 파일명으로 검색
find .kb/ -name "*인증*"
```

## 📈 KB 품질 관리

- **일관성**: 템플릿 사용으로 문서 구조 통일
- **최신성**: 결정 변경 시 관련 문서 업데이트  
- **연결성**: 관련 문서 간 상호 참조
- **검색성**: 명확한 제목과 태그 사용

---

**📝 이 README는 KB 시스템의 진화와 함께 지속적으로 업데이트됩니다.**