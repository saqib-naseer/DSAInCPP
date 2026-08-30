#include <iostream>
#include <vector>
using namespace std;

class minHeap {
  public:
    // Initialize your data members
    vector<int> arr;
  public:
    void heapifyUp(int index){
        if (index == 0)
        return;
        
        int smallest = index;
        int parent = (index-1)/2;
        
        if(arr[parent]>arr[index])
        smallest = parent;
        
        if(smallest!=index){
            swap(arr[parent],arr[index]);
            heapifyUp(parent);
        }
    }
    
     void heapifyDown(int index){
        
        int smallest = index;
        
        int left = (index*2)+1;
        int right = (index*2)+2;
         
        if(left < arr.size() && arr[left]<arr[index])
        smallest = left;
        
         if(right < arr.size() && arr[right]<arr[smallest])
        smallest = right;
        
        if(smallest!=index){
            swap(arr[smallest],arr[index]);
            heapifyDown(smallest);
        }
    }
    
    void insert(int x) {
        // Insert x into the heap
        if(arr.empty()){
            arr.push_back(x);
            return;
        }
        
        arr.push_back(x);
        int index = arr.size()-1;
        heapifyUp(index);
    }

    void pop() {
        // Remove the top (minimum) element
        if (arr.empty())
        return;
        
        if(arr.size()==1) 
        {arr.pop_back(); return;}
        
        int index = arr.size()-1;
        swap(arr[0],arr[index]);
        arr.pop_back();
        heapifyDown(0);
        
        
    }

    int peek() {
        // Return the top element or -1 if empty
        if(arr.empty()) return -1;
        
        return arr[0];
    }

    int size() {
        // Return the number of elements in the heap
        return arr.size();
    }

void preorder(int index){
	if(index>=arr.size()) return;
  
	cout<<arr[index]<<" ";
	preorder(2*index+1);
	preorder(2*index+2);

}
};


int main() {
  minHeap heap;
  heap.insert(10);
  heap.insert(20);
  heap.insert(30);
  heap.insert(40);
  heap.insert(50);
  heap.insert(60);
  heap.insert(160);
  
  // array
  cout<<"\nArray Shape Currently: \n";
  for(int i=0;i<heap.arr.size();i++)
    cout<<heap.arr[i]<<" ";
  
  heap.size();
  heap.peek();

  cout<<"\nPreorder Traversal: \n";
  // Preorder
  heap.preorder(0);
  
  heap.pop();

	
	 // array
  cout<<"\nAfter Deletion: \n";
  
  cout<<"\nArray Shape Currently: \n";
  for(int i=0;i<heap.arr.size();i++)
    cout<<heap.arr[i]<<" ";
  
  heap.size();
  heap.peek();

  cout<<"\nPreorder Traversal: \n";
  // Preorder
  heap.preorder(0);

  
}
