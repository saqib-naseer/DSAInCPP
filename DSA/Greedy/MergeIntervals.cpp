/*
    Problem: Merge Intervals

    We are given multiple intervals:
        [start, end]

    Example:
        [1,3], [2,6], [8,10], [15,18]

    Goal:
    Merge intervals that overlap.

    Main Idea:
    1. Sort intervals by their starting time.
    2. Take the first interval as our "current" interval.
    3. Compare every next interval with current.

    Overlap condition:

        nextStart <= currentEnd

    If they overlap:
        Extend the current interval's end.

        currentEnd = max(currentEnd, nextEnd)

    If they DON'T overlap:
        Current interval is complete.
        Add it to the answer and make the next interval our new current.

    Finally:
        Add the last current interval to the answer.

    Time Complexity:
        O(n log n) because of sorting.

    Space Complexity:
        O(n) for the result.
*/

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {

        // Sort intervals by starting time.
        sort(intervals.begin(), intervals.end());

        // This will contain our final merged intervals.
        vector<vector<int>> result;

        // Start with the first interval.
        vector<int> current = intervals[0];

        // Start checking from the second interval.
        for (int i = 1; i < intervals.size(); i++) {

            int nextStart = intervals[i][0];
            int nextEnd = intervals[i][1];

            int currentEnd = current[1];

            // If next interval starts before or exactly when
            // current interval ends, they overlap.
            if (nextStart <= currentEnd) {

                // Merge them by extending the ending.
                current[1] = max(current[1], nextEnd);
            }

            // No overlap.
            else {

                // Current interval is finished,
                // so save it in the result.
                result.push_back(current);

                // The next interval now becomes our current interval.
                current = intervals[i];
            }
        }

        // The last current interval is still not inside result,
        // so add it.
        result.push_back(current);

        return result;
    }
};