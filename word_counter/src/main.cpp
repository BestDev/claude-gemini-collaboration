#include <iostream>
#include <fstream>
#include <string>

class WordCounter {
private:
    size_t lines = 0;
    size_t words = 0;
    size_t chars = 0;
    
    bool in_word = false;
    bool prev_was_newline = true;  // 파일 시작은 새 줄로 간주
    
public:
    void process_char(char c) {
        chars++;
        
        // 줄 수 계산
        if (c == '\n') {
            lines++;
            prev_was_newline = true;
        } else {
            if (prev_was_newline) {
                // 새 줄의 첫 번째 문자이면서 개행이 아닌 경우
                // 이미 줄 카운트는 이전 개행에서 처리됨
            }
            prev_was_newline = false;
        }
        
        // 단어 수 계산
        bool is_whitespace = (c == ' ' || c == '\t' || c == '\n' || c == '\r');
        
        if (!is_whitespace && !in_word) {
            // 공백이 아닌 문자를 만나고 현재 단어 안에 있지 않으면 새 단어 시작
            words++;
            in_word = true;
        } else if (is_whitespace && in_word) {
            // 공백을 만나고 현재 단어 안에 있으면 단어 끝
            in_word = false;
        }
    }
    
    void finalize() {
        // 파일이 개행으로 끝나지 않는 경우 마지막 줄 처리
        if (!prev_was_newline && chars > 0) {
            lines++;
        }
    }
    
    size_t get_lines() const { return lines; }
    size_t get_words() const { return words; }
    size_t get_chars() const { return chars; }
};

bool count_file(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file '" << filename << "'" << std::endl;
        return false;
    }
    
    WordCounter counter;
    char c;
    
    // 한 글자씩 읽어서 처리
    while (file.get(c)) {
        counter.process_char(c);
    }
    
    file.close();
    counter.finalize();
    
    // 출력 형식: [줄 수] [단어 수] [글자 수] [파일 경로]
    std::cout << counter.get_lines() << " " 
              << counter.get_words() << " " 
              << counter.get_chars() << " " 
              << filename << std::endl;
    
    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file1> [file2] ..." << std::endl;
        return 1;
    }
    
    bool all_success = true;
    
    for (int i = 1; i < argc; i++) {
        if (!count_file(argv[i])) {
            all_success = false;
        }
    }
    
    return all_success ? 0 : 1;
}
