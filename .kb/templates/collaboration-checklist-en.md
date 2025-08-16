# Collaboration Checklist (v2.2)

## Pre-Session Preparation

### User Preparation
- [ ] Have you clearly organized the requirements?
- [ ] Are priorities and deadlines set?
- [ ] Do you have expectations for the expected deliverables?
- [ ] Are necessary permissions and access secured?

### Environment Preparation  
- [ ] Is the Claude Code session active?
- [ ] Is Gemini CLI access available?
- [ ] Are you running in the project directory?
- [ ] Does the `.kb` folder structure comply with v2.2 rules?

## Gemini Analysis Phase

### Requirements Analysis
- [ ] Did you accurately understand the user request?
- [ ] Did you request clarification for ambiguous parts?
- [ ] Did you identify relationships with existing systems?
- [ ] **(v2.2)** Proactive dependency check: Did you identify necessary external libraries?

### Planning
- [ ] Did you divide the work into appropriate units?
- [ ] Did you identify dependencies for each step?
- [ ] **(v2.2)** Did you plan to request user confirmation for identified external dependencies?
- [ ] Did you identify risk factors and prepare countermeasures?

### Plan Proposal
- [ ] Did you explain it in a way that's easy for users to understand?
- [ ] Did you present alternatives?
- [ ] Did you clearly explain pros and cons?
- [ ] Did you specify concrete deliverables?

## User Approval Stage 1

### Plan Review
- [ ] Does the plan meet the requirements?
- [ ] Is the schedule realistic?
- [ ] **(v2.2)** Are the proposed external dependencies appropriate and installable?
- [ ] Are risk factors properly managed?

### Feedback Provision
- [ ] Did you clearly express approval/modification/rejection?
- [ ] Did you specifically point out parts that need modification?
- [ ] Did you specify any additional requirements?

## Gemini Specification Writing Phase

### Detailed Specification
- [ ] Are all requirements included?
- [ ] Are technical details sufficiently described?
- [ ] **(v2.2)** Is the required documentation tier (Tier 0-2) specified?
- [ ] Are test criteria clear?
- [ ] Are completion conditions measurable?

### For Bug Fix Requests
- [ ] **(v2.2)** Did you include a 'feature preservation checklist' to prevent feature regression?

### Claude Work Instructions
- [ ] Did you write it in a way that's easy for Claude to understand?
- [ ] **(v2.2)** For file modifications, did you specify which hybrid protocol (replace/Staged Write) to attempt?
- [ ] Did you include necessary context information?

## User Approval Stage 2

### Specification Review
- [ ] Is the technical approach appropriate?
- [ ] Are business requirements accurately reflected?
- [ ] Are security or performance considerations included?
- [ ] Is future scalability considered?

## Claude Implementation Phase

### Implementation Preparation
- [ ] Did you sufficiently understand the specification?
- [ ] **(v2.2)** Did you confirm the specified documentation tier and feature preservation checklist?
- [ ] Did you confirm necessary dependencies?
- [ ] Did you understand the existing code style?
- [ ] Did you select appropriate Subagents?

### Implementation Process
- [ ] Are you proceeding with TDD approach?
- [ ] Are you testing step by step?
- [ ] Are you maintaining code quality?
- [ ] Are you responding appropriately to unexpected issues?

### Implementation Completion
- [ ] Are all requirements implemented?
- [ ] Do all tests pass?
- [ ] **(v2.2)** Do all items in the feature preservation checklist work normally?
- [ ] Did you pass code quality checks?
- [ ] Is documentation for the required tier updated?

## User Approval Stage 3

### Deliverable Review
- [ ] Are all requirements met?
- [ ] Does it meet quality standards?
- [ ] Is it satisfactory from the user's perspective?
- [ ] Are there any parts that need additional modification?

### Deployment Preparation
- [ ] Is the deployment plan appropriate?
- [ ] Is a rollback plan prepared?
- [ ] Are monitoring measures in place?

## Documentation and Wrap-up

### Documentation
- [ ] Are important decisions recorded as ADRs?
- [ ] Is the session log properly recorded in `.kb/sessions`?
- [ ] Are necessary design documents created in `.kb/projects`?
- [ ] Is the problem-solving process documented?

### Project Cleanup
- [ ] Is code properly committed?
- [ ] Is branch management done correctly?
- [ ] Is the next step plan established?
- [ ] Are lessons learned organized?

## Quality Assurance

### Code Quality
- [ ] Did you pass linting rules?
- [ ] Is test coverage sufficient?
- [ ] Does performance meet requirements?
- [ ] Is security verification complete?

### Process Quality
- [ ] Did you go through all approval stages?
- [ ] Was sufficient communication conducted?
- [ ] Was documentation done appropriately?
- [ ] Did you consider future maintenance?

---

**Use this checklist to improve the quality and efficiency of collaboration.**