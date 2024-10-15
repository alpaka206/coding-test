class Solution {
    public int solution(int[] events, int limit) {
        int left = 1;
        int right = events[events.length - 1];
        int longestCycle = 0;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (canSetCycle(events, limit, mid)) {
                longestCycle = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return longestCycle;
    }

    private boolean canSetCycle(int[] events, int limit, int cycle) {
        int eventCount = 0;
        int currentTime = 0;

        for (int event : events) {
            if (event >= currentTime + cycle) {
                eventCount = 1;
                currentTime = event - (event % cycle);
            } else {
                eventCount++;
                if (eventCount > limit) {
                    return false;
                }
            }
        }
        return true;
    }
}