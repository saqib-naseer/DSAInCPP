#include <iostream>
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono;

int TopDownDP(int n, vector<int> &dp){
  if (n == 0 || n == 1) return n;  

  if(dp[n]!=-1) return dp[n];

  return dp[n]=TopDownDP(n - 1,dp) + TopDownDP(n - 2,dp);  
}

int BottomUpDP(int n){
  if (n == 0) return 0; // Fixed: Fib(0) is 0
  if (n == 1) return 1; // Fixed: Fib(1) is 1

  int prev1=0; // Fixed: start with 0
  int prev2=1; // Fixed: start with 1
  int ans=0;

  for(int i=2;i<=n;i++){ // Fixed: Loop from 2 to n
    ans=prev1+prev2;
    prev1=prev2;
    prev2=ans;
  }  

  return ans;
}

int BottomUpDP2(int n){
  if (n <= 1) return n; // Fixed: return n
  vector<int> dp(n+1,0);

  dp[0]=0;
  dp[1]=1;

  for(int i=2;i<=n;i++){
    dp[i]=dp[i-1]+dp[i-2];
  }  

  return dp[n];
}

int fib(int n) {
    // Calling your working function
    return BottomUpDP(n);
}

int main() {
  auto start_time = high_resolution_clock::now();

  // Test with n=5. Fib sequence: 0, 1, 1, 2, 3, 5... so 5 is correct.
  cout << "Fibonacci of 5: " << fib(5) << endl;

  auto end_time = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(end_time - start_time);
  cout << endl << "Execution Time: " << duration.count() << " microseconds" << endl;

  return 0;
}