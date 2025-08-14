import random


def generate_answer():
    """1-9 사이의 중복되지 않는 3개의 숫자 리스트 생성"""
    numbers = list(range(1, 10))
    return random.sample(numbers, 3)


def check_guess(answer, guess):
    """스트라이크, 볼 판정 로직"""
    strikes = 0
    balls = 0
    
    for i in range(3):
        if guess[i] == answer[i]:
            strikes += 1
        elif guess[i] in answer:
            balls += 1
    
    return strikes, balls


def validate_input(user_input):
    """사용자 입력값 검증"""
    # 길이 체크
    if len(user_input) != 3:
        return False, "3자리 숫자를 입력해주세요."
    
    # 숫자 체크
    if not user_input.isdigit():
        return False, "숫자만 입력해주세요."
    
    # 숫자를 리스트로 변환
    numbers = [int(d) for d in user_input]
    
    # 0 포함 체크
    if 0 in numbers:
        return False, "1~9 사이의 숫자만 입력해주세요."
    
    # 중복 체크
    if len(set(numbers)) != 3:
        return False, "중복되지 않는 숫자를 입력해주세요."
    
    return True, numbers


def display_result(strikes, balls):
    """게임 결과 출력"""
    if strikes == 3:
        return "3S - 정답입니다!"
    elif strikes == 0 and balls == 0:
        return "아웃"
    else:
        result = ""
        if strikes > 0:
            result += f"{strikes}S"
        if balls > 0:
            if result:
                result += " "
            result += f"{balls}B"
        return result


def main():
    """게임 루프 및 사용자 인터랙션 처리"""
    print("=" * 40)
    print("🥎 숫자 야구 게임에 오신 것을 환영합니다! 🥎")
    print("=" * 40)
    print("규칙:")
    print("- 컴퓨터가 1~9 사이의 서로 다른 3개 숫자를 생성했습니다.")
    print("- 숫자와 위치가 모두 맞으면 스트라이크(S)")
    print("- 숫자는 맞지만 위치가 틀리면 볼(B)")
    print("- 맞는 숫자가 없으면 아웃")
    print("- 9번의 기회 안에 정답을 맞춰보세요!")
    print("=" * 40)
    
    answer = generate_answer()
    max_attempts = 9
    attempts = 0
    
    while attempts < max_attempts:
        print(f"\n시도 {attempts + 1}/{max_attempts}")
        user_input = input("3자리 숫자를 입력하세요: ").strip()
        
        # 입력값 검증
        is_valid, result = validate_input(user_input)
        if not is_valid:
            print(f"❌ {result}")
            continue
        
        attempts += 1
        guess = result
        
        # 정답 체크
        strikes, balls = check_guess(answer, guess)
        result_message = display_result(strikes, balls)
        print(f"결과: {result_message}")
        
        # 승리 조건
        if strikes == 3:
            print(f"\n🎉 축하합니다! {attempts}번만에 정답을 맞췄습니다! 🎉")
            return
    
    # 패배
    print(f"\n😢 아쉽습니다! 9번의 기회를 모두 사용했습니다.")
    print(f"정답은 {''.join(map(str, answer))}였습니다.")


def test_game_logic():
    """게임 로직 테스트"""
    print("게임 로직 테스트 시작...")
    
    # 정답 생성 테스트
    answer = [1, 2, 3]
    print(f"테스트 정답: {answer}")
    
    # 테스트 케이스들
    test_cases = [
        ([1, 2, 3], "3S"),  # 정답
        ([1, 2, 4], "2S"),  # 2스트라이크
        ([1, 3, 2], "1S 2B"),  # 1스트라이크 2볼
        ([2, 3, 1], "3B"),  # 3볼
        ([4, 5, 6], "아웃"),  # 아웃
        ([1, 4, 5], "1S"),  # 1스트라이크
    ]
    
    for guess, expected in test_cases:
        strikes, balls = check_guess(answer, guess)
        result = display_result(strikes, balls)
        print(f"추측: {guess} -> {result} (예상: {expected})")
    
    # 입력 검증 테스트
    print("\n입력 검증 테스트:")
    validation_tests = [
        ("123", True),
        ("12", False),
        ("1234", False),
        ("abc", False),
        ("112", False),
        ("012", False),
    ]
    
    for test_input, should_be_valid in validation_tests:
        is_valid, result = validate_input(test_input)
        status = "✓" if is_valid == should_be_valid else "✗"
        print(f"{status} 입력 '{test_input}': {is_valid} (예상: {should_be_valid})")
    
    print("\n게임 로직 테스트 완료!")


if __name__ == "__main__":
    import sys
    if len(sys.argv) > 1 and sys.argv[1] == "test":
        test_game_logic()
    else:
        main()