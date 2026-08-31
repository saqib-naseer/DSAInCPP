#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    vector<int> maxToMinHeap(vector<int> nums) {
        if(nums.size()==1) return nums;
        int lastNonLeaf = (nums.size()/2)-1;

        for(int i = lastNonLeaf;i>=0;i--){
            HeapifyDown(i,nums);

        }

        return nums;


    }

void HeapifyDown(int index,vector<int>& arr){


	while(index<arr.size()){
		int smallest = index;		//reset for this level
			
		int left = index*2+1;
		int right = index*2+2;
		
		if(left< arr.size() && arr[left]<arr[index]){
			smallest = left;
		} 
		
		if(right< arr.size() && arr[right]<arr[smallest]){
			smallest = right;
		}
		
		if(smallest==index) break;
		
		swap(arr[smallest],arr[index]);
		
		index = smallest;
	}

}

};



int main() {

    // Create an object of Solution
    Solution solution;

    // Our max heap
    vector<int> nums = {7, 5, 6, 4, 2, 1, 3 };

    // Convert it
    vector<int> answer = solution.maxToMinHeap(nums);

    // Print answer
    for(int num : answer) {
        cout << num << " ";
    }

    return 0;
}


