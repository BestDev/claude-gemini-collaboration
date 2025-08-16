# 데이터베이스-언어 에이전트 협업 규칙

## 개요
데이터베이스 전문가와 언어별 전문가 간의 효율적이고 체계적인 협업 프로토콜을 정의합니다.

## 핵심 협업 원칙

### 🎯 역할 분리 및 책임
- **언어 에이전트**: 애플리케이션 로직, 데이터 구조 정의, ORM/ODM 설정
- **DB 에이전트**: 스키마 설계, 쿼리 최적화, 인덱싱, 성능 튜닝
- **데이터 소스 에이전트**: 스프레드시트 파싱, 데이터 변환, 품질 검증
- **완전 분리**: 각 에이전트는 자신의 전문 영역에만 집중

### 🔄 Claude 중재 모델
모든 전문가 에이전트 간 협업은 **Claude(L2)의 중재**를 통해 이루어집니다.

```
기획자 스프레드시트
        ↓
SpreadsheetExpert ↔ Claude ↔ 언어 에이전트
        ↓              ↓              ↓
    데이터 변환      작업 조율      코드 생성
        ↓                            ↓
    DB 에이전트 ← ← ← ← ← ← ← ← ← ← 최종 결과
        ↓
    DB 설계/최적화
```

## 협업 워크플로우

### 📊 스프레드시트 기반 데이터 개발 시나리오

#### 상황: 게임 아이템 시스템 구축
```
기획자: "새로운 아이템들을 추가하고 밸런스를 조정했습니다"
```

#### 워크플로우 단계
```
1. SpreadsheetExpert → Claude: "Items.xlsx 파일이 업데이트되었습니다"
2. Claude → UnityExpert: "아이템 데이터를 ScriptableObject로 변환해주세요"
3. Claude → SQLiteExpert: "게임 DB 스키마를 아이템 데이터에 맞게 업데이트해주세요"
4. Claude: 두 결과를 통합하고 일관성 검증
```

### 🏗️ 신규 기능 개발 시나리오

#### 1단계: 요구사항 분석 (Gemini → Claude)
```
Gemini: "사용자 관리 API를 FastAPI + PostgreSQL로 구현"
Claude: 작업을 언어별 + DB별로 분해
```

#### 2단계: 데이터 모델 정의 (언어 → Claude → DB)
```
1. Claude → PythonExpert: "User 모델에 필요한 필드들을 Pydantic으로 정의해줘"
2. PythonExpert → Claude: SQLAlchemy 모델 및 API 스키마 반환
3. Claude → PostgreSQLExpert: "Python 모델에 맞는 최적화된 테이블과 인덱스를 설계해줘"
4. PostgreSQLExpert → Claude: DDL 스크립트 및 인덱스 전략 반환
```

#### 3단계: 통합 및 검증 (Claude)
```
Claude가 수행하는 작업:
- Python 코드와 PostgreSQL DDL 통합
- 데이터 마이그레이션 스크립트 생성 (Alembic)
- API 엔드포인트와 DB 쿼리 연결점 검증
```

### 🔧 기존 시스템 최적화 시나리오

#### 성능 문제 해결
```
1. 문제 식별: "사용자 검색 API가 느림"
2. Claude → PostgreSQLExpert: "users 테이블 쿼리 성능 분석 및 최적화"
3. Claude → PythonExpert: "PostgreSQL 권장사항에 맞춰 FastAPI 코드 수정"
4. Claude: 변경사항 통합 및 테스트
```

## 언어별 DB 연동 패턴

### 🐍 Python 생태계

#### Python ↔ PostgreSQL
```python
# PythonExpert가 생성하는 코드
from sqlalchemy import Column, Integer, String, DateTime
from sqlalchemy.ext.declarative import declarative_base

Base = declarative_base()

class User(Base):
    __tablename__ = 'users'
    
    id = Column(Integer, primary_key=True)
    email = Column(String(255), unique=True, nullable=False)
    username = Column(String(50), unique=True, nullable=False)
    created_at = Column(DateTime, default=func.now())
```

```sql
-- PostgreSQLExpert가 생성하는 DDL
CREATE TABLE users (
    id BIGSERIAL PRIMARY KEY,
    email VARCHAR(255) UNIQUE NOT NULL,
    username VARCHAR(50) UNIQUE NOT NULL,
    created_at TIMESTAMPTZ DEFAULT NOW()
);

CREATE INDEX idx_users_email ON users(email);
CREATE INDEX idx_users_username ON users(username);
```

#### Python ↔ MongoDB
```python
# PythonExpert: Pydantic 모델
from pydantic import BaseModel, Field
from datetime import datetime

class User(BaseModel):
    email: str = Field(..., description="User email")
    username: str = Field(..., description="Unique username")
    created_at: datetime = Field(default_factory=datetime.utcnow)
```

```javascript
// MongoDBExpert: 컬렉션 스키마 및 인덱스
db.users.createIndex({ "email": 1 }, { unique: true });
db.users.createIndex({ "username": 1 }, { unique: true });
db.users.createIndex({ "created_at": -1 });
```

### 🎮 Unity 생태계

#### Unity C# ↔ SQLite
```csharp
// UnityExpert가 생성하는 코드
[System.Serializable]
public class PlayerData
{
    public int playerId;
    public string playerName;
    public int level;
    public float experience;
    public string settingsJson;
}

public class PlayerDataManager : MonoBehaviour
{
    private GameDatabase database;
    
    public void SavePlayer(PlayerData data)
    {
        database.SavePlayerData(data);
    }
}
```

```sql
-- SQLiteExpert가 생성하는 스키마
CREATE TABLE players (
    player_id INTEGER PRIMARY KEY AUTOINCREMENT,
    player_name TEXT NOT NULL,
    level INTEGER DEFAULT 1,
    experience REAL DEFAULT 0.0,
    settings_json TEXT DEFAULT '{}',
    created_at INTEGER DEFAULT (strftime('%s', 'now'))
);

CREATE INDEX idx_players_name ON players(player_name);
```

### 🟢 Node.js 생태계

#### Node.js ↔ Redis
```javascript
// NodeJSExpert가 생성하는 코드
class UserCacheService {
    constructor(redisClient) {
        this.redis = redisClient;
    }
    
    async cacheUser(userId, userData) {
        const key = `user:${userId}`;
        await this.redis.setex(key, 3600, JSON.stringify(userData));
    }
    
    async getUser(userId) {
        const key = `user:${userId}`;
        const cached = await this.redis.get(key);
        return cached ? JSON.parse(cached) : null;
    }
}
```

```redis
# RedisExpert가 제공하는 최적화
# 사용자 캐시 패턴
SET user:1001 '{"name":"John","email":"john@example.com"}' EX 3600

# 세션 관리
SET session:abc123 "user_id:1001;role:admin" EX 7200

# 실시간 카운터
INCR page_views:20240814
EXPIRE page_views:20240814 86400
```

## 데이터베이스별 특화 협업

### 🗄️ 관계형 데이터베이스 (MySQL, PostgreSQL)

#### 공통 협업 패턴
1. **스키마 우선 설계**
   - DB Expert: ERD 설계 → DDL 생성
   - Language Expert: ORM 모델 매핑
   
2. **마이그레이션 관리**
   - DB Expert: ALTER TABLE 스크립트
   - Language Expert: 마이그레이션 도구 설정 (Alembic, Sequelize 등)

3. **쿼리 최적화**
   - DB Expert: 실행 계획 분석, 인덱스 추천
   - Language Expert: ORM 쿼리 최적화

### ⚡ 캐시 데이터베이스 (Redis)

#### 협업 패턴
1. **캐시 전략 수립**
   - Language Expert: 캐시가 필요한 데이터 식별
   - Redis Expert: 캐시 패턴 및 TTL 전략 제시

2. **데이터 구조 선택**
   - Language Expert: 애플리케이션 요구사항 정의
   - Redis Expert: 최적 Redis 데이터 타입 선택

### 🍃 NoSQL 데이터베이스 (MongoDB)

#### 협업 패턴
1. **스키마리스 설계**
   - Language Expert: 도큐먼트 구조 정의
   - MongoDB Expert: 임베딩 vs 참조 전략 결정

2. **집계 파이프라인**
   - Language Expert: 비즈니스 로직 요구사항
   - MongoDB Expert: 효율적인 집계 쿼리 작성

## 충돌 해결 및 우선순위

### 🚨 의견 충돌 시 해결 원칙

#### 1. 기술적 충돌
```
예시: 인덱스 설계 의견 차이
- DB Expert: "복합 인덱스 (status, created_at) 권장"
- Language Expert: "개별 인덱스가 ORM에서 유연함"

해결: Claude가 성능 테스트 결과를 바탕으로 결정
```

#### 2. 우선순위 설정
1. **데이터 일관성** > 개발 편의성
2. **성능** > 코드 단순성  
3. **보안** > 기능 구현 속도
4. **확장성** > 초기 구현 복잡도

### 🔧 협업 최적화 가이드라인

#### Do's (권장사항)
- ✅ 명확한 인터페이스 정의 (API ↔ DB)
- ✅ 버전 관리를 통한 스키마 진화
- ✅ 각 전문가의 권장사항 문서화
- ✅ 성능 테스트 결과 공유

#### Don'ts (피해야 할 것)
- ❌ 언어 에이전트가 직접 DB 스키마 수정
- ❌ DB 에이전트가 애플리케이션 로직 관여
- ❌ 에이전트 간 직접 소통 (Claude 우회)
- ❌ 일방적인 기술 결정

## 품질 보증 체크리스트

### 🔍 협업 완료 전 검증사항

#### 기술적 검증
- [ ] 언어별 코딩 표준 준수
- [ ] DB별 최적화 기법 적용
- [ ] 인덱스 전략의 적절성
- [ ] 트랜잭션 범위 검토
- [ ] 보안 취약점 확인

#### 통합 검증  
- [ ] API-DB 인터페이스 일관성
- [ ] 에러 처리 전략 통일
- [ ] 로깅 및 모니터링 설정
- [ ] 백업 및 복구 계획
- [ ] 성능 벤치마크 통과

## 성공 사례 템플릿

### 📋 사용자 인증 시스템 구축

#### 참여 에이전트
- **NodeJSExpert**: Express.js 기반 인증 API
- **RedisExpert**: 세션 관리 및 Rate Limiting  
- **PostgreSQLExpert**: 사용자 정보 저장

#### 협업 결과물
1. **Node.js 코드**: JWT 토큰 관리, bcrypt 암호화
2. **Redis 설정**: 세션 저장, 로그인 시도 제한
3. **PostgreSQL 스키마**: 사용자 테이블, 인덱스 최적화
4. **통합 문서**: API 명세, 보안 정책, 운영 가이드

---

**이 협업 규칙을 통해 각 전문가의 expertise를 최대한 활용하면서도 시스템 전체의 일관성과 품질을 보장합니다.**