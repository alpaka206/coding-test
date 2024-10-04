#include <vector>
#include <string>

std::string solution(int U, int L, std::vector<int> &C) {
    int N = C.size();
    std::vector<int> top(N, 0), bottom(N, 0);  // 두 행을 나타낼 벡터

    // Step 1: 각 열에 대해 처리
    for (int i = 0; i < N; i++) {
        if (C[i] == 2) {
            // 값이 2인 경우 두 행 모두 1
            if (U > 0 && L > 0) {
                top[i] = 1;
                bottom[i] = 1;
                U--;
                L--;
            } else {
                return "IMPOSSIBLE";
            }
        } else if (C[i] == 1) {
            // 값이 1인 경우 한 행에만 1 할당
            if (U > L && U > 0) {
                top[i] = 1;
                U--;
            } else if (L > 0) {
                bottom[i] = 1;
                L--;
            } else {
                return "IMPOSSIBLE";
            }
        }
        // 값이 0인 경우는 이미 두 행 모두 0으로 초기화되어 있으므로 처리할 필요 없음
    }

    // Step 2: U와 L이 정확히 0이어야 함
    if (U != 0 || L != 0) {
        return "IMPOSSIBLE";
    }

    // Step 3: 결과 문자열로 변환
    std::string top_row = "", bottom_row = "";
    for (int i = 0; i < N; i++) {
        top_row += std::to_string(top[i]);
        bottom_row += std::to_string(bottom[i]);
    }

    return top_row + "," + bottom_row;
}