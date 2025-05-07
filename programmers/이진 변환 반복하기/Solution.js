function solution(s) {
  let count = 0;
  let zero_count = 0;

  while (s != "1") {
    zero_count += (s.match(/0/g) || []).length;
    s = s.replace(/0/g, "");
    s = s.length.toString(2);
    count++;
  }
  return [count, zero_count];
}
