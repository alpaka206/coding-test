#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAX = 201;

vector<int> adj[MAX];  // 인접 리스트
int match[MAX];  // 축사에 매칭된 소
bool visited[MAX];  // DFS 방문 여부

// DFS를 사용하여 가능한 매칭을 찾기
bool dfs(int cow) {
    for (int barn : adj[cow]) {
        if (visited[barn]) continue;
        visited[barn] = true;

        if (match[barn] == -1 || dfs(match[barn])) {
            match[barn] = cow;
            return true;
        }
    }
    return false;
}

int main() {
    int N, M;
    cin >> N >> M;

    for (int i = 1; i <= N; i++) {
        int S;
        cin >> S;
        for (int j = 0; j < S; j++) {
            int barn;
            cin >> barn;
            adj[i].push_back(barn);
        }
    }

    // match 배열을 -1로 초기화하여 축사가 매칭되지 않은 상태로 설정
    memset(match, -1, sizeof(match));

    int maxMatch = 0;
    for (int cow = 1; cow <= N; cow++) {
        // visited 배열을 false로 초기화하여 모든 축사를 방문하지 않은 상태로 설정
        memset(visited, false, sizeof(visited));
        if (dfs(cow)) {
            maxMatch++;
        }
    }

    cout << maxMatch << endl;

    return 0;
}
