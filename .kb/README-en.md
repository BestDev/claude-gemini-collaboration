# Knowledge Base (KB) Usage Guide v2.3

## 1. Core Philosophy: Knowledge Repository for "Makers"

This `.kb` folder is an internal knowledge repository for project **makers** (development teams, PMs, AI collaborators). It records everything about **"How and why was this made?"** including project history, decision-making processes, and technical discussions.

In contrast, documentation about **"How to use this?"** should be written in the `doc/` directory within each project folder. (e.g., `tetris/doc/how_to_play.md`)

| Aspect | `.kb` (Knowledge Base) | `[project-name]/doc` (User Docs) |
| :--- | :--- | :--- |
| **Audience** | Internal development team, PM, AI collaborators | End users, API/library consumers |
| **Purpose** | **Why & How it was made** (creation process record) | **How to use it** (usage guidance) |
| **Main Content** | ADR, technical specs, designs, review/debugging logs | Installation guide, tutorials, API reference |

## 2. Folder Structure (v2.2)

`.kb` consists of two top-level folders: `projects` for managing **static project documents** and `sessions` for managing **chronological work records**.

### 📂 `projects/[project-name]/`
Store all static documents about the project here.

-   `project-overview.md`: **(Required)** The most important file defining project overview, tech stack, and **documentation level**.
-   `spec.md`: Functional requirements specification.
-   `design/`: Visual design materials like class diagrams, system architecture.
-   `adr/`: Architecture Decision Records for important architectural decisions.
-   `research/`: Technical research, benchmarking results.
-   `sessions/`: All session records related to this project.

### 📂 `sessions/[YYYY-MM-DD-task-name]/`
Record logs, error reports, and resolution processes for work performed on a specific date.

-   `session-log.md`: Summary of work flow for that session.
-   `error-report.md`: Detailed report on bugs or issues that occurred.
-   `solution-proposal.md`: Ideas proposed for problem resolution.
-   `troubleshooting.md`: Record of actual problem-solving process.

### 📂 `templates/`
Store standard templates for various document creation such as `adr-template.md`, `project-overview-template.md`, etc.

## 3. Core Collaboration Protocol (v2.2)

The following core protocols derived from actual project log analysis must be strictly followed to enhance collaboration stability and efficiency. (Refer to `GEMINI.md` and `CLAUDE.md` for detailed content)

#### 1. Hybrid File Modification Protocol
- **Problem**: Simultaneously resolves AI file modification failure (Silent Failure) and inefficiency of simple tasks.
- **Rules (2-step approach):**
    - **Step 1 (Simple modification):** For simple changes like variable name changes or single-line edits, attempt immediate modification using the `replace` tool.
    - **Step 2 (Complex modification & Step 1 failure):** When `replace` usage is inappropriate or fails, switch to **"Staged Write"**. AI creates modifications as a new file (e.g., `main_v2.cpp`), and the supervisor (Gemini/user) verifies and directly replaces the original.

#### 2. Explicit Documentation Tier System
- **Problem**: Resolves ambiguity in 'voluntary documentation' rules.
- **Rules**: Explicitly specify documentation requirement levels in work specifications as **Tier 0 (comments), Tier 1 (README), Tier 2 (user guide)**.

#### 3. Test Checklist for Feature Preservation
- **Problem**: Prevents 'feature regression' where other functions break during bug fixes.
- **Rules**: When requesting bug fixes, provide a checklist of 'core functions that must be maintained even after fixes'.

#### 4. Proactive Dependency Verification
- **Problem**: Prevents work interruption due to external library or dependency issues during work.
- **Rules**: Identify all necessary external dependencies in advance during project planning phase, and request user confirmation of installation status before starting implementation.

## 4. Usage Methods and Workflow

### When Starting a New Project
1.  `mkdir -p .kb/projects/my-new-project`
2.  `cp .kb/templates/project-overview-template.md .kb/projects/my-new-project/project-overview.md`
3.  Write `project-overview.md` to define project goals and documentation level.
4.  **Write specifications using templates like `cp .kb/templates/specification-template.md .kb/projects/my-new-project/spec.md`.**

### When Starting Daily Development Session
1.  `mkdir -p .kb/sessions/2025-08-16-feature-login`
2.  Record work logs, error reports, etc. in that folder.

## 5. Onboarding and Template Usage Rules (v2.3)

### Onboarding Procedure
- **Rules:** When newly joining a project or when major protocol versions are updated, all AI agents must read not only `GEMINI.md`, `CLAUDE.md`, and `.kb/README.md`, but also the core philosophy and design documents in the `.kb/projects/protocol-meta/` folder to understand the basic principles of collaboration.

### Template Usage
- **Rules:** When writing all specifications and checklists, the latest templates in `.kb/templates` must be used.

## 6. Collaboration Guide

**File Modification Principle:** When modifying any document within this Knowledge Base, content must never be summarized or omitted. Always read the entire file content, modify it, and save it again with complete content.

(Refer to `GEMINI.md` and `CLAUDE.md` for detailed AI collaboration rules.)

---
**This Knowledge Base is a living document. Continue to improve collaboration quality through continuous updates and improvements.**