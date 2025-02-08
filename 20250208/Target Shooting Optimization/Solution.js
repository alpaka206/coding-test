const fs = require("fs");

// 입력 처리
const input = fs.readFileSync("/dev/stdin").toString().trim().split("\n");
const [N, K, P] = input[0].split(" ").map(Number);

// 격자판 점수 저장
const board = [];
for (let i = 1; i <= N; i++) {
  board.push(input[i].split(" ").map(Number));
}

// 화살별 힘 저장 (1부터 시작)
const B = input[N + 1].split(" ").map(Number);
B.unshift(0); // B[1]부터 사용하기 위해 0을 추가

// 맨해튼 거리로 점수를 계산하는 함수
function calculateScore(x, y, size) {
  let score = 0;
  for (let i = 0; i < N; i++) {
    for (let j = 0; j < N; j++) {
      if (Math.abs(x - i) + Math.abs(y - j) < size) {
        score += board[i][j];
      }
    }
  }
  return score;
}

// BFS를 이용한 최소 힘 탐색
function findMinForce() {
  let queue = [[0, 0, new Set()]]; // [현재 점수, 총 힘, 사용한 화살 집합]
  let minForce = Infinity;

  while (queue.length > 0) {
    let [currentScore, currentForce, usedArrows] = queue.shift();

    // 정확히 P 점을 만들었다면 최소 힘 갱신
    if (currentScore === P) {
      minForce = Math.min(minForce, currentForce);
      continue;
    }

    // 모든 가능한 화살 배치 탐색
    for (let size = 1; size <= K; size++) {
      if (usedArrows.has(size)) continue; // 이미 사용한 화살이면 스킵

      for (let x = 0; x < N; x++) {
        for (let y = 0; y < N; y++) {
          let newScore = currentScore + calculateScore(x, y, size);
          let newForce = currentForce + B[size];

          // 점수가 목표 P를 초과하면 스킵
          if (newScore > P) continue;

          // 새로운 상태를 큐에 추가
          let newSet = new Set(usedArrows);
          newSet.add(size);
          queue.push([newScore, newForce, newSet]);
        }
      }
    }
  }

  return minForce === Infinity ? -1 : minForce;
}

// 결과 출력
console.log(findMinForce());
