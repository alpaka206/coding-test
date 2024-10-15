class Solution {
    public int[] solution(int day, int k) {
        int[] daysInMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int[] result = new int[12];
        
        for (int i = 0; i < 12; i++) {
            int kDay = (day + k - 1) % 7; // 매달 k일의 요일을 계산
            result[i] = (kDay == 5 || kDay == 6) ? 1 : 0; // 토요일(5) 또는 일요일(6)이면 1, 아니면 0
            day = (day + daysInMonth[i]) % 7; 
        }
        
        return result;
    }
}