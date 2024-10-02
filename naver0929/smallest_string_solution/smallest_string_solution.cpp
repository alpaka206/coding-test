#include <string>

std::string solution(std::string S) {
    std::string smallest = S.substr(1);  // 첫 번째 문자를 제거한 결과로 초기화

    // 모든 위치에서 문자를 하나씩 제거한 결과를 확인
    for (int i = 1; i < S.size(); i++) {
        std::string temp = S.substr(0, i) + S.substr(i + 1);
        if (temp < smallest) {
            smallest = temp;
        }
    }
    
    return smallest;
}