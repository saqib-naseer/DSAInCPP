/*
    Problem: Shortest Job First (SJF)

    We are given the burst time of each process.

    Burst Time:
    How long a process takes to execute.

    All processes are available at time 0.

    We need to schedule the processes using Shortest Job First (SJF)
    and return the average waiting time.


    --------------------------------------------------
    GREEDY IDEA
    --------------------------------------------------

    Always execute the shortest available job first.

    Why?

    A job executed now makes every job behind it wait.

    Therefore, putting a short job first adds a smaller waiting time
    to the remaining jobs than putting a long job first.

    Example:

        Jobs: [10, 2]

        Order: 10, 2
        Waiting times:
            10 waits 0
            2  waits 10

        Total waiting = 10


        Order: 2, 10
        Waiting times:
            2  waits 0
            10 waits 2

        Total waiting = 2

    Therefore, shortest job first minimizes total waiting time.


    --------------------------------------------------
    IMPORTANT: BURST TIME VS WAITING TIME
    --------------------------------------------------

    Burst time = how long THIS job takes to execute.

    Waiting time = how long THIS job waits before it starts.

    Example after sorting:

        [1, 2, 3, 4]

    Waiting times:

        Job 1 waits = 0
        Job 2 waits = 1
        Job 3 waits = 1 + 2 = 3
        Job 4 waits = 1 + 2 + 3 = 6

    Waiting times are:

        [0, 1, 3, 6]

    We need the average of WAITING TIMES,
    not the average of burst times.


    --------------------------------------------------
    ROLE OF currentTime
    --------------------------------------------------

    currentTime stores the total execution time of all jobs
    that have already finished.

    Therefore, it is exactly how long the current job has waited.

    Example:

        Sorted jobs = [1, 2, 3]

        Before job 1:
            currentTime = 0
            job 1 waited 0

        After job 1:
            currentTime = 1

        Before job 2:
            currentTime = 1
            job 2 waited 1

        After job 2:
            currentTime = 3

        Before job 3:
            currentTime = 3
            job 3 waited 3


    Time Complexity: O(n log n)
    Space Complexity: O(1)
*/

class Solution {
public:
    int solve(vector<int>& bt) {

        // Shortest job should execute first.
        sort(bt.begin(), bt.end());

        // Sum of waiting times of all processes.
        long long totalWaitingTime = 0;

        // Total time consumed by previously completed jobs.
        long long currentTime = 0;

        for (int burstTime : bt) {

            /*
                The current process has waited for all previous
                processes to finish.

                Therefore its waiting time is currentTime.
            */
            totalWaitingTime += currentTime;

            /*
                Now execute the current process.

                Future processes will also have to wait for
                this process, so add its burst time.
            */
            currentTime += burstTime;
        }

        // Return floor of average waiting time.
        return totalWaitingTime / bt.size();
    }
};