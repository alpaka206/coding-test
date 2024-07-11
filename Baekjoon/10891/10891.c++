#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> adj;
int d[100001]; 
int cnt[100001];
int ans = 0;  


int dfs(int u, int p) {
    int c = 0;  
    int f = 0;  

    for (int v : adj[u]) {
        if (v == p) continue;  
        if (d[v] == 0) { 
            d[v] = d[u] + 1;  
            c += dfs(v, u);
        }
        else if (d[u] > d[v]) {  
            c++;
        }
        else if (d[u] < d[v]) { 
            f--;
        }
    }

    cnt[u] = c;
    if (cnt[u] >= 2) ans = 1;// 사이클이 두 개 이상 교차하면 선인장이 아님
    return c + f;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    adj.resize(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    d[1] = 1;  
    dfs(1, 0); 
    printf("%s\n", ans ? "Not cactus" : "Cactus");

    return 0;
}
