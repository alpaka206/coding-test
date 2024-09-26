#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

vector<int> DiversitySub(const string& s) {
    int n = s.size();
    vector<int> result(26, 0);

    for (int targetDiversity = 1; targetDiversity <= 26; ++targetDiversity) {
        unordered_map<char, int> freq;
        int uniqueCount = 0; 
        int left = 0;
        int maxLen = 0; 

        for (int right = 0; right < n; ++right) {
            if (freq[s[right]]++ == 0) {
                uniqueCount++;
            }

            while (uniqueCount > targetDiversity) {
                if (--freq[s[left]] == 0) {
                    uniqueCount--;
                }
                left++; 
            }

            if (uniqueCount == targetDiversity) {
                maxLen = max(maxLen, right - left + 1);
            }
        }

        result[targetDiversity - 1] = maxLen;
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    string S;
    cin >> N >> S;

    vector<int> result =DiversitySub(S);

    for (int i = 0; i < 26; ++i) {
        if (result[i] == 0) {
            cout << "0\n";
        }
        else {
            cout << result[i] << '\n';
        }
    }

    return 0;
}
