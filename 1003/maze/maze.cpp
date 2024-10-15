#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

const int MAX = 254;
int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

struct Point {
    int x, y;
};

int n, m;
char maze[MAX][MAX];
int dist[MAX][MAX]; 
Point start, goal;
vector<int> paths;

bool isValid(int x, int y) {
    return x >= 0 && y >= 0 && x < n && y < m && maze[x][y] != '#';
}

void bfs() {
    queue<Point> q;
    q.push(start);
    dist[start.x][start.y] = 0;

    while (!q.empty()) {
        Point cur = q.front();
        q.pop();

       
        if (cur.x == goal.x && cur.y == goal.y) {
            return;
        }

        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];

            if (isValid(nx, ny) && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[cur.x][cur.y] + 1;
                q.push({ nx, ny });
            }
        }
    }
}

void findAllPaths(Point cur, vector<Point>& path, vector<vector<bool>>& visited) {

    if (cur.x == goal.x && cur.y == goal.y) {
        paths.push_back(path.size());
        return;
    }


    visited[cur.x][cur.y] = true;
    path.push_back(cur);


    for (int i = 0; i < 4; i++) {
        int nx = cur.x + dx[i];
        int ny = cur.y + dy[i];

       
        if (isValid(nx, ny) && !visited[nx][ny]) {
            findAllPaths({ nx, ny }, path, visited);
        }
    }


    path.pop_back();
    visited[cur.x][cur.y] = false;
}

void printMaze() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << maze[i][j];
        }
        cout << endl;
    }
}

void findShortestPath() {
    Point cur = goal;
    while (!(cur.x == start.x && cur.y == start.y)) {
        maze[cur.x][cur.y] = '*';
        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            if (isValid(nx, ny) && dist[nx][ny] == dist[cur.x][cur.y] - 1) {
                cur = { nx, ny };
                break;
            }
        }
    }
    maze[start.x][start.y] = '*';
    maze[goal.x][goal.y] = 'G';
}

int main() {
    ifstream infile("maze.txt");
    if (!infile) {
        cerr << "파일을 열 수 없습니다." << endl;
        return 1;
    }

    string line;
    n = 0;
    while (getline(infile, line)) {
        m = line.length();
        for (int j = 0; j < m; j++) {
            maze[n][j] = line[j];
            dist[n][j] = -1;
            if (line[j] == 'S') {
                start = { n, j };
            }
            else if (line[j] == 'G') {
                goal = { n, j };
            }
        }
        n++;
    }
    infile.close();

    bfs();

    if (dist[goal.x][goal.y] != -1) {
        vector<Point> path; 
        vector<vector<bool>> visited(n, vector<bool>(m, false)); 
        findAllPaths(start, path, visited); 

        for (int pathLen : paths) {
            cout << "==================================== Goal (" << pathLen << ")" << endl;
        }
        cout << endl << endl << "==================================== 최단거리 (" << dist[goal.x][goal.y] << ")" << endl;
        findShortestPath();
        printMaze();
    }
    else {
        cout << "탈출 경로가 없습니다." << endl;
    }

    return 0;
}
