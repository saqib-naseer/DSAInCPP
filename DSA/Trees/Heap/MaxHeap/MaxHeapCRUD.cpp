#include <iostream>
#include <vector>
using namespace std;

class Heap {
	
	public:
		vector<int> arr;
		
	public:
		Heap()=default;
		
		// Heapify Down
		void heapifyDown(int index);
		
		// HeapifyDown
		void heapifyUp(int index);
		
		//Insert
		void insert(int val);
		
		// Delete
		void delet();
		
		// Peak
		void peek();
		
		// PreOrder
		void preorder(int index);
		
		// Total Size
		void size();
};

void Heap::heapifyUp(int index){
		
		// Iterative Approach
		
	while (index > 0)
    {
        int parent = (index - 1) / 2;

        if (arr[parent] >= arr[index])
            break;

        swap(arr[parent], arr[index]);

        index = parent;
    }


		/* Recursive
		int largest = index;
		
		int parent = (index-1)/2;
		if(parent>=0 && arr[parent]<arr[index])
		largest = parent;
		
		if(largest!=index){
			swap(arr[index],arr[parent]);
			heapifyUp(largest);
		}
		*/
}

void Heap::heapifyDown(int index){

	if(arr.size()>0){
		int index =0;
		
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

void Heap::peek(){
	if(arr.size()>=0) cout<<"\nRoot is "<<arr[0]<<endl; return;
	cout<<"\nNo elements in heap "<<endl;
}

void Heap::size(){
	cout<<"\nHeap Size: "<<arr.size()<<" elements";
}

void Heap::preorder(int index){
	if(index>=arr.size()) return;
  
	cout<<arr[index]<<" ";
	preorder(2*index+1);
	preorder(2*index+2);

}

void Heap::insert(int val){
	arr.push_back(val);
	
	int lastIndex = arr.size()-1;
	heapifyUp(lastIndex);
	
}

void Heap::delet(){
		cout<<"\nDeleting Root: "<<arr[0]<<endl;
		if(arr.size()>0){
		
		int lastIndex = arr.size()-1;
		
		swap(arr[lastIndex],arr[0]);
		
		arr.pop_back();
		
		heapifyDown(0);
		
		return;
		}
		
}

int main() {
  Heap heap;
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
  
  heap.delet();

	
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
