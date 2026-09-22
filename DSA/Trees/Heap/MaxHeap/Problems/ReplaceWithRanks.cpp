class Solution {
public:
// Time:  O(n log n) - sorting
// Space: O(n)       - storing {value, originalIndex}
    void replaceWithRank(vector<int>& arr) {

        // Store {value, originalIndex}.
        // We need the original index because sorting changes element positions.
        vector<pair<int, int>> valueWithIndex;

        for (int i = 0; i < arr.size(); i++) {
            valueWithIndex.push_back({arr[i], i});
        }

        // Default pair sorting:
        // 1. Sort by value (.first)
        // 2. If values are equal, sort by original index (.second)
        // This also ensures earlier duplicates get a smaller rank.
        sort(valueWithIndex.begin(), valueWithIndex.end());

        // Position in the sorted array represents the rank.
        // Put that rank back at the element's original index.
        for (int rank = 0; rank < valueWithIndex.size(); rank++) {

            int originalIndex = valueWithIndex[rank].second;

            arr[originalIndex] = rank;
        }
    }
};