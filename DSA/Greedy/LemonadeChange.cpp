/*
    Problem: Lemonade Change LC 860

    Each lemonade costs $5.
    Customers pay one by one using a $5, $10, or $20 bill.

    We start with no money and must give the correct change immediately.
    If at any point we cannot give the required change, return false.

    Approach:
    We do NOT need to track total cash/profit.
    We only need to track the physical bills that are useful for making change:

        five = number of $5 bills we currently have
        ten  = number of $10 bills we currently have

    We do not track $20 bills because they cannot help us make the required
    $5 or $15 change for future customers.

    Cases:

    1. Customer pays $5:
       - No change is required.
       - Keep the $5 bill.
       - five++

    2. Customer pays $10:
       - Need to return $5.
       - We must have one $5 bill.
       - Give one $5 and keep the customer's $10.
       - five--
       - ten++

    3. Customer pays $20:
       - Need to return $15.
       - Prefer $10 + $5 if possible.
       - Otherwise use $5 + $5 + $5.
       - If neither is possible, return false.

    Greedy Idea:
    When giving $15 change, prefer $10 + $5 instead of three $5 bills.

    This uses only one $5 bill and preserves the remaining $5 bills.
    $5 bills are especially useful because a customer paying $10 can only
    receive change using a $5 bill.

    Important:
    When a customer pays $20, we DO receive and keep their $20 bill.
    We simply do not track it because it is useless for making future change.
    Our goal is not to calculate profit; our goal is only to determine
    whether we can give change to every customer.

    Time Complexity: O(n)
    Space Complexity: O(1)
*/

class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {

        // Count of physical $5 and $10 bills currently available.
        int five = 0;
        int ten = 0;

        // Customers must be processed in the given order.
        for (int bill : bills) {

            if (bill == 5) {

                // Customer pays exactly $5, so no change is needed.
                // We keep their $5 bill for future change.
                five++;
            }

            else if (bill == 10) {

                // Customer needs $5 change.
                if (five == 0)
                    return false;

                // Return one $5 bill.
                five--;

                // Keep the customer's $10 bill.
                ten++;
            }

            else { // bill == 20

                // Customer needs $15 change.

                // Greedy choice:
                // Prefer $10 + $5 to preserve more $5 bills.
                if (ten > 0 && five > 0) {
                    ten--;   // Return one $10 bill.
                    five--;  // Return one $5 bill.
                }

                // If no $10 is available, try three $5 bills.
                else if (five >= 3) {
                    five -= 3;
                }

                // Cannot make $15 change.
                else {
                    return false;
                }

                /*
                    We received the customer's $20 bill, but we do not
                    track it because a $20 bill cannot help us make
                    $5 or $15 change for future customers.
                */
            }
        }

        return true;
    }
};