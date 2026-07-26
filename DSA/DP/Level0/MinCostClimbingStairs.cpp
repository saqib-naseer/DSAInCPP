#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Forward declaration or keeping functions above main
int myFuncBottomUpSpaceOptimized(vector<int>& cost){
      int prev1 = 0;
      int prev2 = 0;
      int ans = 0;

  for(int stair = 2 ; stair<=cost.size(); stair++){
      int oneStep = cost[stair-1] + prev1;
      int twoStep = cost[stair-2] + prev2;
      ans = min(oneStep,twoStep);
      prev2 = prev1;
      prev1 = ans;
  }
  return ans;
}

int myFuncBottomUp(int step, vector<int>& cost){
   vector<int> dp(step+1,-1);
      dp[0] = 0;
      dp[1] = 0;
  for(int stair = 2 ; stair<=cost.size(); stair++){
      int prev1 = cost[stair-1] + dp[stair-1];
      int prev2 = cost[stair-2] + dp[stair-2];
      dp[stair] = min(prev1,prev2);
  }
  return dp[step];
}

int myFunc(int step, vector<int>& cost, vector<int>& dp){
  if(step == 0 || step == 1) return 0;

  if(dp[step]!=-1) return dp[step];

  int step1cost = cost[step-1] + myFunc(step-1,cost,dp);
  int step2cost = cost[step-2] + myFunc(step-2,cost,dp);

  return dp[step] = min(step1cost,step2cost);
}

int minCostClimbingStairs(vector<int>& cost) {
  return myFuncBottomUpSpaceOptimized(cost);
}

int main() {
  vector<int> cost1 = {10, 15, 20};
  vector<int> cost2 = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};

  cout << "Example 1 Result: " << minCostClimbingStairs(cost1) << endl;
  cout << "Example 2 Result: " << minCostClimbingStairs(cost2) << endl;

  return 0;
}

/*
 * PROBLEM DESCRIPTION:
 * You are given an integer array cost where cost[i] is the cost of ith step on a staircase. 
 * Once you pay the cost, you can either climb one or two steps.
 * You can either start from the step with index 0, or the step with index 1.
 * Return the minimum cost to reach the top of the floor.
 * * Example 1:
 * Input: cost = [10,15,20]
 * Output: 15
 * Explanation: You will start at index 1. Pay 15 and climb two steps to reach the top.
 * * Example 2:
 * Input: cost = [1,100,1,1,1,100,1,1,100,1]
 * Output: 6
 * Explanation: Start at index 0. Follow steps with cost 1 to reach the top.
 * * Constraints:
 * - 2 <= cost.length <= 1000
 * - 0 <= cost[i] <= 999
 */