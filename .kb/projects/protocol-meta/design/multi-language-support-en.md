# Multi-Language Support Collaboration Strategy

## Overview
This document defines optimized workflows and tool configurations for major development languages in the collaboration between Claude Code and Gemini CLI.

## Supported Languages List

### 1. 🐍 Python
**Use Cases**: Scripting, web development, data analysis, AI/ML
**Characteristics**: Dynamic typing, interpreted language

### 2. ⚡ C++
**Use Cases**: System programming, high-performance applications
**Characteristics**: Compiled language, memory management required

### 3. 🔧 C
**Use Cases**: System programming, embedded development, kernel development
**Characteristics**: Low-level control, manual memory management, POSIX compatible

### 4. 🎮 Unreal Engine C++
**Use Cases**: Game development, high-performance 3D applications
**Characteristics**: UE framework specialized, Blueprint integration

### 5. 🎯 Unity C#
**Use Cases**: Game development, VR/AR applications
**Characteristics**: Unity engine specialized, MonoBehaviour-based

### 6. 🚀 Go (Golang)
**Use Cases**: Microservices, network programming, DevOps tools
**Characteristics**: Compiled language, goroutine support

### 7. 💼 C# .NET
**Use Cases**: Enterprise applications, web services, desktop apps
**Characteristics**: Strong typing, garbage collection, cross-platform

### 8. 🟢 Node.js
**Use Cases**: Backend development, API servers, real-time applications
**Characteristics**: Asynchronous I/O, event loop, JavaScript runtime

### 9. 🔷 TypeScript
**Use Cases**: Large-scale JavaScript applications, type safety required projects
**Characteristics**: Static typing, JavaScript superset, compile-time checking

## Supported Database List

### 1. 🗄️ MySQL
**Use Cases**: Relational database, standard RDBMS for web applications
**Characteristics**: ACID transactions, mature ecosystem, high performance

### 2. ⚡ Redis
**Use Cases**: In-memory cache, session storage, real-time data processing
**Characteristics**: High-speed processing, various data structures, Pub/Sub support

### 3. 🐘 PostgreSQL
**Use Cases**: Advanced relational database, enterprise-grade applications
**Characteristics**: Advanced SQL features, JSON support, extensibility

### 4. 🍃 MongoDB
**Use Cases**: NoSQL document database, flexible schema
**Characteristics**: JSON native, horizontal scaling, aggregation framework

### 5. 📱 SQLite
**Use Cases**: Embedded database, game/mobile applications
**Characteristics**: Serverless, lightweight, cross-platform

## Supported Data Source List

### 1. 📊 Excel/Google Sheets
**Use Cases**: Planning data management, game table data, multi-language support
**Characteristics**: Real-time synchronization, planning-development bridge, non-developer friendly

## Language-Specific Development Environment and Tools

### Python
```yaml
Linters/Formatters:
  - black (code formatting)
  - isort (import sorting)
  - flake8 (style checking)
  - mypy (type checking)

Build/Test:
  - pytest (test framework)
  - poetry/pip (package management)
  - tox (multi-environment testing)

Documentation:
  - sphinx (documentation generation)
  - docstring (function documentation)
  - type hints (type specification)
```

### C++
```yaml
Linters/Formatters:
  - clang-format (code formatting)
  - clang-tidy (static analysis)
  - cpplint (style checking)

Build/Test:
  - CMake (build system)
  - Google Test/Catch2 (test framework)
  - Valgrind (memory checking)

Documentation:
  - Doxygen (API documentation)
  - Header comments (/// style)
  - README.md (project overview)
```

### Unreal Engine C++
```yaml
Linters/Formatters:
  - Unreal Code Style (UE conventions)
  - clang-format (UE configuration)
  - UnrealHeaderTool rules

Build/Test:
  - Unreal Build Tool (UBT)
  - Automation Tests (UE testing)
  - Blueprint integration tests

Documentation:
  - UCLASS/UFUNCTION comments
  - Blueprint documentation
  - UE API documentation integration
```

### Unity C#
```yaml
Linters/Formatters:
  - Unity Code Style
  - dotnet format
  - EditorConfig settings

Build/Test:
  - Unity Test Framework
  - NUnit (unit testing)
  - Unity Cloud Build

Documentation:
  - XML documentation comments (///)
  - Unity Inspector descriptions
  - ScriptableObject documentation
```

### Go
```yaml
Linters/Formatters:
  - gofmt (standard formatter)
  - golint (style checking)
  - go vet (static analysis)
  - golangci-lint (integrated linter)

Build/Test:
  - go build (standard build)
  - go test (standard testing)
  - go mod (module management)

Documentation:
  - godoc (standard documentation)
  - README.md
  - Package-level comments
```

### C
```yaml
Linters/Formatters:
  - clang-format (code formatting)
  - cppcheck (static analysis)
  - splint (code checking)
  - RATS (security checking)

Build/Test:
  - Make/CMake (build system)
  - CUnit/Unity (test framework)
  - Valgrind (memory checking)
  - GDB (debugging)

Documentation:
  - Doxygen (API documentation)
  - Header comments (/** */ style)
  - man pages (system documentation)
```

### C# .NET
```yaml
Linters/Formatters:
  - dotnet format (standard formatter)
  - StyleCop (style analysis)
  - FxCop (code analysis)

Build/Test:
  - dotnet build (standard build)
  - MSTest/xUnit/NUnit (testing)
  - NuGet (package management)

Documentation:
  - XML documentation comments (///)
  - DocFX (documentation generation)
  - Automated API documentation
```

### Node.js
```yaml
Linters/Formatters:
  - ESLint (JavaScript linter)
  - Prettier (code formatter)
  - JSDoc (documentation comment checking)

Build/Test:
  - npm/yarn/pnpm (package management)
  - Jest/Mocha/Vitest (testing)
  - Webpack/Vite (bundling)
  - PM2/Nodemon (process management)

Documentation:
  - JSDoc (API documentation)
  - README.md
  - OpenAPI/Swagger (API documentation)
```

### TypeScript
```yaml
Linters/Formatters:
  - ESLint + @typescript-eslint
  - Prettier (code formatter)
  - TSLint (deprecated, use ESLint)

Build/Test:
  - TypeScript Compiler (tsc)
  - ts-node (development execution)
  - Jest/Vitest (testing)
  - Webpack/Vite (bundling)

Documentation:
  - TSDoc (TypeScript documentation)
  - Typedoc (API documentation generation)
  - Type definition files (.d.ts)
```

## Database-Specific Development Environment and Tools

### MySQL
```yaml
Management Tools:
  - MySQL Workbench (GUI management)
  - phpMyAdmin (web-based management)
  - HeidiSQL (Windows client)

Performance Analysis:
  - MySQL Enterprise Monitor
  - Percona Monitoring and Management
  - pt-query-digest (query analysis)

Backup/Recovery:
  - mysqldump (logical backup)
  - MySQL Enterprise Backup
  - Percona XtraBackup (hot backup)

Language Integration:
  - Python: PyMySQL, SQLAlchemy
  - Node.js: mysql2, Prisma
  - C#: MySql.Data, Entity Framework
  - Java: MySQL Connector/J
```

### Redis
```yaml
Management Tools:
  - Redis CLI (command-line tool)
  - RedisInsight (GUI management)
  - Redis Commander (web-based management)

Monitoring:
  - Redis Sentinel (high availability)
  - Redis Cluster (sharding)
  - Grafana + Prometheus (metrics)

Backup/Recovery:
  - RDB snapshots
  - AOF (Append Only File)
  - Redis replication (Master-Slave)

Language Integration:
  - Python: redis-py, aioredis
  - Node.js: ioredis, node_redis
  - C#: StackExchange.Redis
  - Java: Jedis, Lettuce
```

### PostgreSQL
```yaml
Management Tools:
  - pgAdmin (GUI management)
  - psql (command-line client)
  - DBeaver (multi-platform GUI)

Performance Analysis:
  - pg_stat_statements (query statistics)
  - pgBadger (log analysis)
  - EXPLAIN ANALYZE (execution plan)

Backup/Recovery:
  - pg_dump/pg_restore (logical backup)
  - pg_basebackup (physical backup)
  - WAL archiving (continuous backup)

Language Integration:
  - Python: psycopg2, asyncpg
  - Node.js: pg, TypeORM
  - C#: Npgsql, Entity Framework
  - Java: PostgreSQL JDBC
```

### MongoDB
```yaml
Management Tools:
  - MongoDB Compass (GUI management)
  - Robo 3T (lightweight GUI)
  - mongo shell (command-line tool)

Performance Analysis:
  - MongoDB Profiler
  - explain() method
  - Atlas Performance Advisor

Backup/Recovery:
  - mongodump/mongorestore
  - Atlas automatic backup
  - Ops Manager backup

Language Integration:
  - Python: PyMongo, Motor (async)
  - Node.js: MongoDB Driver, Mongoose
  - C#: MongoDB.Driver
  - Java: MongoDB Java Driver
```

### SQLite
```yaml
Management Tools:
  - SQLite Browser (GUI)
  - sqlite3 CLI (command-line)
  - DB Browser for SQLite

Optimization:
  - PRAGMA settings
  - ANALYZE command (statistics)
  - sqlite3_analyzer (analysis tool)

Backup/Recovery:
  - .backup command
  - .dump command (SQL dump)
  - File copy (simple backup)

Language Integration:
  - Python: sqlite3 (built-in)
  - Node.js: sqlite3, better-sqlite3
  - C#: System.Data.SQLite
  - Unity: SQLite4Unity3d
  - Unreal: SQLite3 Plugin
```

## Language-Specific Subagents Strategy

### DocGenerator Language Specialization

#### Python
- **docstring** automatic generation (Google/NumPy style)
- **type hints** addition and validation
- **requirements.txt** automatic updates
- **API documentation** (sphinx) generation

#### C++
- **Doxygen comments** automatic generation
- **Header file documentation** (classes, functions)
- **CMakeLists.txt** comment addition
- **Usage example** code generation

#### Unreal Engine C++
- **UCLASS/UFUNCTION** metadata documentation
- **Blueprint integration** guide generation
- **UE convention** compliance documentation
- **Performance guide** generation

#### Unity C#
- **MonoBehaviour** documentation
- **Inspector description** automatic generation
- **ScriptableObject** usage documentation
- **Unity events** documentation

#### Go
- **Package-level** documentation generation
- **godoc format** comment addition
- **Example code** (Example functions) generation
- **API usage** documentation

#### C
- **Doxygen comments** automatic generation
- **Header file documentation** (structs, functions)
- **Makefile** comment addition
- **System call** usage documentation

#### C# .NET
- **XML documentation comments** automatic generation
- **API documentation** (DocFX) generation
- **NuGet package** documentation
- **Version management** documentation

#### Node.js
- **JSDoc comments** automatic generation
- **API endpoint** documentation
- **OpenAPI/Swagger** specification generation
- **Environment setup** guides

#### TypeScript
- **TSDoc comments** automatic generation
- **Type definition** documentation
- **Interface** usage documentation
- **Generic type** explanations

### Language-Specific Linter/Formatter Configuration

#### Common Principles
1. **Consistency**: Unify coding style within projects
2. **Automation**: Auto-execute before commits
3. **Gradual Adoption**: Apply to existing code progressively
4. **Team Agreement**: Pre-agree on style guides

#### Execution Order
```bash
# Step 1: Formatting
Execute language_specific_formatter

# Step 2: Linting
Execute language_specific_linter

# Step 3: Static Analysis
Execute language_specific_static_analyzer

# Step 4: Testing
Execute language_specific_test_runner
```

## Project Structure-Based Responses

### Single Language Projects
- Activate only relevant language tools
- Apply simple workflows
- Configure fast feedback loops

### Multi-Language Projects
- Execute language-specific subagents in parallel
- Establish common documentation strategies
- Document inter-language interfaces

### Game Engine Projects
- Use engine-specific specialized tools
- Consider asset pipelines
- Support platform-specific builds

## Performance Optimization Strategies

### Language-Specific Considerations
- **Compiled Languages**: Support incremental builds
- **Interpreted Languages**: Fast feedback
- **Game Engines**: Consider editor integration

### Caching Strategies
- Cache linter results
- Cache documentation generation results
- Cache test results

### Parallel Processing
- Independent processing per language
- Optimize CPU core utilization
- Monitor memory usage

## Quality Standards

### Code Quality
- **Style Consistency**: 95% or higher
- **Documentation Ratio**: 80% or higher
- **Test Coverage**: Set language-specific targets

### Performance Standards
- **Linting Time**: Within 1 minute
- **Documentation Generation**: Within 5 minutes
- **Full Workflow**: Within 10 minutes

---

**This document is continuously updated based on language-specific characteristics and project requirements.**