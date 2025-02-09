const fs = require("fs");

function maxIndependentSet(n, edges) {
  // 그래프를 인접 리스트 형태로 생성
  const graph = Array.from({ length: n + 1 }, () => []);
  const visited = Array(n + 1).fill(false); // 방문 여부 체크 배열
  let maxCount = 0; // 최대 선택 가능한 정점 개수

  // 그래프 구성
  edges.forEach(([u, v]) => {
    graph[u].push(v);
    graph[v].push(u);
  });

  function dfs(node) {
    if (visited[node]) return 0; // 이미 방문한 노드는 탐색하지 않음
    visited[node] = true; // 현재 노드 방문 체크

    let childCount = 0; // 현재 노드를 선택하지 않을 경우 ( 자식 노드들만 선택)
    let subCount = 1; // 현재 노드를 포함하는 경우 (최소 1개)

    // 현재 노드의 모든 이웃을 확인
    for (let neighbor of graph[node]) {
      if (!visited[neighbor]) {
        visited[neighbor] = true; // 방문 처리
        for (let next of graph[neighbor]) {
          if (!visited[next]) {
            childCount += dfs(next); // 이웃의 이웃(2단계 거리) 탐색
          }
        }
      }
    }
    // 현재 노드를 포함하는 경우와 포함하지 않는 경우 중 최댓값 반환
    return Math.max(childCount, subCount + childCount);
  }

  // 그래프가 연결되어 있지 않을 수도 있으므로 모든 정점을 확인
  for (let i = 1; i <= n; i++) {
    if (!visited[i]) {
      maxCount += dfs(i); // 각 컴포넌트의 최대 독립 정점 개수를 더함
    }
  }

  return maxCount; // 최종 결과 반환
}

// 입력 처리
const input = fs.readFileSync("/dev/stdin").toString().trim().split("\n");
const [N, M] = input[0].split(" ").map(Number); // 첫 줄: 정점 개수(N)와 간선 개수(M)
const edges = input.slice(1).map((line) => line.split(" ").map(Number)); // 다음 M개의 줄에서 간선 정보 읽기

console.log(maxIndependentSet(N, edges));
