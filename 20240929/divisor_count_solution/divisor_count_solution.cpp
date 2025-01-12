#include <vector>

std::vector<int> solution(std::vector<int> &A) {
    int N = A.size();               // 배열의 크기
    std::vector<int> result(N, 0);  // 결과 배열 초기화 (0으로 초기화)

    // 각 요소에 대해 그 이전에 나온 숫자들 중 약수(divisor)를 찾는다.
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < i; j++) {
            if (A[i] % A[j] == 0) {  // 약수인 경우
                result[i]++;
            }
        }
    }

    return result;  // 결과 배열 반환
}