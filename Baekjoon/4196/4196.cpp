#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>
#include <vector>
#include <memory.h>

using namespace std;

const int MAX = 100001;

vector<int> adj[MAX];
stack<int> s;

bool finish[MAX]; 
int dfsn[MAX];
int SCCnum[MAX]; 
int indegree[MAX];
int cnt; 
int SCCtotal; 

int dfs(int cur) {
    dfsn[cur] = ++cnt;
    s.push(cur);
    int result = dfsn[cur];
    for (int next : adj[cur]) {
        if (!dfsn[next])
            result = min(result, dfs(next));
        else if (!finish[next])
            result = min(result, dfsn[next]);
    }
    if (result == dfsn[cur]) {
        while (true) {
            int t = s.top();
            s.pop();
            finish[t] = true;
            SCCnum[t] = SCCtotal;
            if (t == cur)
                break;
        }
        SCCtotal++;
    }
    return result;
}

int main() {
    int tc;
    scanf("%d", &tc);
    while (tc--) {
        int V, E;
        scanf("%d %d", &V, &E);
        for (int i = 0; i < MAX; i++)
            adj[i].clear();
        memset(finish, false, sizeof(finish));
        memset(dfsn, 0, sizeof(dfsn));
        memset(SCCnum, 0, sizeof(SCCnum));
        memset(indegree, 0, sizeof(indegree));
        cnt = 0;
        SCCtotal = 0;
        for (int i = 0; i < E; i++) {
            int from, to;
            scanf("%d %d", &from, &to);
            adj[from].push_back(to);
        }
        for (int i = 1; i <= V; i++)
            if (!dfsn[i])
                dfs(i);
        for (int i = 1; i <= V; i++)
            for (int j : adj[i])
                if (SCCnum[i] != SCCnum[j])
                    indegree[SCCnum[j]]++;
        int cnt = 0;
        for (int i = 0; i < SCCtotal; i++)
            if (indegree[i] == 0)
                cnt++;
        printf("%d\n", cnt);
    }
    return 0;
}

