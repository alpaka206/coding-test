function solution(bombs) {
  let isSorted = true;
  for (let i = 1; i < bombs.length; i++) {
    if (bombs[i] < bombs[i - 1]) {
      isSorted = false;
      break;
    }
  }
  if (!isSorted) {
    bombs.sort((a, b) => a - b);
  }
  let time = 0;
  let count = 0;

  for (let i = 0; i < bombs.length; i++) {
    if (time >= bombs[i]) {
      break;
    }
    count++;
    time++;
  }

  return count;
}

console.log(solution(JSON.parse(`[3, 1, 2, 4]`)));
console.log(solution(JSON.parse(`[2, 2, 2, 2]`)));
