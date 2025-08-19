# Document Consistency Review Guidelines (문서 일관성 검토 가이드라인)

## 🎯 Purpose (목적)

이 문서는 **기존 AI 협업 규칙 문서들의 일관성 검토**를 위한 가이드라인입니다. 

### **핵심 목적:**
- CLAUDE.md, COLLABORATION-RULES.md, GEMINI.md 등 기존 문서에 **추가/수정이 발생했을 때** 
- 다른 세션이나 다른 AI가 **동일한 검토 기준**으로 문서 품질을 확인할 수 있도록
- **구체적인 검토 체크리스트와 자동 검증 방법** 제공

### **적용 시점:**
✅ 규칙 문서 수정 후 일관성 검토 필요 시
✅ 새로운 AI가 기존 문서 품질 점검 시  
✅ 정기적 문서 품질 감사 시

❌ 새 문서 작성 시 (→ COLLABORATION-RULES.md 참조)
❌ 일반 프로젝트 문서 작성 시

## 📋 Core Principles (핵심 원칙)

### 1. **Clarity First (명확성 우선)**
- Claude와 Subagents가 즉시 이해할 수 있는 구체적 기준
- 여러 해석이 가능한 애매한 표현 금지

### 2. **Semantic-Driven Structure (의미 중심 구조)**
- 순차적 섹션: 단계나 우선순위가 있는 경우 번호 사용
- 병렬적 섹션: 독립적이고 동등한 경우 번호 없이 구성
- 내용의 성격이 구조를 결정

### 3. **Intelligent Consistency (지능적 일관성)**
- 의미적 구조를 해치지 않는 선에서 형식 통일
- 시각적 일관성: 제목 형식, 이모지, 코드 블록 등은 모든 문서가 동일
- 우선순위: 내용의 의미 전달 > 형식적 통일성 > 개별 문서 최적화

## 🎯 Abstract Expression Management (추상적 표현 관리)

### **🚫 Problematic Expressions (문제 표현 목록)**

#### **Tier 1: Immediate Fix Required (즉시 수정 필요)**
```markdown
❌ "복잡한" → ✅ "3개 이상 파일 관련" 또는 "5개 이상 시스템 관련"
❌ "적절한" → ✅ "다음 조건 중 하나 해당 시"
❌ "충분한" → ✅ "모든 핵심 로직" 또는 "100% 커버리지"
❌ "자세한" → ✅ "문서화, 가이드, 매뉴얼 키워드 포함"
❌ "많은" → ✅ "10개 이상" 또는 구체적 수치
❌ "빠른" → ✅ "2초 이내" 또는 구체적 성능 기준
```

#### **Tier 2: Context-Dependent (맥락 의존적)**
```markdown
⚠️ "필요시" → ✅ "다음 경우에 한해" + 구체적 조건
⚠️ "가능한" → ✅ "조건이 충족되면" + 구체적 조건
⚠️ "일반적으로" → ✅ "80% 이상의 경우" 또는 구체적 비율
⚠️ "보통" → ✅ "기본값으로" 또는 "기준점으로"
⚠️ "대부분" → ✅ "90% 이상" 또는 구체적 비율
```

#### **Tier 3: Acceptable with Clarification (명확화 필요)**
```markdown
⚡ "중요한" → ✅ 중요한 이유 명시 + 구체적 영향
⚡ "기본적인" → ✅ 기본이 되는 기준 명시
⚡ "핵심적인" → ✅ 핵심 기준 또는 최우선 항목 명시
⚡ "주요한" → ✅ 우선순위나 빈도 기준 명시
```

### **🔍 Detection Methods (감지 방법)**

#### **자동 감지 스크립트:**
```bash
#!/bin/bash
# abstract_expression_checker.sh

echo "=== Tier 1 문제 표현 검색 ==="
grep -n -i "복잡한\|적절한\|충분한\|자세한\|많은\|빠른" *.md
grep -n -i "complex\|appropriate\|sufficient\|detailed\|many\|fast" *.md

echo "=== Tier 2 맥락 의존적 표현 검색 ==="
grep -n -i "필요시\|가능한\|일반적으로\|보통\|대부분" *.md
grep -n -i "if needed\|possible\|generally\|usually\|most" *.md

echo "=== 수치 기준 없는 조건문 ==="
grep -n "경우\|when\|if" *.md | grep -v "[0-9]" | grep -v "다음\|following"

echo "=== 비교급 형용사 (상대적 표현) ==="
grep -n -i "더\|less\|more\|better\|worse\|faster\|slower" *.md
```

#### **수동 검토 체크리스트:**
```markdown
- [ ] 모든 조건문에 구체적 기준이 있는가?
- [ ] 성능 관련 표현에 수치가 포함되어 있는가?
- [ ] "복잡함"의 정의가 측정 가능한가?
- [ ] 시간 관련 표현이 구체적인가?
- [ ] 비교 표현에 명확한 기준점이 있는가?
```

### **🔧 Quantification Strategies (수치화 전략)**

#### **시간 기준 구체화:**
```markdown
❌ "빠르게" → ✅ "2초 이내"
❌ "즉시" → ✅ "500ms 이내" 또는 "사용자 입력 즉시"
❌ "오래" → ✅ "30분 이상" 또는 구체적 시간
❌ "가끔" → ✅ "월 1회 미만" 또는 구체적 빈도
```

#### **복잡도 기준 구체화:**
```markdown
❌ "복잡한 작업" → ✅ "다음 중 하나 이상:
  - 3개 이상 파일 수정
  - 5개 이상 시스템 관련
  - 새로운 기술 스택 도입
  - 30분 이상 예상 작업"
```

#### **품질 기준 구체화:**
```markdown
❌ "충분한 테스트" → ✅ "다음 모든 조건:
  - 핵심 로직 100% 커버리지
  - 경계값 테스트 포함
  - 예외 상황 테스트 포함"
```

### **📋 Concrete Alternative Patterns (구체적 대안 패턴)**

#### **조건문 패턴:**
```markdown
# 대신 사용할 구체적 패턴들

Pattern 1: 수치 기준
"3개 이상 파일을 수정하는 경우"
"응답 시간이 2초를 초과하는 경우"
"메모리 사용량이 512MB를 넘는 경우"

Pattern 2: 체크리스트 기준
"다음 조건 중 하나라도 해당하는 경우:"
"아래 모든 항목을 만족하는 경우:"
"다음 체크리스트를 통과한 경우:"

Pattern 3: 키워드 기준
"'문서화', '가이드', '매뉴얼' 키워드가 포함된 경우"
"사용자가 명시적으로 '상세한', '자세한' 요청을 한 경우"
```

#### **측정 가능한 품질 기준:**
```markdown
# 성능 관련
"빌드 시간 30초 이내"
"테스트 실행 시간 5분 이내"
"응답 시간 2초 이내"

# 코드 품질 관련
"lint 에러 0개"
"테스트 커버리지 90% 이상"
"순환 복잡도 10 이하"

# 문서 품질 관련
"모든 함수에 docstring 존재"
"README.md 5개 섹션 이상"
"예제 코드 실행 가능"
```

### **⚡ Real-time Application (실시간 적용)**

#### **검토 중 발견 시 즉시 적용 절차:**
```markdown
1. 추상적 표현 발견
2. Tier 분류 (1/2/3)
3. 맥락 파악
4. 구체적 대안 선택
5. 수치/조건 기준 추가
6. 측정 가능성 확인
```

#### **팀 내 표준화:**
```markdown
- 새로운 추상적 표현 발견 시 이 목록에 추가
- 구체화 패턴의 재사용성 고려
- 도메인별 특화 기준 개발
- 정기적 업데이트 (월 1회)
```

## 🔍 Document Consistency Checklist (문서 일관성 체크리스트)

### ✅ **1. Title Structure Consistency (제목 구조 일관성)**

#### **English (Korean) Format Rule**
**✅ 올바른 형식:**
```markdown
## 🎯 Core Philosophy: User-Centric Collaboration Model (사용자 중심 협업 모델)
### 📋 Prerequisite: Rule Comprehension (사전 작업: 규칙 숙지)
```

**❌ 잘못된 형식:**
```markdown
## 🎯 사용자 중심 협업 모델 (User-Centric Collaboration Model)  # 한글 우선
## Gemini 주도 워크플로우  # 영문 제목 누락
## 에러 처리 및 의사결정 프로토콜 (Error Handling & Decision Protocol)  # 한글 우선
```

#### **검토 방법:**
```bash
# 모든 제목 구조 확인
grep "^##+ " [파일명].md

# 불일치 패턴 찾기
grep "^##+ [가-힣]" [파일명].md  # 한글로 시작하는 제목들
```

### ✅ **2. Section Numbering Consistency (섹션 번호 매기기 일관성)**

#### **의미적 구분 원칙:**

**📚 Sequential Sections (순차적 섹션) - 번호 필요**
- **Documentation Triggers**: `1. Project Start`, `2. Complex Collaboration`, `3. Advanced Documentation`
- **Mandatory Invocation Triggers**: `1. Complex Requirement Analysis`, `2. Technology Stack Decision`
- **Workflow Steps**: `1. 사용자 요청`, `2. Gemini 분석`, `3. 사용자 승인`

**🔄 Parallel Sections (병렬적 섹션) - 번호 불필요**
- **AI Responsibility Areas**: `Analysis & Planning`, `Implementation & Documentation`
- **Inter-AI Communication**: `File-Based Communication`, `Project Folder Structure`
- **Expert Categories**: `Language Experts`, `Database Experts`, `Project Management Experts`

#### **검토 방법:**
```bash
# 번호가 있는 섹션들 확인
grep "^#### [0-9]" [파일명].md

# 일관성 확인: 같은 레벨 섹션들이 모두 번호를 가지거나 모두 없어야 함
```

### ✅ **3. Emoji Usage Consistency (이모지 사용 일관성)**

#### **주요 섹션 이모지 규칙:**
- **역할/책임**: `👤` `🎭` `🤖`
- **목표/철학**: `🎯` 
- **체크리스트**: `📋`
- **워크플로우**: `🚀` `⚡`
- **문서/참조**: `📚` `📁` `📝`
- **규칙/프로토콜**: `🚨` `🛡️` `⚠️`
- **성공/품질**: `✅` `🔬` `⭐`

#### **검토 방법:**
```bash
# 주요 섹션(##, ###)에 이모지가 있는지 확인
grep "^## [^🎯📋🚀📚🤖👤🔧📁🚨🛡️🚫✅⚠️]" [파일명].md
```

### ✅ **4. Code Block Style Consistency (코드 블록 스타일 일관성)**

#### **표준 형식:**
```markdown
# 올바른 형식 (들여쓰기 없음)
```
사용자 요청 → Gemini 분석&계획 → [사용자 승인] → 
Gemini 명세서 작성 → Claude 구현 → [사용자 검토] → 완료
```

# 잘못된 형식 (들여쓰기 있음)
    ```
    코드 내용
    ```
```

#### **검토 방법:**
```bash
# 들여쓰기가 있는 코드 블록 찾기
grep "^    \`\`\`" [파일명].md

# 모든 코드 블록 위치 확인
grep "^\`\`\`" [파일명].md
```

### ✅ **5. Cross-Reference Consistency (상호 참조 일관성)**

#### **참조 형식 규칙:**
```markdown
# 올바른 참조
`COLLABORATION-RULES.md`의 **"Error Handling & Decision Protocol"** 섹션을 참조하세요.

# 섹션명은 실제 제목과 정확히 일치해야 함
Complex Collaboration 조건 참조
```

#### **검토 방법:**
```bash
# 문서 간 참조 확인
grep "COLLABORATION-RULES\.md\|CLAUDE\.md\|GEMINI\.md" [파일명].md

# 섹션 참조가 실제 존재하는지 확인
grep "Complex Collaboration\|Error Handling" *.md
```

## 📝 Content Quality Review Framework (내용 품질 검토 프레임워크)

### ✅ **1. Duplication Detection & Resolution (중복 감지 및 해결)**

#### **중복 식별 방법:**
```bash
# 같은 개념을 다루는 섹션들 찾기
grep -n "에러 처리\|Error Handling" *.md
grep -n "폴더 구조\|Folder Structure" *.md
grep -n "문서 표준\|Document Standards" *.md
```

#### **해결 우선순위 규칙:**
1. **COLLABORATION-RULES.md 우선**: 공통 규칙은 여기에 보관, 다른 문서는 참조
2. **구체적 > 추상적**: 상세한 규칙이 일반적 규칙보다 우선
3. **최신 > 과거**: 가장 최근에 수정된 버전을 기준으로 통일
4. **사용 빈도 우선**: 여러 문서에서 참조하는 내용을 기준점으로 설정

#### **중복 해결 절차:**
```markdown
1. 중복 내용 식별 → 2. 우선순위 규칙 적용 → 3. 보존할 위치 결정 → 4. 다른 위치는 참조로 교체
```

### ✅ **2. Ambiguity Assessment (애매모호성 평가)**

#### **문제가 되는 주관적 표현들:**
```markdown
❌ "복잡한 작업"          → ✅ "3개 이상 파일 수정" 또는 "5개 이상 시스템 관련"
❌ "적절한 시점"          → ✅ "다음 조건 중 하나 해당 시"
❌ "충분한 테스트"        → ✅ "모든 핵심 로직에 대한 단위 테스트"
❌ "자세한 문서"          → ✅ "문서화, 가이드, 매뉴얼 키워드 포함 시"
❌ "성능 문제"            → ✅ "응답 시간 2초 이상" 또는 "메모리 사용량 512MB 이상"
```

#### **애매모호함 감지 방법:**
```bash
# 주관적 표현 검색
grep -i "복잡한\|적절한\|충분한\|자세한\|많은\|빠른\|느린" *.md
grep -i "complex\|appropriate\|sufficient\|detailed\|many\|fast\|slow" *.md

# 수치 기준이 없는 조건문 찾기
grep "경우\|when\|if" *.md | grep -v "[0-9]"
```

### ✅ **3. Logical Consistency Check (논리적 일관성 체크)**

#### **체크해야 할 논리적 모순 유형:**

**상호 모순 규칙:**
```bash
# 같은 조건에 대한 다른 지시사항 찾기
grep -A3 -B3 "Complex Collaboration" *.md
grep -A3 -B3 "문서 생성" *.md
```

**순환 참조:**
```bash
# A→B, B→A 참조 관계 확인
grep "CLAUDE.md.*COLLABORATION" *.md
grep "COLLABORATION.*CLAUDE.md" *.md
```

**전제 조건 위반:**
```markdown
예시: "파일 기반 소통"을 원칙으로 하면서 "구두 지시" 허용하는 경우
체크: 기본 원칙과 세부 규칙이 상충하지 않는지 확인
```

#### **일관성 검증 체크리스트:**
- [ ] 같은 조건에 대한 지시사항이 문서 간 일치하는가?
- [ ] 전제 조건과 세부 규칙이 모순되지 않는가?
- [ ] 용어 정의가 문서 전체에서 일관되게 사용되는가?
- [ ] 순환 참조나 무한 루프 구조가 없는가?

### ✅ **4. Rule Compliance Verification (규칙 준수 검증)**

#### **핵심 규칙 위반 패턴:**
```bash
# 파일명 규칙 위반 (한글 파일명)
find . -name "*[가-힣]*" -type f

# 인코딩 규칙 체크
file *.md | grep -v "UTF-8"

# 영문 우선 제목 규칙 위반
grep "^## [가-힣]" *.md
```

#### **메타 규칙 체크:**
- **완전성**: 모든 시나리오에 대한 규칙이 존재하는가?
- **실행 가능성**: AI가 실제로 따를 수 있는 구체적 규칙인가?
- **측정 가능성**: 규칙 준수 여부를 객관적으로 판단할 수 있는가?

## 🔧 Systematic Review Process (체계적 검토 프로세스)

### **Step 1: Automated Structure Analysis**
```bash
# 1. 모든 제목 구조 추출
grep "^##+ " [파일명].md > titles_check.txt

# 2. 영문(한글) 형식 위반 찾기
grep "^##+ [가-힣]" [파일명].md

# 3. 번호 매기기 패턴 확인
grep "^#### [0-9]" [파일명].md
```

### **Step 2: Manual Semantic Review**
1. **섹션 성격 분석**: 순차적(번호 필요) vs 병렬적(번호 불필요)
2. **이모지 의미 확인**: 섹션 내용과 이모지가 일치하는가
3. **상호 참조 검증**: 참조된 섹션이 실제 존재하는가

### **Step 3: Consistency Validation**
1. **형식 통일성**: 모든 문서가 동일한 패턴을 따르는가
2. **내용 연결성**: 문서 간 참조가 올바르게 연결되어 있는가
3. **의미적 일관성**: 같은 개념이 다른 용어로 표현되지 않았는가

## 📊 Common Issues and Solutions (일반적 문제와 해결책)

### **Issue 1: Mixed Title Format**
**문제**: `## 한글 제목 (English Title)` 형식
**해결**: `## English Title (한글 제목)` 형식으로 통일

### **Issue 2: Inconsistent Numbering**
**문제**: 같은 성격의 섹션 중 일부만 번호 사용
**해결**: 순차적 섹션은 모두 번호, 병렬적 섹션은 모두 번호 제거

### **Issue 3: Missing Emojis**
**문제**: 주요 섹션에 이모지 누락으로 시각적 일관성 저해
**해결**: 섹션 성격에 맞는 적절한 이모지 추가

### **Issue 4: Broken Cross-References**
**문제**: 참조된 섹션명이 실제 제목과 다름
**해결**: 참조 대상의 정확한 제목으로 수정

## 🎯 Quality Metrics (품질 지표)

### **완벽한 일관성 달성 기준:**
- [ ] **Title Format**: 100% English (Korean) 형식
- [ ] **Section Numbers**: 의미적 구분에 따른 정확한 번호 사용
- [ ] **Emoji Usage**: 모든 주요 섹션에 적절한 이모지
- [ ] **Code Blocks**: 들여쓰기 없는 통일된 형식
- [ ] **Cross-References**: 모든 참조가 정확하게 연결됨

### **측정 가능한 일관성 지표:**
1. **형식 일치율**: (올바른 형식 섹션 수 / 전체 섹션 수) × 100%
2. **참조 정확도**: (올바른 참조 수 / 전체 참조 수) × 100%
3. **이모지 적용률**: (이모지가 있는 주요 섹션 수 / 전체 주요 섹션 수) × 100%

## 🤖 AI-Specific Review Guidelines (AI별 검토 가이드라인)

### **🔍 Session Type Detection (세션 유형 감지)**

#### **메인 세션 AI 판별 방법:**
```bash
# 1. 명시적 세션 시작 패턴 확인
grep -i "claude.*주도\|gemini.*주도\|claude.*led\|gemini.*led" *.md

# 2. 역할 키워드로 판단
grep -i "구현가\|implementer\|PM\|architect\|관리자" *.md

# 3. 첫 번째 작업 지시자로 판단
who_starts=$(grep -n "\[.*\].*요청\|\[.*\].*분석" *.md | head -1)
```

#### **세션 유형별 특징:**
- **Claude-led**: 즉시 구현, Subagents 활용, 품질 검증 중심
- **Gemini-led**: 분석→설계→명세→Claude 지시 순서
- **Multi-AI**: 역할 분담 명확화, 상호 검토 필수

### **🎯 Claude-led Session Guidelines (Claude 주도 세션 가이드라인)**

#### **Claude 특화 검토 항목:**
```markdown
✅ Subagents System 관련:
- [ ] 13개 전문가 에이전트 목록이 정확한가?
- [ ] 선택 기준이 우선순위 순서대로 정리되어 있는가?
- [ ] Combination Rules가 명확한가?

✅ Immediate Execution 관련:
- [ ] "즉시 실행" 조건이 구체적으로 명시되어 있는가?
- [ ] Gemini 호출 시점이 수치 기준으로 정의되어 있는가?

✅ Quality Assurance 관련:
- [ ] lint, test, build 검증 절차가 상세한가?
- [ ] 에러 처리 프로토콜 참조가 정확한가?
```

#### **Claude 세션 검토 프로세스:**
```bash
# 1. Subagent 정보 정확성 체크
grep -A5 -B5 "python-expert\|cpp-expert\|unity-expert" CLAUDE.md

# 2. 호출 조건 수치 확인
grep "[0-9].*개\|[0-9].*분\|[0-9].*파일" CLAUDE.md

# 3. 품질 검증 단계 확인
grep -i "lint\|test\|build" CLAUDE.md
```

### **🚀 Gemini-led Session Guidelines (Gemini 주도 세션 가이드라인)**

#### **Gemini 특화 검토 항목:**
```markdown
✅ Requirement Analysis 관련:
- [ ] 요구사항 분석 절차가 체계적인가?
- [ ] 사용자 승인 단계가 명확히 포함되어 있는가?

✅ Architecture Design 관련:
- [ ] 설계 과정이 단계별로 정의되어 있는가?
- [ ] 기술 스택 결정 기준이 명확한가?

✅ Specification Writing 관련:
- [ ] spec.md 형식이 COLLABORATION-RULES.md와 일치하는가?
- [ ] Claude 지시 방법이 파일 기반으로 명시되어 있는가?
```

#### **Gemini 세션 워크플로우 검증:**
```bash
# 1. 7단계 워크플로우 완전성 체크
grep -n "\[사용자\]\|\[Gemini\]\|\[Claude\]" GEMINI.md | wc -l  # 7개여야 함

# 2. 승인 단계 존재 확인
grep "승인\|검토\|approval\|review" GEMINI.md

# 3. 파일 기반 지시 확인
grep "spec\.md\|파일.*전달" GEMINI.md
```

### **🔄 Multi-AI Collaboration Guidelines (다중 AI 협업 가이드라인)**

#### **협업 세션 특화 검토:**
```markdown
✅ Role Separation 관련:
- [ ] AI별 담당 영역이 중복 없이 정의되어 있는가?
- [ ] Direct Storage 규칙이 일관되게 적용되어 있는가?

✅ Communication Protocol 관련:
- [ ] 파일 기반 소통 규칙이 모든 AI에게 적용되는가?
- [ ] 상호 검토 절차가 명확한가?

✅ Conflict Resolution 관련:
- [ ] AI 간 의견 불일치 해결 프로토콜이 상세한가?
- [ ] 최종 결정권자가 명확한가?
```

### **🎛️ AI-Agnostic Universal Guidelines (AI 무관 공통 가이드라인)**

#### **모든 AI가 따라야 할 기본 원칙:**
```markdown
1. **Documentation First**: 규칙 문서 우선 참조
2. **File-Based Communication**: 모든 지시는 파일 경로 기반
3. **UTF-8 Encoding**: 파일명 영문, 내용 한글, 인코딩 UTF-8
4. **Error Protocol**: 실패 시 즉시 프로토콜 따름
5. **User Reporting**: 주요 결정사항 사용자 보고
```

#### **공통 검토 체크리스트:**
- [ ] COLLABORATION-RULES.md를 최신 버전으로 확인했는가?
- [ ] 해당 AI의 특화 문서(CLAUDE.md/GEMINI.md)를 참조했는가?
- [ ] 파일 기반 소통 원칙을 준수하고 있는가?
- [ ] UTF-8 인코딩 및 파일명 규칙을 따르고 있는가?
- [ ] 에러 발생 시 처리 프로토콜을 숙지하고 있는가?

## 🚀 Implementation Guidelines (구현 가이드라인)

### 📋 Step-by-Step Application Process (단계별 적용 프로세스)

#### **Phase 1: Structure Check (구조 검사)**
```bash
# 1. 제목 형식 확인
grep "^##+ " [파일명].md | grep -v "^##+ [A-Z].*([가-힣].*)"

# 2. 이모지 누락 확인  
grep "^## [^🎯📋🚀📚🤖👤🔧📁🚨🛡️🚫✅⚠️]" [파일명].md

# 3. 번호 매기기 일관성 확인
grep "^#### [0-9]" [파일명].md
```

#### **Phase 2: Content Quality (내용 품질)**
```bash
# 1. 중복 내용 감지
grep -n "에러 처리\|Error Handling" *.md
grep -n "폴더 구조\|Folder Structure" *.md

# 2. 추상적 표현 감지
grep -i "복잡한\|적절한\|충분한\|자세한\|많은\|빠른" *.md

# 3. 논리적 일관성 체크
grep -A3 -B3 "Complex Collaboration" *.md
```

#### **Phase 3: Cross-Reference Validation (상호 참조 검증)**
```bash
# 1. 문서 간 참조 확인
grep "COLLABORATION-RULES\.md\|CLAUDE\.md\|GEMINI\.md" [파일명].md

# 2. 섹션 참조 정확성 확인
grep "Complex Collaboration\|Error Handling" *.md
```

#### **Phase 4: Final Validation (최종 검증)**
- [ ] 7-Point Compliance Checklist 전체 확인
- [ ] 자동 스크립트 실행 결과 0개
- [ ] 수동 검토 항목 모두 통과
- [ ] 동료 AI 크로스체크 (가능한 경우)

### 🔍 Verification Checklist (검증 체크리스트)

#### **자동 검증 스크립트:**
```bash
#!/bin/bash
# doc_consistency_checker.sh

echo "=== Phase 1: Structure Check ==="
echo "1. 제목 형식 위반:"
grep "^##+ [가-힣]" *.md || echo "   ✅ 모든 제목이 영문 우선 형식"

echo "2. 이모지 누락:"
grep "^## [^🎯📋🚀📚🤖👤🔧📁🚨🛡️🚫✅⚠️]" *.md || echo "   ✅ 모든 주요 섹션에 이모지 있음"

echo "=== Phase 2: Content Quality ==="
echo "3. Tier 1 추상적 표현:"
grep -i "복잡한\|적절한\|충분한\|자세한\|많은\|빠른" *.md || echo "   ✅ Tier 1 문제 표현 없음"

echo "4. 중복 섹션:"
duplicates=$(grep -h "^##+ " *.md | sort | uniq -d)
if [ -z "$duplicates" ]; then
    echo "   ✅ 중복 제목 없음"
else
    echo "   ❌ 중복 제목 발견: $duplicates"
fi

echo "=== Phase 3: Cross-Reference ==="
echo "5. 잘못된 참조:"
grep -n "참조" *.md | while read line; do
    ref=$(echo "$line" | grep -o '"[^"]*"')
    if [ ! -z "$ref" ]; then
        actual_section=$(grep "$ref" *.md)
        if [ -z "$actual_section" ]; then
            echo "   ❌ 잘못된 참조: $line"
        fi
    fi
done

echo "=== 검증 완료 ==="
```

### 🎯 AI-Specific Implementation (AI별 구현 방법)

#### **For Claude & Subagents:**
1. **사전 검토**: 문서 수정 전 반드시 이 가이드라인과 CLAUDE.md 확인
2. **Subagent 활용**: 언어별/도메인별 전문가 적극 활용
3. **즉시 실행**: 복잡성 판단 후 적절한 Gemini 호출 또는 직접 구현
4. **품질 검증**: 4단계 프로세스 순차 실행
5. **결과 보고**: 사용된 Subagents 목록 포함하여 완료 보고

#### **For Gemini & Planning AIs:**
1. **분석 우선**: 웹 검색 활용한 최신 정보 기반 분석
2. **명세 작성**: COLLABORATION-RULES.md 형식 엄격 준수
3. **사용자 승인**: 주요 설계 결정 시 반드시 사용자 승인 획득
4. **파일 기반 지시**: Claude에게 파일 경로 기반으로 명확한 작업 지시
5. **검증 책임**: 4단계 프로세스로 최종 결과물 품질 검증

#### **For Other AI Systems:**
1. **세션 타입 감지**: 메인 AI 판별 후 해당 가이드라인 적용
2. **가이드라인 우선**: 개별 판단보다는 이 문서의 기준을 엄격히 적용
3. **의문사항 보고**: 가이드라인에 명시되지 않은 경우 사용자에게 문의
4. **결과 문서화**: 검토 결과와 수정사항을 명확히 기록
5. **메타데이터 포함**: .kb 문서 작성 시 요청자/작성자/목적 명시

## 📚 Reference Examples (참조 예시)

### **Perfect Example (완벽한 예시):**
```markdown
## 🎯 Core Philosophy: User-Centric Collaboration Model (사용자 중심 협업 모델)

### ✅ Automatic Creation (자동 생성) - 반드시 만들어야 함

#### 1. Project Start (프로젝트 시작 시)
#### 2. Complex Collaboration (복잡한 협업 세션 시)
#### 3. Advanced Documentation Request (고급 문서화 요청 시)

### 📝 Optional Creation (선택적 생성) - 요청 시에만
```

### **Common Mistakes (일반적 실수):**
```markdown
## 사용자 중심 협업 모델 (User-Centric Collaboration Model)  # ❌ 한글 우선
## Gemini 주도 워크플로우  # ❌ 영문 제목 누락
#### Project Start (프로젝트 시작 시)  # ❌ 번호 없음 (순차적 섹션인데)
## Error Handling Protocol  # ❌ 이모지 누락
```

---

## ⚠️ Critical Success Factors (핵심 성공 요인)

### **🎯 Primary Objective (최우선 목표)**

**모든 AI가 규칙을 확실하고 정확히 이해하고 실수하지 않게 하는 것**

이 가이드라인의 존재 이유는 단 하나입니다: Claude, Gemini, 그리고 모든 Subagents가 **혼동 없이**, **오해 없이**, **일관되게** 협업 규칙을 적용할 수 있도록 하는 것입니다.

### **📋 7-Point Compliance Checklist (7가지 기준 준수 체크리스트)**

모든 문서 검토 시 반드시 확인해야 할 7가지 핵심 기준:

#### **1. ✅ Rule Compliance & Contradiction Check (규칙 준수 및 모순 체크)**
- [ ] 모든 규칙이 COLLABORATION-RULES.md와 일치하는가?
- [ ] 논리적 모순이나 상호 충돌하는 지시사항이 없는가?
- [ ] 전제 조건과 세부 규칙이 일관되는가?

#### **2. ✅ Duplication Resolution (중복 해결)**
- [ ] 중복된 내용을 식별하고 우선순위 규칙을 적용했는가?
- [ ] COLLABORATION-RULES.md를 기준점으로 설정했는가?
- [ ] 다른 위치의 중복 내용을 적절한 참조로 교체했는가?

#### **3. ✅ Abstract Expression Elimination (추상적 표현 제거)**
- [ ] Tier 1 문제 표현(복잡한, 적절한, 충분한 등)을 모두 구체화했는가?
- [ ] 모든 조건문에 측정 가능한 기준이 포함되어 있는가?
- [ ] 수치나 체크리스트 기반의 명확한 대안을 제시했는가?

#### **4. ✅ English-First Keyword Structure (영문 우선 키워드 구조)**
- [ ] 모든 주요 섹션이 "English (Korean)" 형식을 따르는가?
- [ ] 빠른 스캔과 이해를 위한 영문 키워드가 적절히 배치되어 있는가?
- [ ] 일관된 영문 용어를 사용하고 있는가?

#### **5. ✅ Clarity & Conciseness (명확성 및 간결성)**
- [ ] 핵심 내용이 혼동 없이 명확하게 표현되어 있는가?
- [ ] 불필요한 장황함 없이 간결하게 작성되어 있는가?
- [ ] 오해의 여지가 없는 구체적 지시사항인가?

#### **6. ✅ AI Understanding Optimization (AI 이해도 최적화)**
- [ ] Claude와 Subagents가 즉시 실행할 수 있는 구체적 기준인가?
- [ ] 판단이 어려운 주관적 표현이 제거되어 있는가?
- [ ] 실수를 방지하는 명확한 가이드라인이 제공되어 있는가?

#### **7. ✅ Multi-AI Compatibility (다중 AI 호환성)**
- [ ] Claude 외 다른 AI도 적용할 수 있는 범용적 규칙인가?
- [ ] 세션 타입별(Claude-led, Gemini-led, Multi-AI) 특화 가이드라인이 있는가?
- [ ] AI 무관 공통 원칙이 명확히 정의되어 있는가?

### **🚀 Implementation Priority (구현 우선순위)**

1. **Immediate (즉시)**: Tier 1 추상적 표현 제거
2. **High (높음)**: 영문(한글) 형식 통일 
3. **Medium (중간)**: 중복 내용 정리
4. **Low (낮음)**: 이모지 및 시각적 일관성

### **⭐ Success Metrics (성공 지표)**

**완벽한 가이드라인 달성 기준:**
- **이해도**: AI가 추가 설명 없이 바로 적용 가능 (100%)
- **일관성**: 모든 세션에서 동일한 결과 도출 (100%)  
- **정확성**: 실수나 오해로 인한 재작업 없음 (0%)
- **효율성**: 검토 시간 50% 단축
- **재사용성**: 다른 프로젝트에도 즉시 적용 가능

**최종 목표**: 문서 구조 자체에서 규칙의 의도를 읽어낼 수 있는 **의미를 담은 구조화** 달성

---

**🎯 Remember: 이 가이드라인은 AI 협업 문서의 최우선 기준입니다. 모든 AI는 문서 작업 시 반드시 이 7가지 기준을 적용하여 규칙을 확실하고 정확히 이해하고 실수하지 않게 해야 합니다.**