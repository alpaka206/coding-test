#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

const int MAX = 254;
int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

struct Point {
    int x, y, cost, heuristic;
    bool operator<(const Point& other) const {
        return (cost + heuristic) > (other.cost + other.heuristic);
    }
};

int n, m;
char maze[MAX][MAX];
int dist[MAX][MAX];
Point start, goal;

bool isValid(int x, int y) {
    return x >= 0 && y >= 0 && x < n && y < m && maze[x][y] != '#';
}

int heuristic(Point a, Point b) {
    return abs(a.x - b.x) + abs(a.y - b.y); 
}

void aStar() {
    priority_queue<Point> pq;
    pq.push({ start.x, start.y, 0, heuristic(start, goal) });
    dist[start.x][start.y] = 0;

    while (!pq.empty()) {
        Point cur = pq.top();
        pq.pop();

        if (cur.x == goal.x && cur.y == goal.y) {
            return; 
        }

        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];

            if (isValid(nx, ny)) {
                int newCost = dist[cur.x][cur.y] + 1;
                if (newCost < dist[nx][ny]) {
                    dist[nx][ny] = newCost;
                    pq.push({ nx, ny, newCost, heuristic({nx, ny}, goal) });
                }
            }
        }
    }
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
                cur = { nx, ny, 0, 0 };
                break;
            }
        }
    }
    maze[start.x][start.y] = '*'; 
    maze[goal.x][goal.y] = 'G';   
}

int main() {
    ifstream infile("maze2.txt");
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
            dist[n][j] = 1e9; 
            if (line[j] == 'S') {
                start = { n, j, 0, 0 };
            }
            else if (line[j] == 'G') {
                goal = { n, j, 0, 0 };
            }
        }
        n++;
    }
    infile.close();

    aStar(); 

    if (dist[goal.x][goal.y] != 1e9) {
        cout << "============================== 최단거리: (" << dist[goal.x][goal.y] << ")" << endl << endl << endl;
        findShortestPath();
        printMaze();
    }
    else {
        cout << "탈출 경로가 없습니다." << endl;
    }

    return 0;
}
