
/*
Maximum Profit from Stadium Tickets — Max Heap

Observation:
Ticket price = number of currently vacant seats in that row.

To maximize profit, for every customer:
→ sell from the row having the MOST vacant seats.

Therefore:
→ MAX HEAP


Algorithm:

1. Put vacant seats of all rows into a max heap.

2. Repeat B times:

   - Take row with maximum vacant seats.
   - That value is the ticket price.
   - Add it to total profit.
   - Decrease vacant seats by 1.
   - If seats remain, push the row back.

3. Return total profit.


Example:

A = [2, 3], B = 3

heap: [3, 2]

take 3 → profit = 3
push 2

heap: [2, 2]

take 2 → profit = 5
push 1

heap: [2, 1]

take 2 → profit = 7
push 1

Answer = 7


Time:  O((N + B) log N)
Space: O(N)


*/


int Solution::solve(vector<int> &A, int B) {

    // Max heap keeps the row with the most vacant seats on top
    priority_queue<int> maxHeap;

    // Add the vacant seat count of every row
    for(int seats : A) {
        maxHeap.push(seats);
    }

    int totalProfit = 0;

    // Sell one ticket to each of the B people
    while(B > 0) {

        // Sell from the row with the most vacant seats
        int vacantSeats = maxHeap.top();
        maxHeap.pop();

        // Ticket price = current number of vacant seats in that row
        totalProfit += vacantSeats;

        // One seat has now been sold from this row
        int remainingSeats = vacantSeats - 1;

        // Put the row back if it still has vacant seats
        if(remainingSeats > 0) {
            maxHeap.push(remainingSeats);
        }

        B--;
    }

    return totalProfit;
}