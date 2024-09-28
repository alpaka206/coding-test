function solution(S) {
  // 세 글자 미만의 문자열은 처리할 필요가 없음
  if (S.length < 3) return 0;

  // 새로운 Set을 생성해서 중복을 제거
  let substrings = new Set();

  // 세 글자씩 슬라이싱해서 Set에 추가 (중복 제거)
  for (let i = 0; i <= S.length - 3; i++) {
    let substring = S.slice(i, i + 3);
    substrings.add(substring); // Set에 추가
  }

  // Set의 크기가 서로 다른 세 글자 부분 문자열의 수
  return substrings.size;
}
