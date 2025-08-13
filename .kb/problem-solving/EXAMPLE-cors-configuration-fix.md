# CORS 설정 오류 해결 과정

**날짜**: 2025-08-13
**해결자**: Gemini-Claude 협업
**상태**: 해결됨

## 문제 상황
개발 환경에서 프론트엔드(React, localhost:3000)에서 백엔드 API(FastAPI, localhost:8000)로 요청 시 CORS 에러가 발생

### 증상
- 브라우저 콘솔에 CORS 에러 메시지 출력
- `Access to fetch at 'http://localhost:8000/api/users' from origin 'http://localhost:3000' has been blocked by CORS policy`
- GET 요청은 성공하지만 POST, PUT, DELETE 요청 실패

### 발생 환경
- **OS**: Ubuntu 22.04
- **브라우저**: Chrome 130.0.6723.58
- **백엔드**: FastAPI 0.104.1
- **프론트엔드**: React 18.2.0
- **재현 조건**: 로컬 개발 환경에서 API 호출 시

## 문제 분석

### 원인 조사 과정
1. **가설 1**: CORS 미들웨어 누락 → [FastAPI 설정 확인] → [CORS 미들웨어 없음 확인]
2. **가설 2**: 잘못된 Origin 설정 → [허용된 Origin 확인] → [localhost:3000 누락]
3. **가설 3**: Preflight 요청 차단 → [OPTIONS 메서드 확인] → [OPTIONS 허용 안됨]

### 근본 원인
FastAPI 애플리케이션에 CORS 미들웨어가 설정되지 않아 브라우저의 Same-Origin Policy에 의해 크로스 오리진 요청이 차단됨

## 해결 과정

### 시도한 방법들
1. **방법 1**: 브라우저 CORS 비활성화 → [임시 해결되지만 근본 해결책 아님]
2. **방법 2**: 프록시 설정 → [복잡하고 개발 환경에만 적용됨]
3. **방법 3**: FastAPI CORS 미들웨어 추가 → [성공]

### 최종 해결책
FastAPI에 CORSMiddleware를 추가하여 개발 환경에서 localhost:3000 오리진 허용

```python
from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware

app = FastAPI()

# CORS 미들웨어 추가
app.add_middleware(
    CORSMiddleware,
    allow_origins=["http://localhost:3000"],  # React 개발 서버
    allow_credentials=True,
    allow_methods=["GET", "POST", "PUT", "DELETE", "OPTIONS"],
    allow_headers=["*"],
)
```

### 추가 개선사항
```python
# 환경별 설정으로 개선
import os

ALLOWED_ORIGINS = [
    "http://localhost:3000",  # 개발 환경
    "https://yourdomain.com",  # 프로덕션 환경
]

if os.getenv("ENVIRONMENT") == "development":
    ALLOWED_ORIGINS.append("http://localhost:3001")  # 추가 개발 포트

app.add_middleware(
    CORSMiddleware,
    allow_origins=ALLOWED_ORIGINS,
    allow_credentials=True,
    allow_methods=["GET", "POST", "PUT", "DELETE", "OPTIONS"],
    allow_headers=["*"],
)
```

## 예방 조치
- [ ] 프로젝트 초기 설정 시 CORS 미들웨어 기본 포함
- [ ] 환경별 CORS 설정을 환경 변수로 관리
- [ ] API 개발 가이드에 CORS 설정 방법 문서화
- [ ] 프론트엔드-백엔드 연동 테스트를 CI/CD에 포함

## 학습 내용
- CORS는 브라우저의 보안 기능이며 서버에서 허용해야 함
- Preflight 요청(OPTIONS)도 고려해야 함
- 개발 환경과 프로덕션 환경의 CORS 설정은 달라야 함
- `allow_credentials=True` 시 `allow_origins=["*"]` 사용 불가

## 관련 이슈
- [Issue #123: API 연동 실패](https://github.com/project/issues/123)
- [React에서 Cookie 전송 안됨](../problem-solving/2025-08-12-cookie-credentials-issue.md)

## 참고 자료
- [FastAPI CORS 공식 문서](https://fastapi.tiangolo.com/tutorial/cors/)
- [MDN CORS 가이드](https://developer.mozilla.org/en-US/docs/Web/HTTP/CORS)