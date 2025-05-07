function solution(n) {
  const n_count = n.toString(2).match(/1/g).length;
  while (true) {
    n++;
    if (n.toString(2).match(/1/g).length === n_count) return n;
  }
}
