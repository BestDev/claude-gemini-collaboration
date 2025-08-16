# ADR-001: Adoption of User-Centered Collaboration Model

## Status
Approved (2025-08-14)

## Context
We reviewed multiple models to establish an effective collaboration structure between Claude Code and Gemini CLI:

1. **3-Tier Sequential Model**: Gemini(Strategy) → Subagents(Expert Execution) → Claude(Implementation)
2. **Tool-Augmented Model**: Gemini(Central Hub) ↔ Expert Tools(Including Claude)  
3. **User-Centered Model**: Structure where users have approval authority at major decision points

## Decision
We adopt the **User-Centered Collaboration Model**.

### Core Structure
```
User Request → Gemini Analysis&Planning → [User Approval1] → 
Gemini Specification Writing → [User Approval2] → Claude Implementation → [User Approval3] → 
.kb Documentation
```

### Role Definitions
- **User**: Final decision maker, quality standard setter
- **Gemini CLI**: Project manager & strategist (analysis, planning, specification writing)
- **Claude Code**: Expert implementer (code writing, Subagents coordination, quality management)

## Rationale

### Reasons for Selection
1. **Transparency**: All processes are clearly reported to users
2. **Control**: Users can intervene and redirect the process at any time
3. **Context Preservation**: Minimize intent distortion through user approval
4. **Practicality**: Most realistic approach given current AI technology level

### Rejected Alternatives
- **3-Tier Model**: Rigid pipeline, risk of context loss
- **Tool-Augmented Model**: Gemini overload, lack of user control

## Consequences
- Expected improvement in project success rate
- Increased user satisfaction
- Minimized role conflicts between AIs
- Clear responsibility distribution

## Compatibility
Fully compatible with existing Claude Code + Gemini CLI environment.

## References (v2.2)
- `GEMINI.md` - Gemini-led collaboration protocol v2.2
- `CLAUDE.md` - Claude Code collaboration protocol v2.2
- `.kb/README.md` - Knowledge Base structure and usage guide v2.2