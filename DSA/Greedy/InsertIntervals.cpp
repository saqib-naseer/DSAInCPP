class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals,
                               vector<int>& newInterval) {

        vector<vector<int>> result;

        for (int i = 0; i < intervals.size(); i++) {

            int existingStart = intervals[i][0];
            int existingEnd = intervals[i][1];

            int newStart = newInterval[0];
            int newEnd = newInterval[1];

            // CASE 1:
            // Existing interval is completely BEFORE newInterval.
            //
            // [1,2]       [4,8]
            //
            // Just keep the existing interval.
            if (existingEnd < newStart) {

                result.push_back(intervals[i]);
            }

            // CASE 2:
            // Existing interval is completely AFTER newInterval.
            //
            // [4,8]       [12,16]
            //
            // newInterval is now complete, so save it.
            else if (existingStart > newEnd) {

                result.push_back(newInterval);

                // Current existing interval becomes our new interval
                // to handle from now on.
                newInterval = intervals[i];
            }

            // CASE 3:
            // Neither completely before nor completely after.
            // Therefore they OVERLAP.
            //
            // existing:   [3,5]
            // new:          [4,8]
            //
            // merged:     [3,8]
            else {

                newInterval[0] = min(newStart, existingStart);
                newInterval[1] = max(newEnd, existingEnd);
            }
        }

        // Whatever interval is still in our hand
        // must be added at the end.
        result.push_back(newInterval);

        return result;
    }
};