/*
    Problem: Activity Selection

    We are given two arrays:
    - start[i]  = start time of the i-th activity
    - finish[i] = finish time of the i-th activity

    A person can perform only one activity at a time.

    Goal:
    Select the maximum number of non-overlapping activities.

    Greedy Approach:
    ----------------
    Always select the activity that FINISHES EARLIEST.

    Why?

    If we finish an activity as early as possible, we become free earlier.
    This leaves more time available for future activities.

    Steps:
    1. Store each activity as {startTime, finishTime}.
    2. Sort all activities by finish time in ascending order.
    3. Select the first activity because it finishes earliest.
    4. Remember its finish time.
    5. Check every remaining activity:
       - If its start time is greater than the finish time of the
         previously selected activity, select it.
       - Update the last finish time.
    6. Return the number of selected activities.

    Important:
    The problem says the next activity must start at a time GREATER THAN
    the previous activity's finish time.

    Therefore we use:

        currentStartTime > lastFinishTime

    and NOT:

        currentStartTime >= lastFinishTime

    Greedy Choice:
    --------------
    Earliest finishing activity first.

    This is safe because finishing earlier leaves the maximum possible
    time for selecting more activities afterward.

    Time Complexity:
    O(n log n)
    - Creating activity pairs: O(n)
    - Sorting: O(n log n)
    - Traversing activities: O(n)

    Space Complexity:
    O(n)
    - We store all activities in a separate vector.
*/

class Solution {
public:
    int activitySelection(vector<int>& start, vector<int>& finish) {

        // Store every activity as:
        // {startTime, finishTime}
        vector<pair<int, int>> activities;

        for (int i = 0; i < start.size(); i++) {
            activities.push_back({start[i], finish[i]});
        }

        // Sort by finish time from smallest to largest.
        // .second represents the finish time.
        sort(activities.begin(), activities.end(),
             [](auto& a, auto& b) {
                 return a.second < b.second;
             });

        // We always select the first activity because
        // it has the earliest finish time.
        int selectedCount = 1;

        // Remember when the last selected activity finishes.
        int lastFinishTime = activities[0].second;

        // Start checking from the second activity.
        for (int i = 1; i < activities.size(); i++) {

            int currentStartTime = activities[i].first;
            int currentFinishTime = activities[i].second;

            // Current activity can be selected only if it starts
            // after the previously selected activity has finished.
            if (currentStartTime > lastFinishTime) {

                selectedCount++;

                // We selected this activity, so now this becomes
                // our new last finish time.
                lastFinishTime = currentFinishTime;
            }
        }

        return selectedCount;
    }
};