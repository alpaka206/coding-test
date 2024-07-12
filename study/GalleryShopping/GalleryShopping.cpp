#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// 슬라이딩 윈도우 O(N^2)
// 이분 탐색 O(N logN) min,max 값찾기!
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    long long L, R;
    cin >> N >> L >> R;
    vector<long long> prices(N);
    vector<long long> prices_sum(N + 1, 0);
    for (int i = 0; i < N; ++i) {
        cin >> prices[i];
        prices_sum[i + 1] = prices_sum[i] + prices[i];// 누적 합 계산
    }

    int count = 0;

    // 가능한 모든 (a, b) 쌍 계산
    for (int i = 0; i < N; ++i) {
        long long min_sum = prices_sum[i] + L;
        long long max_sum = prices_sum[i] + R;
        
        auto lower = lower_bound(prices_sum.begin() + i + 1, prices_sum.end(), min_sum);//최소 지점 찾기
        auto upper = upper_bound(prices_sum.begin() + i + 1, prices_sum.end(), max_sum);//최대 지점 찾기

        count += distance(lower, upper);// 사이는 모두 가능하므로 모두 포함
    }

    cout << count << endl;

    return 0;
}
