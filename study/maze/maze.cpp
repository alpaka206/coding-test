#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

struct Point {
    int y, x, dist;
};

int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<vector<char>> maze(N, vector<char>(N));
    Point start, end;
    unordered_map<char, Point> wormholes;
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> maze[i][j];
            if (maze[i][j] == 'S') start = { i, j, 1 };
            if (maze[i][j] == 'E') end = { i, j, 0 };
            if (maze[i][j] == 'A' || maze[i][j] == 'a' || maze[i][j] == 'B' || maze[i][j] == 'b') {
                wormholes[maze[i][j]] = { i, j, 0 };
            }
        }
    }

    queue<Point> q;
    vector<vector<bool>> visited(N, vector<bool>(N, false));

    q.push(start);
    visited[start.y][start.x] = true;

    while (!q.empty()) {
        Point current = q.front();
        q.pop();

        // 현재 위치가 탈출구인지 확인
        if (current.y == end.y && current.x == end.x) {
            cout << current.dist << endl;
            return 0;
        }

        // 웜홀에 도착하면 무조건 웜홀을 통해 이동
        if (maze[current.y][current.x] == 'A' || maze[current.y][current.x] == 'B') {
            char portal = maze[current.y][current.x];
            char correspondingPortal = portal == 'A' ? 'a' : 'b';
            Point target = wormholes[correspondingPortal];
            if (!visited[target.y][target.x]) {
                visited[target.y][target.x] = true;
                q.push({ target.y, target.x, current.dist + 1 });
            }
            continue;  // 다른 방향으로 이동하지 않도록 함
        }

        // 상하좌우로 이동
        for (int i = 0; i < 4; i++) {
            int ny = current.y + dy[i];
            int nx = current.x + dx[i];

            if (ny >= 0 && ny < N && nx >= 0 && nx < N && !visited[ny][nx] && maze[ny][nx] != '1') {
                visited[ny][nx] = true;
                q.push({ ny, nx, current.dist + 1 });
            }
        }
    }

    cout << -1 << endl;
    return 0;
}
