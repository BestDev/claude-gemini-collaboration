# Serena MCP로 UnrealEngine 프로젝트 활성화 - 완벽 가이드

## 목차
- [1. 대규모 코드베이스 효율적 탐색](#1-대규모-코드베이스-효율적-탐색)
- [2. 신규 프로젝트 개발 시 구체적 활용 사례](#2-신규-프로젝트-개발-시-구체적-활용-사례)
- [3. Serena의 핵심 장점](#3-serena의-핵심-장점)
- [4. 언리얼 엔진에서 특히 유용한 이유](#4-언리얼-엔진에서-특히-유용한-이유)
- [5. 실제 워크플로우 예시](#5-실제-워크플로우-예시)
- [6. 메모리 시스템의 이점](#6-메모리-시스템의-이점)
- [7. 비활성화 vs 활성화 비교](#7-비활성화-vs-활성화-비교)
- [8. 블루프린트 작업 활용](#8-블루프린트-작업-활용)
- [결론: 어떤 경우에 도움이 되는가?](#결론-어떤-경우에-도움이-되는가)

---

## 1. 대규모 코드베이스 효율적 탐색

### 일반 도구 vs Serena의 차이

#### 일반 방식 (파일 전체 읽기)
- 파일을 통째로 읽어야 함 → 수천 줄의 불필요한 코드도 읽게 됨
- 언리얼 엔진 파일은 보통 수백~수천 줄
- 토큰을 빠르게 소모하고 컨텍스트 한계에 도달

#### Serena 방식 (심볼 기반 탐색)
- 필요한 클래스/함수만 정확히 찾아서 읽음
- 파일 개요 → 특정 심볼 조회 → 필요한 부분만 읽기
- **토큰 사용량 90% 이상 절감 가능**

### 실제 예시

언리얼 엔진에서 `AActor` 클래스의 `Tick` 함수 구현을 찾고 싶다면:

**일반 도구:**
```
1. Actor.h 파일 전체 읽기 (1000+ 줄)
2. Actor.cpp 파일 전체 읽기 (2000+ 줄)
3. 수동으로 Tick 함수 찾기
```

**Serena:**
```
1. find_symbol(name_path="AActor", depth=1) - 메서드 목록만 조회
2. find_symbol(name_path="AActor/Tick", include_body=True) - Tick만 읽기
3. 필요한 10-20줄만 정확히 획득
```

---

## 2. 신규 프로젝트 개발 시 구체적 활용 사례

### 사례 1: 설계 패턴 참고

**상황**: 새로운 게임에서 인벤토리 시스템을 만들고 싶음

**질문**: "언리얼 엔진에서 아이템 관리는 어떻게 구현되어 있어?"

**Serena 활용:**
```
1. search_for_pattern("Item.*Component|Inventory")
   → 관련 클래스 찾기

2. get_symbols_overview("Engine/Source/Runtime/.../InventoryComponent.h")
   → 클래스 구조 파악

3. find_symbol("UInventoryComponent", depth=1)
   → 주요 메서드 목록 확인

4. find_symbol("UInventoryComponent/AddItem", include_body=True)
   → 구현 방식 상세 확인
```

**결과**: 언리얼의 설계 패턴을 참고하여 자신의 프로젝트에 적용

---

### 사례 2: 특정 기능 구현 방법 학습

**상황**: 캐릭터 이동 시스템을 커스터마이징하고 싶음

**질문**: "CharacterMovementComponent에서 점프 높이는 어떻게 계산되지?"

**Serena 활용:**
```
1. find_symbol("UCharacterMovementComponent/DoJump")
2. find_referencing_symbols → DoJump가 어디서 호출되는지
3. 관련 변수 (JumpZVelocity 등) 추적
```

**결과**: 정확한 구현 로직을 이해하고 자신의 코드에 응용

---

### 사례 3: 코드 참조 추적

**상황**: UGameplayStatics를 어떻게 활용하는지 보고 싶음

**Serena 활용:**
```
find_referencing_symbols("UGameplayStatics/SpawnActor")
→ 엔진 전체에서 SpawnActor가 사용되는 모든 곳을 찾아줌
→ 실제 사용 예제를 다양하게 확인 가능
```

**결과**: 베스트 프랙티스와 일반적인 사용 패턴 학습

---

## 3. Serena의 핵심 장점

### A. 심볼 기반 정확한 검색

```python
# 클래스 상속 구조 파악
find_symbol("ACharacter", depth=0)  # 클래스 선언만
find_symbol("ACharacter", depth=1)  # 멤버 함수까지
find_symbol("ACharacter", depth=2)  # 중첩 클래스까지

# 특정 메서드만 정확히 조회
find_symbol("ACharacter/GetVelocity", include_body=True)
```

### B. 코드 관계 이해

```python
# "이 함수가 어디서 호출되나?"
find_referencing_symbols("BeginPlay", relative_path="Actor.cpp")

# "이 클래스를 상속받는 클래스는?"
search_for_pattern(": public ACharacter", restrict_search_to_code_files=True)
```

### C. 효율적인 편집 (필요 시)

```python
# 특정 메서드만 교체
replace_symbol_body(
    name_path="MyClass/MyMethod",
    relative_path="MyFile.cpp",
    body="새로운 구현"
)

# 새 메서드 추가
insert_after_symbol(
    name_path="MyClass/ExistingMethod",
    relative_path="MyFile.cpp",
    body="void NewMethod() { ... }"
)
```

---

## 4. 언리얼 엔진에서 특히 유용한 이유

### 규모
- **수백만 줄**의 C++ 코드
- 수천 개의 클래스와 수만 개의 함수
- 일반 도구로는 탐색이 매우 비효율적

### 복잡성
- 다층 상속 구조
- 매크로 시스템 (UCLASS, UPROPERTY 등)
- 모듈 간 의존성

### 학습 자료로서의 가치
- 최고 수준의 게임 엔진 설계
- 검증된 디자인 패턴
- 성능 최적화 기법

---

## 5. 실제 워크플로우 예시

### 신규 프로젝트에서 AI 시스템 설계

```
1단계: 언리얼의 AI 구조 파악
   "언리얼 엔진의 AI 시스템 구조를 보여줘"
   → Serena가 AIController, BehaviorTree, Blackboard 등 핵심 클래스 찾기

2단계: 특정 기능 구현 확인
   "BehaviorTree에서 태스크는 어떻게 실행되지?"
   → 관련 메서드만 정확히 조회

3단계: 자신의 프로젝트에 응용
   "이 패턴을 참고해서 우리 프로젝트에 커스텀 AI 태스크 만들어줘"
   → 학습한 패턴을 적용

4단계: 엔진 코드 다시 참조
   "Perception 시스템은 어떻게 구현되어 있지?"
   → 필요할 때마다 즉시 참조
```

---

## 6. 메모리 시스템의 이점

onboarding 과정에서 만든 메모리 파일들:

```
✅ project_overview.md - 프로젝트 전체 구조
✅ code_style_and_conventions.md - 코딩 스타일
✅ suggested_commands.md - 자주 쓰는 명령어
✅ development_guidelines.md - 개발 가이드라인
✅ task_completion_checklist.md - 작업 완료 체크리스트
✅ codebase_structure.md - 코드베이스 구조
```

### 이점:
- 매번 README 다시 읽을 필요 없음
- 프로젝트 규칙을 항상 기억
- 일관된 코드 스타일 유지
- 새 세션에서도 즉시 컨텍스트 확보

---

## 7. 비활성화 vs 활성화 비교

### Serena 없이 (비활성화)

```
사용자: "언리얼에서 FVector 구조체는 어떻게 생겼어?"

AI 동작:
- Grep으로 검색
- 여러 파일 찾음
- 각 파일 전체 읽기
- 토큰 3000+ 사용
- 컨텍스트 한계 도달 가능
```

### Serena 사용 (활성화)

```
사용자: "언리얼에서 FVector 구조체는 어떻게 생겼어?"

AI 동작:
- find_symbol("FVector")
- 정확히 해당 구조체만 조회
- 토큰 100-200 사용
- 효율적!
```

---

## 8. 블루프린트 작업 활용

Serena MCP는 블루프린트 작업에도 **매우 강력한 도움**을 제공합니다. 블루프린트는 C++ 코드 위에서 동작하기 때문에, 언리얼 엔진 소스를 이해하면 블루프린트 설계가 훨씬 쉬워집니다.

### 8.1 블루프린트 노드의 내부 구현 이해

#### 예시 1: "Get Velocity" 노드는 내부적으로 어떻게 동작할까?

**블루프린트 작업 중 상황:**
```
캐릭터의 속도를 가져와서 UI에 표시하고 싶은데,
"Get Velocity" 노드가 정확히 무엇을 반환하는지 궁금함
```

**Serena 활용:**
```
질문: "AActor의 GetVelocity 함수 구현을 보여줘"

Serena 실행:
1. find_symbol("AActor/GetVelocity", include_body=True)
```

**결과 확인:**
```cpp
UFUNCTION(BlueprintCallable, Category="Movement")
FVector GetVelocity() const
{
    if (RootComponent)
    {
        return RootComponent->ComponentVelocity;
    }
    return FVector::ZeroVector;
}
```

**블루프린트 설계에 활용:**
- RootComponent가 없으면 Zero Vector를 반환한다는 것을 알게 됨
- 안전하게 Null 체크 없이 사용 가능
- 컴포넌트의 속도를 추적한다는 것을 이해
- 물리 시뮬레이션 속도와 다를 수 있음을 인지

---

### 8.2 BlueprintCallable 함수 찾기

#### 예시 2: 게임플레이 관련 유용한 함수 찾기

**블루프린트 작업 중 상황:**
```
UGameplayStatics에 어떤 유용한 함수들이 있는지 탐색하고 싶음
특히 블루프린트에서 사용 가능한 것들만
```

**Serena 활용:**
```
질문: "UGameplayStatics에서 BlueprintCallable로 노출된 함수들을 보여줘"

Serena 실행:
1. get_symbols_overview("Engine/Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h")
2. find_symbol("UGameplayStatics", depth=1)
3. search_for_pattern("UFUNCTION.*BlueprintCallable",
                      relative_path="GameplayStatics.h")
```

**발견할 수 있는 것들:**
```cpp
UFUNCTION(BlueprintCallable, Category="Game")
static void BreakHitResult(const FHitResult& Hit, ...);

UFUNCTION(BlueprintCallable, Category="Audio")
static void PlaySoundAtLocation(...);

UFUNCTION(BlueprintCallable, Category="Rendering")
static void SpawnEmitterAtLocation(...);
```

**블루프린트 설계에 활용:**
- 몰랐던 유용한 노드들을 발견
- 각 함수의 파라미터와 사용법 이해
- 블루프린트 라이브러리 노드의 전체 목록 파악

---

### 8.3 BlueprintImplementableEvent 패턴 학습

#### 예시 3: 커스텀 이벤트 시스템 설계

**블루프린트 작업 중 상황:**
```
C++에서 정의하고 블루프린트에서 구현하는 이벤트를 만들고 싶음
언리얼은 어떻게 이런 패턴을 사용하는지 보고 싶음
```

**Serena 활용:**
```
질문: "AActor에서 BlueprintImplementableEvent는 어떻게 사용되는지 예시를 보여줘"

Serena 실행:
1. search_for_pattern("UFUNCTION.*BlueprintImplementableEvent",
                      relative_path="Engine/Source/Runtime/Engine/Classes/GameFramework/Actor.h",
                      context_lines_after=3)
```

**발견 예시:**
```cpp
/** Event when play begins for this actor. */
UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "BeginPlay"))
void ReceiveBeginPlay();

/** Event when this actor takes damage */
UFUNCTION(BlueprintImplementableEvent, BlueprintAuthorityOnly, meta=(DisplayName = "AnyDamage"))
void ReceiveAnyDamage(float Damage, const class UDamageType* DamageType, ...);

/** Event called every frame */
UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "Tick"))
void ReceiveTick(float DeltaSeconds);
```

**블루프린트 설계에 활용:**
- 이벤트 함수는 "Receive" 접두사를 사용하는 패턴 학습
- DisplayName 메타로 블루프린트에서 보기 좋은 이름 설정
- BlueprintAuthorityOnly 같은 네트워크 관련 지정자 이해
- 자신의 C++ 클래스에 동일한 패턴 적용 가능

---

### 8.4 블루프린트 노드 카테고리 구조 이해

#### 예시 4: 잘 정리된 블루프린트 라이브러리 만들기

**블루프린트 작업 중 상황:**
```
커스텀 블루프린트 함수 라이브러리를 만들 때
언리얼처럼 잘 정리된 카테고리 구조를 만들고 싶음
```

**Serena 활용:**
```
질문: "UKismetMathLibrary의 카테고리 구조를 보여줘"

Serena 실행:
1. find_symbol("UKismetMathLibrary", depth=1, include_body=False)
2. search_for_pattern("UFUNCTION.*Category.*Math",
                      relative_path="KismetMathLibrary.h",
                      context_lines_after=2)
```

**발견 예시:**
```cpp
/** Returns the sine of A (expects Radians) */
UFUNCTION(BlueprintPure, Category="Math|Trig", meta=(Keywords="sin"))
static float Sin(float A);

/** Clamps a value between a minimum and maximum */
UFUNCTION(BlueprintPure, Category="Math|Float", meta=(Keywords="min max clamp"))
static float FClamp(float Value, float Min, float Max);

/** Returns a random vector with length of 1 */
UFUNCTION(BlueprintPure, Category="Math|Random")
static FVector RandomUnitVector();
```

**블루프린트 설계에 활용:**
- `Category="Math|Trig"` 같은 서브카테고리 구조 학습
- `meta=(Keywords="...")` 로 검색 키워드 추가
- `BlueprintPure` vs `BlueprintCallable` 차이 이해
- 함수 이름과 주석 작성 스타일 참고

---

### 8.5 블루프린트 타입 시스템 이해

#### 예시 5: 구조체와 열거형 설계

**블루프린트 작업 중 상황:**
```
블루프린트에서 사용할 커스텀 구조체를 만들고 싶은데
어떻게 설계해야 블루프린트에서 사용하기 편할까?
```

**Serena 활용:**
```
질문: "FHitResult 구조체는 어떻게 블루프린트에 노출되어 있어?"

Serena 실행:
1. find_symbol("FHitResult", include_body=True, depth=1)
```

**발견 예시:**
```cpp
USTRUCT(BlueprintType)
struct FHitResult
{
    GENERATED_BODY()

    /** Indicates if this hit was a result of blocking collision */
    UPROPERTY(BlueprintReadOnly)
    uint32 bBlockingHit : 1;

    /** Actor hit by the trace */
    UPROPERTY(BlueprintReadOnly)
    TWeakObjectPtr<class AActor> HitObjectHandle;

    /** Component hit by the trace */
    UPROPERTY(BlueprintReadOnly)
    TWeakObjectPtr<class UPrimitiveComponent> HitComponent;

    /** Distance from the trace start to impact */
    UPROPERTY(BlueprintReadOnly)
    float Distance;

    /** Location of the hit */
    UPROPERTY(BlueprintReadOnly)
    FVector Location;

    // ...
};
```

**블루프린트 설계에 활용:**
- `USTRUCT(BlueprintType)` 필수
- `UPROPERTY(BlueprintReadOnly)` 로 읽기 전용 노출
- `GENERATED_BODY()` 매크로 필요
- TWeakObjectPtr 대신 일반 포인터도 가능
- 구조체 브레이크 노드가 각 프로퍼티를 핀으로 만듦

---

### 8.6 블루프린트 애니메이션 시스템

#### 예시 6: 애니메이션 블루프린트 기능 이해

**블루프린트 작업 중 상황:**
```
Animation Blueprint에서 사용할 수 있는
애니메이션 노드들의 내부 구현이 궁금함
```

**Serena 활용:**
```
질문: "UAnimInstance의 블루프린트 관련 함수들을 보여줘"

Serena 실행:
1. find_symbol("UAnimInstance", depth=1)
2. search_for_pattern("UFUNCTION.*BlueprintCallable.*Anim",
                      relative_path="Engine/Source/Runtime/Engine/Classes/Animation/AnimInstance.h")
```

**발견 예시:**
```cpp
/** Get the current velocity of the owning component */
UFUNCTION(BlueprintCallable, Category="Animation")
FVector GetOwnerVelocity() const;

/** Try to get the pawn owner */
UFUNCTION(BlueprintCallable, Category="Animation")
APawn* TryGetPawnOwner() const;

/** Returns whether this animation is currently running on the game thread */
UFUNCTION(BlueprintPure, Category="Animation")
bool IsRunningParallelEvaluation() const;
```

**블루프린트 설계에 활용:**
- Animation Blueprint에서 사용 가능한 헬퍼 함수들 발견
- 커스텀 AnimInstance 클래스 만들 때 참고
- 이름 짓기 패턴 학습 (Get/Try/Is 접두사)

---

### 8.7 블루프린트 네이티브 이벤트 패턴

#### 예시 7: C++과 블루프린트를 함께 사용하는 패턴

**블루프린트 작업 중 상황:**
```
C++에서 기본 로직을 구현하고
블루프린트에서 확장할 수 있는 함수를 만들고 싶음
```

**Serena 활용:**
```
질문: "BlueprintNativeEvent는 어떻게 구현되어 있어?"

Serena 실행:
1. search_for_pattern("UFUNCTION.*BlueprintNativeEvent",
                      relative_path="Engine/Source/Runtime/Engine/Classes/GameFramework/Actor.h",
                      context_lines_after=5)
```

**발견 예시:**
```cpp
/**
 * Event when this actor has the input focus
 * C++ implementation, can be overridden in Blueprint
 */
UFUNCTION(BlueprintNativeEvent, Category="Input")
void ReceiveActorOnInputTouchBegin(const ETouchIndex::Type FingerIndex);

// 실제 구현부 (.cpp 파일)
void AActor::ReceiveActorOnInputTouchBegin_Implementation(const ETouchIndex::Type FingerIndex)
{
    // C++ 기본 구현
    NotifyActorOnInputTouchBegin(FingerIndex);
}
```

**블루프린트 설계에 활용:**
- `BlueprintNativeEvent` 사용 시 `_Implementation` 함수 구현 필요
- 블루프린트에서 "Parent: FunctionName" 호출로 C++ 기본 구현 사용 가능
- 유연한 확장 구조 설계 가능

---

### 8.8 실전 예시: 데미지 시스템 블루프린트 설계

#### 종합 활용 예시

**목표:** 게임에 커스텀 데미지 시스템을 블루프린트로 구현하고 싶음

**Serena 활용 워크플로우:**

**1단계: 언리얼의 데미지 시스템 구조 파악**
```
질문: "AActor의 TakeDamage 함수를 보여줘"

Serena 실행:
→ find_symbol("AActor/TakeDamage", include_body=True)

발견:
UFUNCTION(BlueprintCallable, Category="Damage")
virtual float TakeDamage(
    float DamageAmount,
    struct FDamageEvent const& DamageEvent,
    class AController* EventInstigator,
    AActor* DamageCauser
);
```

**2단계: 데미지 이벤트 구조 확인**
```
질문: "FDamageEvent 구조체를 보여줘"

Serena 실행:
→ find_symbol("FDamageEvent", depth=1)

발견:
USTRUCT(BlueprintType)
struct FDamageEvent
{
    UPROPERTY(BlueprintReadOnly)
    TSubclassOf<UDamageType> DamageTypeClass;
    // ...
};
```

**3단계: 블루프린트 이벤트 확인**
```
질문: "데미지 관련 BlueprintImplementableEvent를 찾아줘"

Serena 실행:
→ search_for_pattern("BlueprintImplementableEvent.*Damage")

발견:
UFUNCTION(BlueprintImplementableEvent)
void ReceiveAnyDamage(float Damage, const UDamageType* DamageType, ...);

UFUNCTION(BlueprintImplementableEvent)
void ReceivePointDamage(float Damage, const UDamageType* DamageType,
                        FVector HitLocation, ...);

UFUNCTION(BlueprintImplementableEvent)
void ReceiveRadialDamage(float DamageReceived, const UDamageType* DamageType,
                         FVector Origin, ...);
```

**4단계: GameplayStatics 유틸리티 확인**
```
질문: "UGameplayStatics에서 데미지 관련 함수를 찾아줘"

Serena 실행:
→ search_for_pattern("UFUNCTION.*Damage", relative_path="GameplayStatics.h")

발견:
UFUNCTION(BlueprintCallable, Category="Damage")
static float ApplyDamage(
    AActor* DamagedActor,
    float BaseDamage,
    AController* EventInstigator,
    AActor* DamageCauser,
    TSubclassOf<UDamageType> DamageTypeClass
);

UFUNCTION(BlueprintCallable, Category="Damage")
static float ApplyPointDamage(...);

UFUNCTION(BlueprintCallable, Category="Damage")
static float ApplyRadialDamage(...);
```

**블루프린트 설계 결과:**

이제 다음과 같은 정보를 알게 되어 블루프린트 설계 가능:

1. **데미지 주기**: `ApplyDamage` 노드 사용
2. **데미지 받기**: Actor에서 `Event Any Damage` 이벤트 사용
3. **데미지 타입**: UDamageType 클래스 생성하여 종류 구분
4. **다양한 데미지 형태**: Point Damage (정확한 위치), Radial Damage (범위)
5. **커스터마이징**: TakeDamage를 오버라이드하여 고유 로직 추가

---

### 8.9 메타데이터 활용

#### 예시 9: 블루프린트 에디터 UI 커스터마이징

**Serena 활용:**
```
질문: "블루프린트 노드의 메타데이터 옵션들을 보여줘"

Serena 실행:
search_for_pattern("meta\\s*=\\s*\\(",
                   paths_include_glob="**/*Library.h",
                   context_lines_after=0)
```

**발견할 수 있는 메타데이터들:**
```cpp
meta=(DisplayName = "노드 표시 이름")
meta=(Keywords = "검색, 키워드")
meta=(CompactNodeTitle = "간략 제목")
meta=(ToolTip = "도구 설명")
meta=(Category = "카테고리|서브카테고리")
meta=(BlueprintInternalUseOnly = "true")  // 숨김
meta=(WorldContext = "WorldContextObject")
meta=(DefaultToSelf = "Target")
meta=(HidePin = "ParamName")
meta=(ExpandEnumAsExecs = "EnumParam")  // Enum을 실행 핀으로
```

**블루프린트 설계에 활용:**
- 사용자 친화적인 노드 UI 설계
- 검색 편의성 향상
- 고급 노드 동작 커스터마이징

---

### 8.10 실제 블루프린트 작업 시나리오

#### 시나리오: RPG 인벤토리 시스템 블루프린트 설계

**단계별 Serena 활용:**

**1. 구조 파악**
```
질문: "UActorComponent를 상속받는 방식으로 인벤토리를 만들고 싶어.
      언리얼에서 비슷한 컴포넌트 예시를 보여줘"

Serena 실행:
→ find_symbol("UActorComponent", depth=1)
→ 관련 컴포넌트들 찾기
```

**2. 블루프린트 노출 패턴 학습**
```
질문: "컴포넌트에서 블루프린트로 노출하는 변수 패턴을 보여줘"

Serena 실행:
→ search_for_pattern("UPROPERTY.*BlueprintReadWrite.*Component")
```

**3. 이벤트 시스템 설계**
```
질문: "아이템 추가/제거 시 이벤트를 발생시키고 싶어"

Serena 실행:
→ "Delegate" 패턴 검색
→ search_for_pattern("DECLARE_DYNAMIC.*DELEGATE")
```

**4. 블루프린트 함수 라이브러리**
```
질문: "아이템 관련 유틸리티 함수를 만들고 싶어"

Serena 실행:
→ UBlueprintFunctionLibrary 상속 패턴 학습
```

---

### 블루프린트 활용 결론

#### ✅ 블루프린트 작업에 도움이 되는 경우

1. **노드 내부 구현 이해**: "이 노드는 정확히 무엇을 하는가?"
2. **사용 가능한 함수 발견**: "몰랐던 유용한 블루프린트 노드 찾기"
3. **패턴 학습**: "BlueprintCallable, Pure, NativeEvent 등의 차이"
4. **커스텀 블루프린트 기능 제작**: "C++ 클래스를 블루프린트 친화적으로 설계"
5. **구조체/열거형 설계**: "블루프린트에서 사용하기 좋은 데이터 구조"
6. **메타데이터 활용**: "블루프린트 에디터 UI 커스터마이징"
7. **디버깅**: "왜 이 노드가 이렇게 동작하지?"

#### 🎯 핵심 이점

블루프린트는 C++ 래퍼이기 때문에:
- **C++ 소스를 이해 = 블루프린트를 깊이 이해**
- 더 효율적인 블루프린트 설계 가능
- 블루프린트 한계를 알고 C++로 전환 시점 판단
- 언리얼 베스트 프랙티스 학습

#### 💡 블루프린트 작업 추천 워크플로우

```
1. 블루프린트에서 기능 구현 시작
   ↓
2. 막히는 부분이나 궁금한 점 발생
   ↓
3. Serena로 언리얼 엔진 소스 탐색
   ↓
4. 내부 구현과 패턴 이해
   ↓
5. 블루프린트 설계에 반영
   ↓
6. 필요 시 C++로 확장
```

**Serena MCP는 블루프린트 작업자에게도 필수 도구입니다!** 🚀

---

## 결론: 어떤 경우에 도움이 되는가?

### ✅ 도움이 많이 되는 경우

1. **설계 참고**: "언리얼은 이 기능을 어떻게 구현했지?"
2. **패턴 학습**: "프로페셔널한 코드 구조는 어떻게 생겼지?"
3. **기능 이해**: "이 API는 내부적으로 어떻게 동작하지?"
4. **문제 해결**: "비슷한 문제를 엔진에서는 어떻게 해결했지?"
5. **베스트 프랙티스**: "메모리 관리는 어떻게 하는 게 좋지?"

### ⚠️ 제한사항

- Serena는 **읽기/탐색/이해**에 최적화
- 실제 게임 프로젝트 파일 편집은 일반 도구 사용
- 언리얼 엔진 소스를 **참고 자료**로 활용하는 것

### 💡 추천 사용 방법

```
1. UnrealEngine 프로젝트 (Serena 활성화)
   → 참고, 학습, 연구용

2. 자신의 게임 프로젝트 (일반 도구 또는 별도 Serena 프로젝트)
   → 실제 개발용

3. 두 프로젝트를 오가며 작업
   → "언리얼 엔진 보고 → 내 프로젝트에 적용"
```

---

## 핵심 요약

Serena로 활성화한 UnrealEngine 프로젝트는 **거대한 참고 라이브러리**이자 **학습 자료**로 활용하는 것이 가장 효과적입니다!

### 주요 이점
- 🚀 **토큰 효율성**: 90% 이상 절감
- 🎯 **정확한 탐색**: 필요한 코드만 정확히 조회
- 📚 **학습 도구**: 프로페셔널 코드 패턴 학습
- 🔍 **관계 추적**: 함수 호출, 상속 관계 파악
- 💾 **메모리 시스템**: 프로젝트 컨텍스트 영구 보존

### 활용 시나리오
1. 새로운 기능 설계 전 언리얼 구현 방식 연구
2. 복잡한 시스템(AI, 물리, 렌더링 등) 아키텍처 학습
3. 성능 최적화 기법 참고
4. 디버깅 시 내부 동작 이해
5. 커스텀 엔진 기능 개발 시 기존 코드 참조
