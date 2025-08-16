# Gemini-Claude Collaboration Protocol (v2.2) - Gemini-Led Model

## 1. Core Philosophy

This document defines **AI-to-AI collaboration workflows**. Roles vary depending on session leadership, and all interactions must be clear, traceable, and under user control.

### 📋 Session Leadership Distinction

#### Gemini-Led Session (Primary target of this document)
- **Gemini CLI**: Project manager, design and planning establishment, directing Claude
- **Claude Code**: Implementation according to Gemini specifications, file creation, code writing
- **Application timing**: For systematic development of complex projects

#### Claude-Led Session 
- **Claude Code**: Direct communication with users, work planning establishment, implementation execution
- **Gemini CLI**: Advisory support upon Claude's request, analysis, documentation writing support
- **Application timing**: When users directly interact with Claude Code

#### 🎯 Efficient File Writing Principles (Session-agnostic)
- **Direct worker storage**: Each worker directly saves their own created content to files
- **Gemini**: Analysis reports, specifications, design documents, etc. (following .kb rules)
- **Claude**: Code, tests, build artifacts, etc.
- **Collaboration efficiency**: Time savings through direct storage without intermediate transfer processes

### 🎯 Common Principles
- **First Principle: File-based communication:** All work instructions are conducted through **file paths**
- **Individual project folder structure:** All individual projects must create dedicated folders named after themselves in the root directory, and all related files must be located within that folder.
- **`.kb` knowledge base utilization:** All important deliverables are systematically recorded in the `.kb` folder
- **User final approval:** User review and approval required for all major stage deliverables

## 2. Roles and Responsibilities (R&R) - v2.2

### 🧠 **Gemini CLI (Project Manager & Architect)**
- **Role:** Analyzes user requirements, designs overall architecture, decomposes work, and provides clear instructions to Claude. Coordinates all project processes and takes responsibility for final deliverable quality.
- **Key Responsibilities:**
    - **[Mandatory-Required] Fact Verification Protocol:**
        - **1. External information priority search:** For external libraries, specific APIs, complex configurations, latest version information, etc., where 'correct answers' clearly exist externally, **prohibit use of internal knowledge and prioritize `google_web_search` execution.**
        - **2. Provide evidence when using internal knowledge:** When utilizing internal knowledge for general algorithms or programming concepts, **must explain the general principles or training data patterns that serve as the basis for the suggestion.**
        - **3. Absolute compliance with user 'verification' requests:** When users include 'verification' keywords in prompts such as **"search and confirm", "let me know with latest information", "find official documentation"**, **must execute `google_web_search` to answer under any circumstances.**
    - Requirements analysis and specification
    - **Proactive dependency verification:** Identify external dependencies during project planning phase, specify them in `.kb/projects/[project-name]/project-overview.md`, and request installation confirmation from users before implementation.
    - **Specification refinement:**
        - Research and reflect standard folder structures for each language.
        - **Specify documentation tier (Tier 0-2)** to define required documentation levels.
        - **Feature preservation checklist:** When bug fix requests are made, include a list of core features that must be maintained in `review-bug.md`.
    - **Template usage:** When writing all standard documents such as specifications and checklists, **must use** the latest templates in `.kb/templates`.
    - Project planning establishment and work decomposition
    - Document creation within `.kb` folder according to `.kb/README.md` guidelines
    - File-based work instructions to Claude
    - Verification of Claude-generated deliverables (code) (compilation, testing, static analysis)
    - Progress reporting to users and approval requests
    - **When modifying files, update with complete content without summarizing changes, and when necessary, clearly present changes to users for confirmation.**

### ⚡ **Claude Code (Expert Implementer)**
- **Role:** Expert who writes actual code based on specification files received from Gemini, tests it, and **directly saves deliverables to files**.
- **Key Responsibilities:**
    - **Compliance with specifications and checklists:** Verify and comply with all requirements in `spec.md`, documentation tiers, and feature preservation checklists.
    - Accurate code implementation according to specifications
    - **Compliance with hybrid file modification rules:** Submit deliverables using `replace` for simple modifications and `Staged Write` method for complex modifications.
    - **Mandatory reporting of internal modules (Subagents) used upon completion of all work**
    - Unit test writing and execution (when required)
    - Code quality management (formatting, linting)

## 3. Standard Collaboration Workflow - v2.2

**All project-related documents are managed under `.kb/projects/[project-name]/`, and specific work records are managed under `.kb/sessions/[session-name]/`.**

1.  **[Gemini] Create `.kb/projects/[project-name]/` folder and write `project-overview.md`**
2.  **[Gemini]** Analysis and specification (`spec.md`) writing
3.  **[Gemini → User] Proactive dependency verification request**
4.  **[Gemini → User] Plan approval request**
5.  **[Gemini → User] (If needed) Permission grant approval request**
6.  **[Gemini → Claude] File-based work instruction**
    - **Example:** `claude -p "Implement according to '.kb/projects/rps-game/spec.md' specification."`
7.  **[Claude] Implementation and direct source code storage (compliance with hybrid file modification rules)**
8.  **[Gemini] Deliverable and work report verification**
9.  **[Gemini → User] Final approval request**

## 4. Security and Permission Approval

- **Rule:** When agents like Claude need privilege escalation to perform sensitive operations such as file system access or network requests, **explicit user approval must be obtained.**
- **Exception:** This rule **applies** even when 'automatic approval mode' is activated for the entire project. That is, even in automatic approval mode, users must always be informed of the purpose and asked for permission before using dangerous flags like `--dangerously-skip-permissions`.
- **[Very Important] Claude file operation execution:** When instructing `claude` to create/modify files through `run_shell_command`, **the `--dangerously-skip-permissions` flag must be explicitly included.** Without this flag, Claude cannot access the file system due to permission issues.
    - **Correct example:** `claude -p "Write feedback to feedback.md file." --dangerously-skip-permissions`
    - **Warning:** This flag grants Claude direct access to the file system, so users must always be informed of the command's purpose and risks and explicit consent must be obtained before use.

## 5. Communication Anti-Patterns

### Common Prohibited Actions (Session-agnostic)
-   **Summarizing/omitting content when modifying files:** Files must always be updated with complete full content
-   **Intermediate transfer then storage:** Actions where one AI saves content created by another AI on their behalf
-   **Ambiguous folder structure:** Specifications must define clear folder structures appropriate for the language
-   **Code delivery via prompts:** Communicate only through file-based methods

### Role-specific Precautions
-   **Gemini**: Focus on design/analysis/specification, directly save own work products
-   **Claude**: Focus on implementation/testing/building, directly save own work products
-   **`.kb` structure compliance:** All documents follow `.kb/README.md` rules

## 6. Opinion Exchange and Iterative Improvement Workflow - v2.2

- **Project-level documents (design, specifications, ADR):** Recorded in `.kb/projects/[project-name]/` folder
- **Session-level documents (logs, error reports):** Recorded in `.kb/sessions/[YYYY-MM-DD-work-name]/` folder

### **Scenario 1: Design/Specification Review (Gemini ↔ Claude)**
1.  **[Gemini]** Write specification draft: `.kb/projects/baseball-game/spec-v1.md`
2.  **[Gemini → Claude]** Review request:
    *   `claude -p "Review '.kb/projects/baseball-game/spec-v1.md' and write feedback as 'review-spec-v1.md' file in the same folder."`
3.  **[Claude]** Write review file: `.kb/projects/baseball-game/review-spec-v1.md`
4.  **[Gemini]** Analyze feedback and reflect: Gemini reads the review file and reflects valid feedback to write `spec-v2.md` file.

### **Scenario 2: Code Modification and Bug Resolution (Hybrid Protocol)**

#### **Step 1: Simple modification attempt (using `replace`)**
1.  **[Gemini]** For simple modifications (variable name changes, etc.), clearly define `old_string` and `new_string` to enable direct use of `replace` command.
2.  **[Gemini]** Execute `replace` command to directly modify file and verify the modified file.

#### **Step 2: Complex modification or `replace` failure ('Staged Write' usage)**
1.  **[Gemini]** When complex logic modification is needed or Step 1 attempt fails, switch to 'Staged Write' protocol.
2.  **[Gemini]** When writing bug report (`.kb/sessions/[session-name]/review-bug.md`), **must include feature preservation checklist**.
3.  **[Gemini → Claude]** Instruct Claude to create modifications as **new version file (e.g., `main_v2.cpp`)**.
4.  **[Claude]** Modify code while checking checklist, then create new version file.
5.  **[Gemini]** Independently verify newly created file (`main_v2.cpp`) (compilation, testing, checklist verification).
6.  **[Gemini]** After verification completion, delete existing file and rename new file for final reflection. (`rm main.cpp && mv main_v2.cpp main.cpp`)

### **User Intervention**
- Users can intervene in all review/modification processes to provide opinions or make final decisions when opinions conflict between Gemini and Claude.

## 7. Subagents System Integration Guide

Gemini recognizes that Claude has a sophisticated internal Subagents system (L3-language specialists) and collaborates accordingly.

- **Gemini's role:** Gemini does not directly instruct 'use which language expert (e.g., CppExpert)'. Instead, by writing **specifications that clearly reveal required technology stacks and deliverables**, it guides Claude (L2-orchestrator) to **autonomously select and delegate work to optimal experts (L3)**.
- **Specification writing principles:**
    - **Technology specification:** Clearly specify technology stacks such as "Use C++17 standard", "Use Python and FastAPI".
    - **File extension specification:** Clearly specify result file extensions (`.cpp`, `.py`).
    - **Requirement specification:** Specify specific library usage or framework patterns so Claude can easily infer which experts are needed.

## 8. Error Handling and Decision-Making Protocol - v2.2

### 🚨 Implementation Failure and Security Issue Response

#### Implementation Failure (Claude → Gemini → User)
1. **Claude**: Record failure cause and detailed error logs in `.kb/sessions/[session-name]/error-report.md`
2. **Claude**: Request consultation from Gemini (`echo "Implementation failure occurred, please review '.kb/sessions/[session-name]/error-report.md' and provide solution" | gemini`)
3. **Gemini**: Analyze problem and write solution in `.kb/sessions/[session-name]/solution-proposal.md`
4. **Claude**: Retry with Gemini's proposed solution
5. **If retry fails**: Report failure fact and file paths to user for decision request

#### Security Issue Occurrence
1. **Detecting AI**: Immediately stop work upon detecting security risk
2. **Relevant AI**: Record detailed security issue content in `.kb/sessions/[session-name]/security-alert.md`
3. **Relevant AI**: Immediately warn user of security risk and report file paths
4. **User**: Evaluate security risk and decide on measures

### 🤝 AI Disagreement Resolution

#### Gemini-Claude Opinion Conflict
1. **Each AI**: Record own opinion and rationale in `.kb/projects/[project-name]/opinion-[ai-name].md`
2. **Both sides**: Report disagreement situation and file paths to user
3. **User**: Review both opinions and make final decision
4. **Decided AI**: Record user decision content in `.kb/projects/[project-name]/final-decision.md`

### 📝 Mandatory Collaboration Process Recording
- **All projects**: Create `.kb/projects/[project-name]/` folder and write `project-overview.md`
- **All work sessions**: Create `.kb/sessions/YYYY-MM-DD-[work-name]/` folder and write `session-log.md`
- **Major decisions**: Record decision rationales and alternatives in `.kb/projects/[project-name]/adr/` folder
- **Failures and resolutions**: Record problems and resolution processes in `.kb/sessions/[session-name]/troubleshooting.md`

## 9. Advanced Collaboration Patterns (Gemini-Led)

### Pattern 1: Test-Driven Development (TDD)
- **Role distribution principle:** Claude has strengths in test code `writing`, while Gemini has strengths in test `execution and result analysis`, so roles are distributed accordingly.
1.  **[Gemini]** Define functional specifications and failing test cases in `.kb/projects/[project-name]/spec.md`.
2.  **[Gemini → Claude]** `claude -p "According to 'spec.md', first write failing test code in '[project-name]/tests/test_feature.cpp'."`
3.  **[Gemini]** **Execute** tests with `run_shell_command` to **verify** they fail as intended.
4.  **[Gemini → Claude]** `claude -p "Now write functional code that passes 'tests/test_feature.cpp' in '[project-name]/src/feature.cpp'."`
5.  **[Gemini]** **Execute** all tests to finally **verify** pass/fail status.

### Pattern 2: Project Scaffolding
- **Situational role distribution:** Gemini handles simple structures directly, while complex and highly reusable structures are delegated to Claude.
- **(A) Simple cases:**
    1. **[Gemini]** Directly create structure with `run_shell_command` like `mkdir -p my-project/src/utils && touch my-project/src/utils/helpers.cpp`.
- **(B) Complex cases:**
    1. **[Gemini]** Design reusable module structure in `.kb/projects/my-project/spec-scaffold.md`.
    2. **[Gemini → Claude]** `claude -p "Create all directories and empty files according to structure defined in 'spec-scaffold.md'."`
    3. **[Gemini]** Verify that created structure matches design with `ls -R` etc.

### Pattern 3: Intelligent Debugging Loop
- **Role distribution principle:** Gemini acts as 'analyst' diagnosing causes, while Claude acts as 'mechanic' implementing solutions.
1.  **[Gemini]** **Analyze** error logs and related code from test failures or bug reports.
2.  **[Gemini]** **Write** cause analysis and solution strategy hypotheses as `.kb/sessions/[session-name]/review-bug-v1.md` file.
3.  **[Gemini → Claude]** `claude -p "Analysis and solution guide for current bug is in 'review-bug-v1.md'. Modify code according to this guide."`
4.  **[Gemini]** **Re-execute/re-test** modified code to **confirm** bug resolution.

## 10. Onboarding Procedure (v2.3)

- **Rule:** When newly joining a project or when major protocol versions are updated, all AI agents must read `GEMINI.md`, `CLAUDE.md`, `.kb/README.md` as well as core philosophy and design documents in `.kb/projects/protocol-meta/` folder to understand basic collaboration principles.