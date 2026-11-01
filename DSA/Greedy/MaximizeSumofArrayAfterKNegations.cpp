/*
    Problem: Maximize Sum of Array After K Negations

    We are given an integer array nums and exactly k operations.

    In one operation, we can choose any element and flip its sign:

        x -> -x

    The same index can be chosen multiple times.

    Goal:
    Maximize the final sum of the array after exactly k operations.


    --------------------------------------------------
    GREEDY IDEA
    --------------------------------------------------

    1. Flip negative numbers first.

       Turning a negative number into positive increases the sum.

       Example:
           -8 -> 8   improves sum by 16
           -3 -> 3   improves sum by 6

       Therefore, we should flip the MOST NEGATIVE numbers first.

       Sorting in ascending order gives:

           [-8, -3, 2, 5]
             ^
          start here


    2. After all useful negative flips, k may still remain.

       This is where the odd/even trick matters.

       Flipping the SAME number twice cancels:

           3 -> -3 -> 3

       Therefore:

           remaining k EVEN
           -> all flips can cancel in pairs
           -> final array does not need to change

           remaining k ODD
           -> pairs cancel, but ONE flip remains
           -> we must flip one number


    3. If one unavoidable flip remains, flip the SMALLEST value.

       Example:

           [2, 5, 8]

       If we must flip one:

           2 -> -2   loss = 4
           5 -> -5   loss = 10
           8 -> -8   loss = 16

       So flipping 2 causes the smallest damage.

       We sort again after processing negatives, so nums[0]
       becomes the smallest remaining value.


    Example:

        nums = [-8, -3, 2, 5]
        k = 5

        Flip -8:
            [8, -3, 2, 5]
            k = 4

        Flip -3:
            [8, 3, 2, 5]
            k = 3

        Sort again:
            [2, 3, 5, 8]

        k = 3 is odd.

        Two of those operations can cancel:

            2 -> -2 -> 2

        One meaningful flip is still left:

            2 -> -2

        Final:
            [-2, 3, 5, 8]


    KEY MEMORY RULE:

        Flip negatives from MOST negative to least negative.

        Remaining k EVEN:
            Do nothing because flips cancel in pairs.

        Remaining k ODD:
            Flip the smallest value once.


    Time Complexity:
        O(n log n)
        because we sort the array.

    Space Complexity:
        O(1) auxiliary space
        ignoring the internal space used by sort.
*/

class Solution {
public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {

        // Sort so the most negative numbers come first.
        sort(nums.begin(), nums.end());

        // Flip negative numbers from most negative to least negative.
        // Each such flip increases the sum as much as possible.
        for (int i = 0; i < nums.size() && k > 0; i++) {

            if (nums[i] < 0) {
                nums[i] = -nums[i];
                k--;
            }
        }

        /*
            Flipping negatives may disturb the sorted order.

            Example:
                Before: [-8, -3, 2, 5]
                After:  [8, 3, 2, 5]

            Sort again so nums[0] is the smallest value.
        */
        sort(nums.begin(), nums.end());

        /*
            If k is even:
                remaining operations can cancel in pairs.

                x -> -x -> x

            If k is odd:
                after cancelling pairs, exactly ONE meaningful
                flip remains.

            Flip the smallest number because this causes
            the minimum possible loss in the final sum.
        */
        if (k % 2 != 0) {
            nums[0] = -nums[0];
        }

        // Calculate the final maximum sum.
        int sum = 0;

        for (int num : nums) {
            sum += num;
        }

        return sum;
    }
};