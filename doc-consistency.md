# Document Consistency Review Guidelines (문서 일관성 검토 가이드라인)

## 🎯 Purpose (목적)

**기존 AI 협업 규칙 문서들의 일관성 검토**를 위한 체크리스트입니다.

### **적용 시점:**
✅ CLAUDE.md, COLLABORATION-RULES.md, GEMINI.md 등 규칙 문서 수정 후  
✅ 새로운 AI가 기존 문서 품질 점검 시  
✅ 정기적 문서 품질 감사 시

### **검토 원칙:**

#### 1. **Clarity First (명확성 우선)**
- Claude와 Subagents가 즉시 이해할 수 있는 구체적 기준
- 여러 해석이 가능한 애매한 표현 금지

#### 2. **Semantic-Driven Structure (의미 중심 구조)**  
- 순차적 섹션: 단계나 우선순위가 있는 경우 번호 사용
- 병렬적 섹션: 독립적이고 동등한 경우 번호 없이 구성
- 내용의 성격이 구조를 결정

#### 3. **Intelligent Consistency (지능적 일관성)**
- 의미적 구조를 해치지 않는 선에서 형식 통일
- 우선순위: 내용의 의미 전달 > 형식적 통일성 > 개별 문서 최적화

#### 4. **Review Scope Focus (검토 범위 집중)**
- **문제 식별만**: 해결책 제시 없이 문제점 발견에만 집중
- **우선순위 기반**: Critical/High 문제 우선, 방향성만 제시

---

## 📋 Consistency Review Checklist (일관성 검토 체크리스트)

### ✅ **1. Title Structure (제목 구조)**
- [ ] **English (Korean) Format**: 모든 주요 섹션이 "영문 (한글)" 형식인가?
- [ ] **Missing Translations**: 영문 또는 한글 번역이 누락된 제목이 있는가?
- [ ] **Order Consistency**: 영문이 먼저, 한글이 괄호 안에 일관되게 배치되었는가?

### ✅ **2. Visual Consistency (시각적 일관성)**
- [ ] **Emoji Usage**: 같은 성격의 섹션에 일관된 이모지가 사용되었는가?
- [ ] **Section Numbering**: 순차적 섹션은 번호가 있고, 병렬적 섹션은 번호가 없는가?
- [ ] **Code Block Style**: 코드 블록 형식이 문서 간 일치하는가?

### ✅ **3. Content Quality (내용 품질)**
- [ ] **Abstract Expressions**: "복잡한", "적절한", "충분한" 등 모호한 표현이 있는가?
- [ ] **Measurable Criteria**: 조건문에 구체적 기준(숫자, 체크리스트)이 있는가?
- [ ] **Duplicate Content**: 같은 내용이 여러 문서에 중복되어 있는가?

### ✅ **4. Logical Consistency (논리적 일관성)**
- [ ] **Rule Conflicts**: 문서 간 상충하는 규칙이나 지시사항이 있는가?
- [ ] **Circular References**: 순환 참조나 무한 루프 구조가 있는가?
- [ ] **Premise Violations**: 기본 원칙과 세부 규칙이 모순되는가?

### ✅ **5. Cross-Reference Accuracy (상호 참조 정확성)**
- [ ] **Document References**: 다른 문서 참조가 실제 파일명과 일치하는가?
- [ ] **Section References**: 참조된 섹션명이 실제 제목과 정확히 일치하는가?
- [ ] **Broken Links**: 존재하지 않는 섹션을 참조하고 있는가?

### ✅ **6. Completeness (완전성)**
- [ ] **Missing Scenarios**: 중요한 시나리오에 대한 규칙이 누락되었는가?
- [ ] **Actionable Rules**: AI가 실제로 따를 수 있는 구체적 규칙인가?
- [ ] **Coverage Balance**: 모든 AI 역할과 상황이 적절히 다뤄지고 있는가?

---

## 🔍 Review Process (검토 프로세스)

### **Step 1: Quick Scan (빠른 스캔)**
문서를 전체적으로 훑어보며 위 체크리스트의 명백한 위반 사항을 식별

### **Step 2: Detailed Check (상세 체크)**
각 체크리스트 항목을 순서대로 확인하며 문제점 기록

### **Step 3: Priority Assessment (우선순위 평가)**
발견된 문제점을 중요도에 따라 분류:
- **Critical (긴급)**: 논리적 모순, 규칙 충돌
- **High (높음)**: 모호한 표현, 참조 오류  
- **Medium (중간)**: 형식 불일치, 중복 내용
- **Low (낮음)**: 시각적 일관성 문제

### **Step 4: Improvement Suggestions (개선 제안)**
문제점별로 **방향성만** 제시 (구체적 해결책은 AI가 판단)

---

## 📊 Success Criteria (성공 기준)

**완벽한 일관성 달성 시:**
- [ ] 모든 체크리스트 항목 통과
- [ ] Critical/High 우선순위 문제 0개
- [ ] AI가 추가 설명 없이 규칙 적용 가능
- [ ] 다른 세션에서 동일한 결과 도출 가능

---

**🎯 Remember: 이 가이드라인은 "무엇을 체크할 것인가"만 제시합니다. 구체적인 검토 방법과 해결책은 AI가 상황에 맞게 판단하세요.**