#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

// 상어의 구조체 정의
struct Shark {
    int r, c, s, d, z; // 상어의 위치 (r, c), 속도(s), 방향(d), 크기(z)
    bool alive; // 상어의 생존 여부
};

int R, C, M; // 격자판의 크기 R, C와 상어의 수 M
vector<Shark> sharks; // 상어들을 저장할 벡터
int grid[101][101]; // 격자판, 각 칸에는 상어의 인덱스가 저장됨

// 방향을 나타내는 배열: 1: 위, 2: 아래, 3: 오른쪽, 4: 왼쪽
int direction[5][2] = { {0, 0}, {-1, 0}, {1, 0}, {0, 1}, {0, -1} };

// 상어를 이동시키는 함수
void moveSharks() {
    int newGrid[101][101];
    memset(newGrid, -1, sizeof(newGrid)); // 새로운 격자판 초기화

    // 모든 상어를 이동시킴
    for (int i = 0; i < M; ++i) {
        if (!sharks[i].alive) continue; // 죽은 상어는 무시

        Shark& shark = sharks[i];
        int speed = shark.s;
        int r = shark.r;
        int c = shark.c;
        int d = shark.d;

        // 이동 속도를 격자판 크기에 맞게 조정
        if (d == 1 || d == 2) speed %= (2 * (R - 1)); // 상하 이동
        else speed %= (2 * (C - 1)); // 좌우 이동

        // 상어를 속도만큼 이동
        for (int j = 0; j < speed; ++j) {
            if (r == 1 && d == 1) d = 2;   // 위쪽 끝에 도달했을 때 방향 전환 (위 -> 아래)
            else if (r == R && d == 2) d = 1; // 아래쪽 끝에 도달했을 때 방향 전환 (아래 -> 위)
            else if (c == 1 && d == 4) d = 3; // 왼쪽 끝에 도달했을 때 방향 전환 (왼쪽 -> 오른쪽)
            else if (c == C && d == 3) d = 4; // 오른쪽 끝에 도달했을 때 방향 전환 (오른쪽 -> 왼쪽)

            // 방향에 따라 상어의 위치 이동
            r += direction[d][0];
            c += direction[d][1];
        }

        // 상어의 새로운 위치와 방향 업데이트
        shark.r = r;
        shark.c = c;
        shark.d = d;

        // 새로운 위치에 상어가 없거나, 현재 상어가 더 크면 그 위치에 현재 상어 배치
        if (newGrid[r][c] == -1 || sharks[newGrid[r][c]].z < shark.z) {
            if (newGrid[r][c] != -1) sharks[newGrid[r][c]].alive = false; // 기존 상어 죽임
            newGrid[r][c] = i; // 현재 상어 배치
        }
        else {
            shark.alive = false; // 현재 상어 죽임
        }
    }

    // 새로운 격자판을 기존 격자판으로 복사
    memcpy(grid, newGrid, sizeof(grid));
}

int main() {
    cin >> R >> C >> M;
    memset(grid, -1, sizeof(grid)); // 격자판 초기화

    // 상어들의 초기 상태 입력
    for (int i = 0; i < M; ++i) {
        int r, c, s, d, z;
        cin >> r >> c >> s >> d >> z;
        sharks.push_back({ r, c, s, d, z, true });
        grid[r][c] = i;
    }

    int totalSize = 0; // 잡은 상어 크기의 합

    // 낚시왕이 1열부터 C열까지 이동
    for (int col = 1; col <= C; ++col) {
        // 현재 열에서 가장 가까운 상어를 잡음
        for (int row = 1; row <= R; ++row) {
            if (grid[row][col] != -1 && sharks[grid[row][col]].alive) {
                totalSize += sharks[grid[row][col]].z;
                sharks[grid[row][col]].alive = false;
                grid[row][col] = -1;
                break;
            }
        }

        // 상어 이동
        moveSharks();
    }

    // 결과 출력
    cout << totalSize << endl;
    return 0;
}
