#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

typedef pair<int, int> pii;
const int INF = INT_MAX;

vector<vector<pii>> graph_a, graph_b;
vector<int> dist_a, dist_b;

void dijkstra(int start, vector<vector<pii>>& graph, vector<int>& dist) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dist[start] = 0;
    pq.push({ 0, start });

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto& edge : graph[u]) {
            int v = edge.first;
            int w = edge.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({ dist[v], v });
            }
        }
    }
}

int main() {
    int N_a, M_a, N_b, M_b;
    cin >> N_a >> M_a >> N_b >> M_b;

    graph_a.resize(N_a + 1);
    graph_b.resize(N_b + 1);
    dist_a.resize(N_a + 1, INF);
    dist_b.resize(N_b + 1, INF);

    for (int i = 0; i < M_a; ++i) {
        int u, v, d;
        cin >> u >> v >> d;
        graph_a[u].push_back({ v, d });
        graph_a[v].push_back({ u, d });
    }

    for (int i = 0; i < M_b; ++i) {
        int u, v, d;
        cin >> u >> v >> d;
        graph_b[u].push_back({ v, d });
        graph_b[v].push_back({ u, d });
    }

    int result = INF;
    for (int i = 1; i <= N_a; ++i) {
        fill(dist_a.begin(), dist_a.end(), INF);
        dijkstra(i, graph_a, dist_a);

        for (int j = 1; j <= N_b; ++j) {
            fill(dist_b.begin(), dist_b.end(), INF);
            dijkstra(j, graph_b, dist_b);

            int max_dist = 0;
            for (int u = 1; u <= N_a; ++u) {
                for (int v = 1; v <= N_b; ++v) {
                    // 포탈 사이의 거리를 abs(i - j) 대신 실제 거리를 고려하여 계산
                    int current_dist = dist_a[u] + dist_b[v];
                    max_dist = max(max_dist, current_dist);
                }
            }
            result = min(result, max_dist);
        }
    }

    cout << result << endl;
    return 0;
}
