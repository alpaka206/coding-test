function solution(edges) {
  const inDegree = {};
  const outDegree = {};
  const nodes = new Set();

  edges.forEach(([from, to]) => {
    nodes.add(from);
    nodes.add(to);
    outDegree[from] = (outDegree[from] || 0) + 1;
    inDegree[to] = (inDegree[to] || 0) + 1;
  });

  let donut = 0;
  let stick = 0;
  let eight = 0;
  let startNode = 0;

  for (let node of nodes) {
    if (outDegree[node] >= 2 && !inDegree[node]) {
      startNode = node;
      break;
    }
  }

  for (let node of nodes) {
    if (node === startNode) continue;

    const inCount = inDegree[node] || 0;
    const outCount = outDegree[node] || 0;

    if (inCount === 0 && outCount === 0) continue;

    if (outCount === 0) stick++;
    else if (outCount === 2) eight++;
  }

  donut = outDegree[startNode] - stick - eight;

  return [startNode, donut, stick, eight];
}
