#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    vector<int> minToMaxHeap(vector<int> nums) {
        if(nums.size()==1) return nums;
        int lastNonLeaf = (nums.size()/2)-1;

        for(int i = lastNonLeaf;i>=0;i--){
            HeapifyDown(i,nums);

        }

        return nums;


    }

  void HeapifyDown(int index, vector<int>& arr){

	if(arr.size()>0){
		
		while(index<arr.size()){
		
		int left = 2*index +1;
		int right = 2*index +2;
		int largest = index;
		
		if(left<arr.size() && arr[left]>arr[largest])
		largest = left;
		
		if(right<arr.size() && arr[right]>arr[largest])
		largest = right;
		
		 if (largest == index)
                break;
				
		swap(arr[largest],arr[index]);
		index = largest;
		
		}
	}

}

};



int main() {

    // Create an object of Solution
    Solution solution;

    // Our min heap
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7};

    // Convert it
    vector<int> answer = solution.minToMaxHeap(nums);

    // Print answer
    for(int num : answer) {
        cout << num << " ";
    }

    return 0;
}


