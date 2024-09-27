#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> heights(N);
    for (int i = 0; i < N; ++i) {
        cin >> heights[i];
    }

    // Stack to store the indices of mountains
    stack<int> s;
    unordered_map<int, vector<int>> same_height_indices;
    
    for (int i = 0; i < N; ++i) {
        same_height_indices[heights[i]].push_back(i);
    }

    int total_bridges = 0;

    for (auto& entry : same_height_indices) {
        vector<int>& indices = entry.second;
        int size = indices.size();
        
        for (int i = 0; i < size; ++i) {
            for (int j = i + 1; j < size; ++j) {
                bool can_build = true;
                for (int k = indices[i] + 1; k < indices[j]; ++k) {
                    if (heights[k] >= heights[indices[i]]) {
                        can_build = false;
                        break;
                    }
                }
                if (can_build) {
                    ++total_bridges;
                }
            }
        }
    }

    cout << total_bridges << endl;

    return 0;
}