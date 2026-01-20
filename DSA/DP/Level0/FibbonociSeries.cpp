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

int fib(int n) {
  vector<int> dp(n + 1, -1);
  return TopDownDP(n, dp);
}


int main() {
  auto start_time = high_resolution_clock::now();

  cout<<fib(10)<<endl;

  auto end_time = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(end_time - start_time);
  cout << endl << "Execution Time: " << duration.count() << " microseconds" << endl;
  
  return 0;
}

