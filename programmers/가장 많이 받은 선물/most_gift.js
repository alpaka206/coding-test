function solution(friends, gifts) {
  const giftMap = new Map();
  const giftScore = new Map();
  const nextGifts = new Map();

  friends.forEach((friend) => {
    giftMap.set(friend, new Map());
    giftScore.set(friend, 0);
    nextGifts.set(friend, 0);
  });

  gifts.forEach((gift) => {
    const [giver, receiver] = gift.split(" ");
    giftScore.set(giver, giftScore.get(giver) + 1);
    giftScore.set(receiver, giftScore.get(receiver) - 1);
    giftMap
      .get(giver)
      .set(receiver, (giftMap.get(giver).get(receiver) || 0) + 1);
  });

  for (let i = 0; i < friends.length; i++) {
    for (let j = i + 1; j < friends.length; j++) {
      const friendA = friends[i];
      const friendB = friends[j];
      const aToB = giftMap.get(friendA).get(friendB) || 0;
      const bToA = giftMap.get(friendB).get(friendA) || 0;

      if (aToB > bToA) {
        nextGifts.set(friendA, nextGifts.get(friendA) + 1);
      } else if (aToB < bToA) {
        nextGifts.set(friendB, nextGifts.get(friendB) + 1);
      } else {
        const scoreA = giftScore.get(friendA);
        const scoreB = giftScore.get(friendB);
        if (scoreA > scoreB) {
          nextGifts.set(friendA, nextGifts.get(friendA) + 1);
        } else if (scoreA < scoreB) {
          nextGifts.set(friendB, nextGifts.get(friendB) + 1);
        }
      }
    }
  }

  var answer = Math.max(...nextGifts.values());
  return answer;
}
