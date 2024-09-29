function solution(D, T) {
  let plasticTime = 0;
  let glassTime = 0;
  let metalTime = 0;

  let lastPlasticHouse = -1;
  let lastGlassHouse = -1;
  let lastMetalHouse = -1;

  // 각 집마다 수거해야 할 쓰레기 종류에 따라 시간을 계산한다
  for (let i = 0; i < D.length; i++) {
    const distance = D[i];
    const trashTypes = T[i];

    if (trashTypes.includes("P")) {
      // 플라스틱 쓰레기를 수거하는 트럭의 시간을 갱신
      plasticTime += 1; // 쓰레기를 수거하는 시간 1분
      lastPlasticHouse = i;
    }

    if (trashTypes.includes("G")) {
      // 유리 쓰레기를 수거하는 트럭의 시간을 갱신
      glassTime += 1; // 쓰레기를 수거하는 시간 1분
      lastGlassHouse = i;
    }

    if (trashTypes.includes("M")) {
      // 금속 쓰레기를 수거하는 트럭의 시간을 갱신
      metalTime += 1; // 쓰레기를 수거하는 시간 1분
      lastMetalHouse = i;
    }
  }

  // 각 트럭이 마지막으로 방문한 집에서 출발점(0번 집)으로 왕복하는 시간을 더한다.
  if (lastPlasticHouse !== -1) {
    plasticTime += D[lastPlasticHouse] * 2; // 시작점에서 해당 집까지 왕복 시간
  }

  if (lastGlassHouse !== -1) {
    glassTime += D[lastGlassHouse] * 2; // 시작점에서 해당 집까지 왕복 시간
  }

  if (lastMetalHouse !== -1) {
    metalTime += D[lastMetalHouse] * 2; // 시작점에서 해당 집까지 왕복 시간
  }

  // 세 트럭 중 가장 오래 걸리는 시간을 반환한다.
  return Math.max(plasticTime, glassTime, metalTime);
}
