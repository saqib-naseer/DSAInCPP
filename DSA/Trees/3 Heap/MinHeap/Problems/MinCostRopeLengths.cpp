/*
Put all ropes into MIN HEAP

while more than 1 rope remains:

    take smallest       → pop()
    take next smallest  → pop()

    join them
        ↓
    currentCost = length1 + length2

    add currentCost to total

    put joined rope BACK into heap
*/


class Solution {
  public:
    int minCost(vector<int>& arr) {
        // code here
        priority_queue<int,vector<int>,greater<int>> p;
        
        for(int i=0;i<arr.size();i++){
            p.push(arr[i]);
        }
        
        int cost = 0;
        
        while(p.size()>1){
            
            int length1 = p.top();
            p.pop();
            int length2=p.top();
            p.pop();
            int currentCost =length1+length2;
            p.push(currentCost);
            cost+=currentCost;
        }
        
        return cost;
    }
};