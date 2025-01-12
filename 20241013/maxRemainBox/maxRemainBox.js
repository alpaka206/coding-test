function solution(a, b) {
  const n = a.length;
  const dp = Array(n).fill(0);

  // 초기값 설정
  dp[0] = (a[0] === "x" ? 1 : 0) + (b[0] === "x" ? 1 : 0);

  for (let i = 1; i < n; i++) {
    const currentX = (a[i] === "x" ? 1 : 0) + (b[i] === "x" ? 1 : 0);

    if (i === 1) {
      dp[i] = currentX;
    } else {
      dp[i] = Math.min(dp[i - 1], dp[i - 2]) + currentX;
    }
  }

  const totalX = (a + b).split("x").length - 1;
  const answer = totalX - Math.min(dp[n - 1], dp[n - 2]);
  return Math.min(answer, Math.floor(n));
}

console.log(solution("..x..", "..xx.")); //2
console.log(solution(".xxx.", "xx.xx")); //4
console.log(solution("x.x.x", ".x.x.")); //3
console.log(solution("..xxx..", "xxx...")); // 4
console.log(solution("x...x...x", "..x...x..")); //5
console.log(solution(".xxxx..", "xxx...x")); // 5
console.log(solution("xxxxxxx", "xxxxxxx")); //7
