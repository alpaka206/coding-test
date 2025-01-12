function solution(a, b) {
  const parentMap = {};

  // 부모-자식 관계 매핑
  for (let i = 0; i < a.length; i++) {
    if (!parentMap[a[i]]) {
      parentMap[a[i]] = new Set();
    }
    parentMap[a[i]].add(b[i]);
  }

  const allNodes = new Set([...a, ...b]);
  // 루트 노드를 찾는 함수
  function findRoot(node, visited = new Set()) {
    if (visited.has(node)) {
      // 순환 발견
      return null;
    }
    visited.add(node);
    allNodes.delete(node);

    if (!parentMap[node] || parentMap[node].size === 0) {
      return node;
    }

    let root = null;
    for (let parent of parentMap[node]) {
      const result = findRoot(parent, new Set(visited));
      if (result === null) {
        return null;
      }
      if (root === null) {
        root = result;
      } else if (root !== result) {
        // 서로 다른 루트 발견
        return null;
      }
    }
    return root;
  }

  let commonRoot = null;

  for (let node of allNodes) {
    const root = findRoot(node);
    if (root === null) {
      // 순환이 발견되거나 서로 다른 루트가 발견되면 -1 반환
      return -1;
    }
    if (commonRoot === null) {
      commonRoot = root;
    } else if (commonRoot !== root) {
      // 서로 다른 루트 발견
      return -1;
    }
  }

  return commonRoot;
}

// 테스트

console.log(solution([1, 2, 3, 5, 6], [3, 3, 4, 4, 4]));
console.log(solution([1, 3, 3, 4, 5], [2, 2, 4, 5, 1]));
console.log(solution([2, 3, 4, 4, 1], [1, 2, 3, 5, 5]));
console.log(solution([1, 2, 3, 1], [4, 3, 1, 2]));
