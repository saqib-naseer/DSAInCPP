int Solution::nchoc(int A, vector<int> &B) {

    // Max heap: always gives us the bag with the most chocolates
    priority_queue<long long> maxHeap;

    // Put all chocolate bags into the max heap
    for(int i = 0; i < B.size(); i++) {
        maxHeap.push(B[i]);
    }

    long long totalChocolatesEaten = 0;

    // Kid can eat chocolates A times
    while(!maxHeap.empty() && A > 0) {

        // Always choose the bag with maximum chocolates
        long long maxChocolates = maxHeap.top();
        maxHeap.pop();

        // Kid eats all chocolates from this bag
        totalChocolatesEaten += maxChocolates;

        // Magician refills the bag with half the chocolates
        long long remainingChocolates = maxChocolates / 2;

        // Put the refilled bag back into the heap
        if(remainingChocolates > 0) {
            maxHeap.push(remainingChocolates);
        }

        A--;
    }

    return totalChocolatesEaten % 1000000007;
}