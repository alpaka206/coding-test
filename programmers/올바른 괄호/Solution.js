function solution(s) {
  let count = 0;
  for (const char of s) {
    if (char === "(") {
      count += 1;
    } else if (char === ")") {
      count -= 1;
    }
    if (count < 0) {
      return false;
    }
  }

  return count === 0;
}
