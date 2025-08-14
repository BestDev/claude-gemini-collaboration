# 다중 언어 지원 협업 전략

## 개요
Claude Code와 Gemini CLI 협업에서 주요 개발 언어들에 대한 최적화된 워크플로우와 도구 설정을 정의합니다.

## 지원 언어 목록

### 1. 🐍 Python
**용도**: 스크립팅, 웹 개발, 데이터 분석, AI/ML
**특징**: 동적 타입, 인터프리터 언어

### 2. ⚡ C++
**용도**: 시스템 프로그래밍, 고성능 애플리케이션
**특징**: 컴파일 언어, 메모리 관리 필요

### 3. 🔧 C
**용도**: 시스템 프로그래밍, 임베디드 개발, 커널 개발
**특징**: 저수준 제어, 수동 메모리 관리, POSIX 호환

### 4. 🎮 Unreal Engine C++
**용도**: 게임 개발, 고성능 3D 애플리케이션
**특징**: UE 프레임워크 특화, Blueprint 연동

### 5. 🎯 Unity C#
**용도**: 게임 개발, VR/AR 애플리케이션
**특징**: Unity 엔진 특화, MonoBehaviour 기반

### 6. 🚀 Go (Golang)
**용도**: 마이크로서비스, 네트워크 프로그래밍, DevOps 도구
**특징**: 컴파일 언어, 고루틴 지원

### 7. 💼 C# .NET
**용도**: 엔터프라이즈 애플리케이션, 웹 서비스, 데스크톱 앱
**특징**: 강타입, 가비지 컬렉션, 크로스 플랫폼

### 8. 🟢 Node.js
**용도**: 백엔드 개발, API 서버, 실시간 애플리케이션
**특징**: 비동기 I/O, 이벤트 루프, JavaScript 런타임

### 9. 🔷 TypeScript
**용도**: 대규모 JavaScript 애플리케이션, 타입 안전성 요구 프로젝트
**특징**: 정적 타입, JavaScript 슈퍼셋, 컴파일 타임 검사

## 지원 데이터베이스 목록

### 1. 🗄️ MySQL
**용도**: 관계형 데이터베이스, 웹 애플리케이션 표준 RDBMS
**특징**: ACID 트랜잭션, 성숙한 생태계, 높은 성능

### 2. ⚡ Redis
**용도**: 인메모리 캐시, 세션 저장소, 실시간 데이터 처리
**특징**: 고속 처리, 다양한 자료구조, Pub/Sub 지원

### 3. 🐘 PostgreSQL
**용도**: 고급 관계형 데이터베이스, 엔터프라이즈급 애플리케이션
**특징**: 고급 SQL 기능, JSON 지원, 확장성

### 4. 🍃 MongoDB
**용도**: NoSQL 문서 데이터베이스, 유연한 스키마
**특징**: JSON 네이티브, 수평 확장, 집계 프레임워크

### 5. 📱 SQLite
**용도**: 임베디드 데이터베이스, 게임/모바일 애플리케이션
**특징**: 서버리스, 경량, 크로스 플랫폼

## 지원 데이터 소스 목록

### 1. 📊 Excel/Google Sheets
**용도**: 기획 데이터 관리, 게임 테이블 데이터, 다국어 지원
**특징**: 실시간 동기화, 기획-개발 브릿지, 비개발자 친화적

## 언어별 개발 환경 및 도구

### Python
```yaml
린터/포매터:
  - black (코드 포매팅)
  - isort (import 정렬)
  - flake8 (스타일 검사)
  - mypy (타입 검사)

빌드/테스트:
  - pytest (테스트 프레임워크)
  - poetry/pip (패키지 관리)
  - tox (멀티 환경 테스트)

문서화:
  - sphinx (문서 생성)
  - docstring (함수 문서)
  - type hints (타입 명시)
```

### C++
```yaml
린터/포매터:
  - clang-format (코드 포매팅)
  - clang-tidy (정적 분석)
  - cpplint (스타일 검사)

빌드/테스트:
  - CMake (빌드 시스템)
  - Google Test/Catch2 (테스트 프레임워크)
  - Valgrind (메모리 검사)

문서화:
  - Doxygen (API 문서)
  - 헤더 주석 (/// 스타일)
  - README.md (프로젝트 개요)
```

### Unreal Engine C++
```yaml
린터/포매터:
  - Unreal Code Style (UE 컨벤션)
  - clang-format (UE 설정)
  - UnrealHeaderTool 규칙

빌드/테스트:
  - Unreal Build Tool (UBT)
  - Automation Tests (UE 테스트)
  - Blueprint 통합 테스트

문서화:
  - UCLASS/UFUNCTION 주석
  - Blueprint 문서화
  - UE API 문서 연동
```

### Unity C#
```yaml
린터/포매터:
  - Unity Code Style
  - dotnet format
  - EditorConfig 설정

빌드/테스트:
  - Unity Test Framework
  - NUnit (단위 테스트)
  - Unity Cloud Build

문서화:
  - XML 문서 주석 (///)
  - Unity Inspector 설명
  - ScriptableObject 문서
```

### Go
```yaml
린터/포매터:
  - gofmt (표준 포매터)
  - golint (스타일 검사)
  - go vet (정적 분석)
  - golangci-lint (통합 린터)

빌드/테스트:
  - go build (표준 빌드)
  - go test (표준 테스트)
  - go mod (모듈 관리)

문서화:
  - godoc (표준 문서)
  - README.md
  - 패키지 레벨 주석
```

### C
```yaml
린터/포매터:
  - clang-format (코드 포매팅)
  - cppcheck (정적 분석)
  - splint (코드 검사)
  - RATS (보안 검사)

빌드/테스트:
  - Make/CMake (빌드 시스템)
  - CUnit/Unity (테스트 프레임워크)
  - Valgrind (메모리 검사)
  - GDB (디버깅)

문서화:
  - Doxygen (API 문서)
  - 헤더 주석 (/** */ 스타일)
  - man pages (시스템 문서)
```

### C# .NET
```yaml
린터/포매터:
  - dotnet format (표준 포매터)
  - StyleCop (스타일 분석)
  - FxCop (코드 분석)

빌드/테스트:
  - dotnet build (표준 빌드)
  - MSTest/xUnit/NUnit (테스트)
  - NuGet (패키지 관리)

문서화:
  - XML 문서 주석 (///)
  - DocFX (문서 생성)
  - API 문서 자동 생성
```

### Node.js
```yaml
린터/포매터:
  - ESLint (JavaScript 린터)
  - Prettier (코드 포매터)
  - JSDoc (문서 주석 검사)

빌드/테스트:
  - npm/yarn/pnpm (패키지 관리)
  - Jest/Mocha/Vitest (테스트)
  - Webpack/Vite (번들링)
  - PM2/Nodemon (프로세스 관리)

문서화:
  - JSDoc (API 문서)
  - README.md
  - OpenAPI/Swagger (API 문서)
```

### TypeScript
```yaml
린터/포매터:
  - ESLint + @typescript-eslint
  - Prettier (코드 포매터)
  - TSLint (deprecated, ESLint 사용)

빌드/테스트:
  - TypeScript Compiler (tsc)
  - ts-node (개발 실행)
  - Jest/Vitest (테스트)
  - Webpack/Vite (번들링)

문서화:
  - TSDoc (TypeScript 문서)
  - Typedoc (API 문서 생성)
  - 타입 정의 파일 (.d.ts)
```

## 데이터베이스별 개발 환경 및 도구

### MySQL
```yaml
관리도구:
  - MySQL Workbench (GUI 관리)
  - phpMyAdmin (웹 기반 관리)
  - HeidiSQL (Windows 클라이언트)

성능분석:
  - MySQL Enterprise Monitor
  - Percona Monitoring and Management
  - pt-query-digest (쿼리 분석)

백업/복구:
  - mysqldump (논리적 백업)
  - MySQL Enterprise Backup
  - Percona XtraBackup (핫 백업)

언어별연동:
  - Python: PyMySQL, SQLAlchemy
  - Node.js: mysql2, Prisma
  - C#: MySql.Data, Entity Framework
  - Java: MySQL Connector/J
```

### Redis
```yaml
관리도구:
  - Redis CLI (명령줄 도구)
  - RedisInsight (GUI 관리)
  - Redis Commander (웹 기반 관리)

모니터링:
  - Redis Sentinel (고가용성)
  - Redis Cluster (샤딩)
  - Grafana + Prometheus (메트릭)

백업/복구:
  - RDB 스냅샷
  - AOF (Append Only File)
  - Redis 복제 (Master-Slave)

언어별연동:
  - Python: redis-py, aioredis
  - Node.js: ioredis, node_redis
  - C#: StackExchange.Redis
  - Java: Jedis, Lettuce
```

### PostgreSQL
```yaml
관리도구:
  - pgAdmin (GUI 관리)
  - psql (명령줄 클라이언트)
  - DBeaver (멀티 플랫폼 GUI)

성능분석:
  - pg_stat_statements (쿼리 통계)
  - pgBadger (로그 분석)
  - EXPLAIN ANALYZE (실행 계획)

백업/복구:
  - pg_dump/pg_restore (논리적 백업)
  - pg_basebackup (물리적 백업)
  - WAL 아카이빙 (연속 백업)

언어별연동:
  - Python: psycopg2, asyncpg
  - Node.js: pg, TypeORM
  - C#: Npgsql, Entity Framework
  - Java: PostgreSQL JDBC
```

### MongoDB
```yaml
관리도구:
  - MongoDB Compass (GUI 관리)
  - Robo 3T (경량 GUI)
  - mongo shell (명령줄 도구)

성능분석:
  - MongoDB Profiler
  - explain() 메서드
  - Atlas Performance Advisor

백업/복구:
  - mongodump/mongorestore
  - Atlas 자동 백업
  - Ops Manager 백업

언어별연동:
  - Python: PyMongo, Motor (async)
  - Node.js: MongoDB Driver, Mongoose
  - C#: MongoDB.Driver
  - Java: MongoDB Java Driver
```

### SQLite
```yaml
관리도구:
  - SQLite Browser (GUI)
  - sqlite3 CLI (명령줄)
  - DB Browser for SQLite

최적화:
  - PRAGMA 설정
  - ANALYZE 명령 (통계)
  - sqlite3_analyzer (분석 도구)

백업/복구:
  - .backup 명령
  - .dump 명령 (SQL 덤프)
  - 파일 복사 (단순 백업)

언어별연동:
  - Python: sqlite3 (내장)
  - Node.js: sqlite3, better-sqlite3
  - C#: System.Data.SQLite
  - Unity: SQLite4Unity3d
  - Unreal: SQLite3 Plugin
```

## 언어별 Subagents 전략

### DocGenerator 언어별 특화

#### Python
- **docstring** 자동 생성 (Google/NumPy 스타일)
- **type hints** 추가 및 검증
- **requirements.txt** 자동 업데이트
- **API 문서** (sphinx) 생성

#### C++
- **Doxygen 주석** 자동 생성
- **헤더 파일 문서화** (클래스, 함수)
- **CMakeLists.txt** 주석 추가
- **사용 예제** 코드 생성

#### Unreal Engine C++
- **UCLASS/UFUNCTION** 메타데이터 문서
- **Blueprint 연동** 가이드 생성
- **UE 컨벤션** 준수 문서
- **퍼포먼스 가이드** 생성

#### Unity C#
- **MonoBehaviour** 문서화
- **Inspector 설명** 자동 생성
- **ScriptableObject** 사용법 문서
- **Unity 이벤트** 문서화

#### Go
- **패키지 레벨** 문서 생성
- **godoc 형식** 주석 추가
- **예제 코드** (Example 함수) 생성
- **API 사용법** 문서

#### C
- **Doxygen 주석** 자동 생성
- **헤더 파일 문서화** (구조체, 함수)
- **Makefile** 주석 추가
- **시스템 콜** 사용법 문서

#### C# .NET
- **XML 문서 주석** 자동 생성
- **API 문서** (DocFX) 생성
- **NuGet 패키지** 문서
- **버전 관리** 문서

#### Node.js
- **JSDoc 주석** 자동 생성
- **API 엔드포인트** 문서화
- **OpenAPI/Swagger** 스펙 생성
- **환경 설정** 가이드

#### TypeScript
- **TSDoc 주석** 자동 생성
- **타입 정의** 문서화
- **인터페이스** 사용법 문서
- **제네릭 타입** 설명

### Linter/Formatter 언어별 설정

#### 공통 원칙
1. **일관성**: 프로젝트 내 코딩 스타일 통일
2. **자동화**: 커밋 전 자동 실행
3. **점진적 도입**: 기존 코드는 단계적 적용
4. **팀 합의**: 스타일 가이드 사전 협의

#### 실행 순서
```bash
# 1단계: 포매팅
언어별_formatter 실행

# 2단계: 린팅
언어별_linter 실행

# 3단계: 정적 분석
언어별_static_analyzer 실행

# 4단계: 테스트
언어별_test_runner 실행
```

## 프로젝트 구조별 대응

### 단일 언어 프로젝트
- 해당 언어 도구만 활성화
- 단순한 워크플로우 적용
- 빠른 피드백 루프 구성

### 다중 언어 프로젝트
- 언어별 subagent 병렬 실행
- 공통 문서화 전략 수립
- 언어 간 인터페이스 문서화

### 게임 엔진 프로젝트
- 엔진별 특화 도구 사용
- 에셋 파이프라인 고려
- 플랫폼별 빌드 지원

## 성능 최적화 전략

### 언어별 특성 고려
- **컴파일 언어**: 증분 빌드 지원
- **인터프리터 언어**: 빠른 피드백
- **게임 엔진**: 에디터 통합 고려

### 캐싱 전략
- 린터 결과 캐싱
- 문서 생성 결과 캐싱
- 테스트 결과 캐싱

### 병렬 처리
- 언어별 독립적 처리
- CPU 코어 활용 최적화
- 메모리 사용량 모니터링

## 품질 기준

### 코드 품질
- **스타일 일관성**: 95% 이상
- **문서화 비율**: 80% 이상
- **테스트 커버리지**: 언어별 목표 설정

### 성능 기준
- **린팅 시간**: 1분 이내
- **문서 생성**: 5분 이내
- **전체 워크플로우**: 10분 이내

---

**이 문서는 언어별 특성과 프로젝트 요구사항에 따라 지속적으로 업데이트됩니다.**