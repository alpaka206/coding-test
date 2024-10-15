class Solution {
    public int solution(int[][] office, int k) {
        int n = office.length;
        int maxEmployees = 0;

        // Precompute cumulative sum
        int[][] sum = new int[n + 1][n + 1];
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + office[i - 1][j - 1];
            }
        }

        // Check all possible k x k squares
        for (int i = k; i <= n; i++) {
            for (int j = k; j <= n; j++) {
                int employeesInSquare = sum[i][j] - sum[i - k][j] - sum[i][j - k] + sum[i - k][j - k];
                maxEmployees = Math.max(maxEmployees, employeesInSquare);
            }
        }

        return maxEmployees;
    }
}