#include <iostream>

 vector<int> kthLargest(vector<int>& arr, int k) {
        // code here
        vector<int> ans;
        priority_queue<int,vector<int>,greater<int>> p;
        
        for(int i=0;i<arr.size();i++){
            
            p.push(arr[i]);
            
            if(p.size()>k)
            { 
                p.pop();
            }
                
            if(p.size()<k) ans.push_back(-1);
            else ans.push_back(p.top());
        }
        
        return ans;
    }
  
int main() {

}
