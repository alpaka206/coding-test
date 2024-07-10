# 문제 설명

문자열 S가 주어졌을 때, 문자열의 각 다양성에 따른 부분 문자열의 최대 길이를 구하는 문제입니다.

- 문자열의 다양성: 문자열을 구성하는 서로 다른 문자의 개수
- 부분 문자열: 기존 문자열의 연속된 일부 문자들로 만든 문자열

### 요구사항

1. 문자열 S에서 다양성이 1부터 26까지인 부분 문자열 중 가장 긴 문자열의 길이를 각각 구합니다.
2. 다양성이 i인 부분 문자열이 존재하지 않으면 0를 출력합니다.

### 입력 형식

첫째 줄: 문자열의 길이 N (1 ≤ N ≤ 100000)
둘째 줄: 문자열 S (알파벳 소문자로만 이루어짐)

### 출력 형식

총 26개의 줄에 걸쳐 답을 출력합니다.
i번째 줄에는 다양성이 i인 S의 부분 문자열의 최대 길이를 출력합니다. 만약 그러한 부분 문자열이 존재하지 않는다면 ()을 출력합니다.

#### 예시 1

- 입력

```
9
abdaccadd
```

- 출력

```
2
4
7
9
0
0
0
0
0
0
0
0
0
0
0
0
0
0
0
0
0
0
0
0
0
0
```

- 예시 설명
  예제 문자열 abdaccadd에 대해:

다양성 1: 가장 긴 부분 문자열은 cc, dd (길이 2)
다양성 2: 가장 긴 부분 문자열은 acca (길이 4)
다양성 3: 가장 긴 부분 문자열은 daccadd (길이 7)
다양성 4: 가장 긴 부분 문자열은 abdaccadd (길이 9)
다양성 5 이상: 존재하지 않음, 이후 쭉 0

### 해결 방법

1. 슬라이딩 윈도우와 해시맵:
   - 각 다양성에 대해 슬라이딩 윈도우 기법을 사용하여 최대 길이를 찾습니다.
   - 해시맵을 이용해 현재 윈도우의 문자 빈도를 추적합니다.
2. 최대 길이 갱신:
   - 슬라이딩 윈도우를 이동시키면서 다양성 조건을 만족하는 가장 긴 부분 문자열의 길이를 갱신합니다.
3. 출력:
   - 각 다양성에 대해 계산된 최대 길이를 출력합니다. 다양성이 만족되지 않으면 0를 출력합니다.