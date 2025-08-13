def say_hello():
    """Hello World 메시지를 출력하는 함수"""
    print("Hello, World!")

def say_hello_with_name(name):
    """이름을 포함한 인사말을 출력하는 함수"""
    print(f"Hello, {name}!")

if __name__ == "__main__":
    # 기본 Hello World 출력
    say_hello()
    
    # 사용자 이름과 함께 출력
    say_hello_with_name("Python")