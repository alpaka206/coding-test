function solution(D, T) {
  // 각 쓰레기별로 가장 먼 거리 저장소
  let PMAX = 0;
  let GMAX = 0;
  let MMAX = 0;

  // 각 쓰레기별 방문 횟수 (개수를 계산하기 위해)
  let PCount = 0;
  let GCount = 0;
  let MCount = 0;

  let Distance = 0; // 현재까지의 거리를 저장

  // 가장 먼 거리 구하기
  for (let i = 0; i < D.length; i++) {
    Distance += D[i]; // 현재 집까지의 거리를 누적

    // 'P'의 개수만큼 시간을 더해줌
    const PNum = (T[i].match(/P/g) || []).length; // P의 개수
    if (PNum > 0) {
      PMAX = Distance; // 플라스틱이 포함된 집까지의 최대 거리
      PCount += PNum; // 플라스틱 수거 횟수는 개수만큼 증가
    }

    // 'G'의 개수만큼 시간을 더해줌
    const GNum = (T[i].match(/G/g) || []).length; // G의 개수
    if (GNum > 0) {
      GMAX = Distance; // 유리가 포함된 집까지의 최대 거리
      GCount += GNum; // 유리 수거 횟수는 개수만큼 증가
    }

    // 'M'의 개수만큼 시간을 더해줌
    const MNum = (T[i].match(/M/g) || []).length; // M의 개수
    if (MNum > 0) {
      MMAX = Distance; // 금속이 포함된 집까지의 최대 거리
      MCount += MNum; // 금속 수거 횟수는 개수만큼 증가
    }
  }

  // 각 쓰레기별로 최종 시간 계산
  let PTime = PMAX * 2 + PCount; // 왕복 거리와 수거 시간을 합산
  let GTime = GMAX * 2 + GCount; // 유리
  let MTime = MMAX * 2 + MCount; // 금속

  // 세 트럭 중 가장 오래 걸리는 시간 반환
  return Math.max(PTime, GTime, MTime);
}
