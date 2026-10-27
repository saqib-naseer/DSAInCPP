
 struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
class Solution {
public:
  // Approach 5: Merge two with each other and then result with next
 ListNode* mergeKLists(vector<ListNode*>& lists) {

        if (lists.empty()) return NULL;

        // Start with the first sorted list as our current merged result.
        ListNode* mergedHead = lists[0];

        // Merge each remaining list one-by-one into the growing result.
        //
        // Example:
        // L1 + L2       -> L12
        // L12 + L3      -> L123
        // L123 + L4     -> L1234
        for (int i = 1; i < lists.size(); i++) {
            mergedHead = mergeTwoLists(mergedHead, lists[i]);
        }

        return mergedHead;
    }


    // Merge two already sorted linked lists.
    ListNode* mergeTwoLists(ListNode* h1, ListNode* h2) {

        // Dummy node avoids special handling for the first node.
        ListNode* dummy = new ListNode(0);
        ListNode* tail = dummy;

        // Compare the current nodes of both lists and
        // attach the smaller one to the merged result.
        while (h1 && h2) {

            if (h1->val <= h2->val) {
                tail->next = h1;
                h1 = h1->next;
            }
            else {
                tail->next = h2;
                h2 = h2->next;
            }

            // Move tail to the newly attached node.
            tail = tail->next;
        }

        // One list may still contain nodes.
        // Since it is already sorted, attach the whole remainder.
        if (h1) {
            tail->next = h1;
        }
        else {
            tail->next = h2;
        }

        return dummy->next;
    }

    // Approach 4: Using Merge Sort
    ListNode* mergeKLists(vector<ListNode*>& lists) {

        if (lists.empty()) return NULL;

        // Divide the K lists into halves and merge them recursively.
        mergeLists(lists, 0, lists.size() - 1);

        // After all recursive merges, lists[0] contains the final merged list.
        return lists[0];
    }


    void mergeLists(vector<ListNode*>& lists, int start, int end) {

        // One list remains in this range — already sorted.
        if (start >= end) return;

        int mid = start + (end - start) / 2;

        // Recursively merge all lists in the left half.
        mergeLists(lists, start, mid);

        // Recursively merge all lists in the right half.
        mergeLists(lists, mid + 1, end);

        // At this point:
        // lists[start] → merged result of the LEFT half
        // lists[mid+1] → merged result of the RIGHT half
        // Merge these two sorted lists and store the result at lists[start].
        lists[start] = mergeTwoLists(lists[start], lists[mid + 1]);
    }


    ListNode* mergeTwoLists(ListNode* h1, ListNode* h2) {

        // Dummy node makes building the merged list easier.
        ListNode* dummy = new ListNode(0);
        ListNode* tail = dummy;

        // Pick the smaller current node from the two sorted lists.
        while (h1 && h2) {

            if (h1->val <= h2->val) {
                tail->next = h1;
                h1 = h1->next;
            }
            else {
                tail->next = h2;
                h2 = h2->next;
            }

            // Move the tail of the merged list forward.
            tail = tail->next;
        }

        // One list may still have nodes left.
        // Since it is already sorted, attach the whole remaining part.
        if (h1) {
            tail->next = h1;
        }
        else {
            tail->next = h2;
        }

        return dummy->next;
    }


// Approach 3:
 ListNode* mergeKLists(vector<ListNode*>& lists) {
      if(lists.empty()) return NULL;
       priority_queue<ListNode*,vector<ListNode*>,Compare> p;

        for(ListNode* i : lists){
            if(i){

        p.push(i);
            }
        }

        ListNode* dummy = new ListNode(0);
        ListNode* root = dummy;

        while(!p.empty()){
            ListNode* temp = p.top();
            p.pop();
            root->next = temp;
            root = root->next;

            if(temp->next) {
                p.push(temp->next);
                }

        }

        return dummy->next;
    }

// Approach 2: Put all elements in min heap and pop out
 ListNode* mergeKLists(vector<ListNode*>& lists) {
     
        vector<int> llarr;
        priority_queue<int,vector<int>,greater<int>> p;

        for(ListNode* i:lists){
            ListNode* temp = i;

            while(temp){
                p.push(temp->val);
                temp=temp->next;
            }
        }

        ListNode* root = new ListNode(0);
        ListNode* temp = root;
        while(!p.empty()){
            temp->next = new ListNode(p.top());
            temp = temp->next;
            p.pop();
        }

        return root->next;

    }
  // Approach 1 : Just put all in an array, sort that array and build new linked list
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // code here
        vector<int> llarr;
        
        for(int i=0;i<lists.size();i++){
            ListNode* temp = lists[i];
            
            while(temp){
            llarr.push_back(temp->val);
            temp = temp->next;
            }
        }
        
        sort(llarr.begin(),llarr.end());
        
        ListNode* root = new ListNode(0);
        ListNode* temp=root;
        for(int i:llarr){
            ListNode* newNode = new ListNode(i);
            temp->next = newNode;
            temp = temp->next;
        }
        
        return root->next; 
    }
};
 struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
class Solution {
public:

// Approach 3:
 ListNode* mergeKLists(vector<ListNode*>& lists) {
      if(lists.empty()) return NULL;
       priority_queue<ListNode*,vector<ListNode*>,Compare> p;

        for(ListNode* i : lists){
            if(i){

        p.push(i);
            }
        }

        ListNode* dummy = new ListNode(0);
        ListNode* root = dummy;

        while(!p.empty()){
            ListNode* temp = p.top();
            p.pop();
            root->next = temp;
            root = root->next;

            if(temp->next) {
                p.push(temp->next);
                }

        }

        return dummy->next;
    }

// Approach 2: Put all elements in min heap and pop out
 ListNode* mergeKLists(vector<ListNode*>& lists) {
     
        vector<int> llarr;
        priority_queue<int,vector<int>,greater<int>> p;

        for(ListNode* i:lists){
            ListNode* temp = i;

            while(temp){
                p.push(temp->val);
                temp=temp->next;
            }
        }

        ListNode* root = new ListNode(0);
        ListNode* temp = root;
        while(!p.empty()){
            temp->next = new ListNode(p.top());
            temp = temp->next;
            p.pop();
        }

        return root->next;

    }
  // Approach 1 : Just put all in an array, sort that array and build new linked list
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // code here
        vector<int> llarr;
        
        for(int i=0;i<lists.size();i++){
            ListNode* temp = lists[i];
            
            while(temp){
            llarr.push_back(temp->val);
            temp = temp->next;
            }
        }
        
        sort(llarr.begin(),llarr.end());
        
        ListNode* root = new ListNode(0);
        ListNode* temp=root;
        for(int i:llarr){
            ListNode* newNode = new ListNode(i);
            temp->next = newNode;
            temp = temp->next;
        }
        
        return root->next; 
    }
};
 struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
class Solution {
public:

// Approach 3:
 ListNode* mergeKLists(vector<ListNode*>& lists) {
      if(lists.empty()) return NULL;
       priority_queue<ListNode*,vector<ListNode*>,Compare> p;

        for(ListNode* i : lists){
            if(i){

        p.push(i);
            }
        }

        ListNode* dummy = new ListNode(0);
        ListNode* root = dummy;

        while(!p.empty()){
            ListNode* temp = p.top();
            p.pop();
            root->next = temp;
            root = root->next;

            if(temp->next) {
                p.push(temp->next);
                }

        }

        return dummy->next;
    }

// Approach 2: Put all elements in min heap and pop out
 ListNode* mergeKLists(vector<ListNode*>& lists) {
     
        vector<int> llarr;
        priority_queue<int,vector<int>,greater<int>> p;

        for(ListNode* i:lists){
            ListNode* temp = i;

            while(temp){
                p.push(temp->val);
                temp=temp->next;
            }
        }

        ListNode* root = new ListNode(0);
        ListNode* temp = root;
        while(!p.empty()){
            temp->next = new ListNode(p.top());
            temp = temp->next;
            p.pop();
        }

        return root->next;

    }
  // Approach 1 : Just put all in an array, sort that array and build new linked list
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // code here
        vector<int> llarr;
        
        for(int i=0;i<lists.size();i++){
            ListNode* temp = lists[i];
            
            while(temp){
            llarr.push_back(temp->val);
            temp = temp->next;
            }
        }
        
        sort(llarr.begin(),llarr.end());
        
        ListNode* root = new ListNode(0);
        ListNode* temp=root;
        for(int i:llarr){
            ListNode* newNode = new ListNode(i);
            temp->next = newNode;
            temp = temp->next;
        }
        
        return root->next; 
    }
};
 struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
class Solution {
public:

// Approach 3:
 ListNode* mergeKLists(vector<ListNode*>& lists) {
      if(lists.empty()) return NULL;
       priority_queue<ListNode*,vector<ListNode*>,Compare> p;

        for(ListNode* i : lists){
            if(i){

        p.push(i);
            }
        }

        ListNode* dummy = new ListNode(0);
        ListNode* root = dummy;

        while(!p.empty()){
            ListNode* temp = p.top();
            p.pop();
            root->next = temp;
            root = root->next;

            if(temp->next) {
                p.push(temp->next);
                }

        }

        return dummy->next;
    }

// Approach 2: Put all elements in min heap and pop out
 ListNode* mergeKLists(vector<ListNode*>& lists) {
     
        vector<int> llarr;
        priority_queue<int,vector<int>,greater<int>> p;

        for(ListNode* i:lists){
            ListNode* temp = i;

            while(temp){
                p.push(temp->val);
                temp=temp->next;
            }
        }

        ListNode* root = new ListNode(0);
        ListNode* temp = root;
        while(!p.empty()){
            temp->next = new ListNode(p.top());
            temp = temp->next;
            p.pop();
        }

        return root->next;

    }
  // Approach 1 : Just put all in an array, sort that array and build new linked list
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // code here
        vector<int> llarr;
        
        for(int i=0;i<lists.size();i++){
            ListNode* temp = lists[i];
            
            while(temp){
            llarr.push_back(temp->val);
            temp = temp->next;
            }
        }
        
        sort(llarr.begin(),llarr.end());
        
        ListNode* root = new ListNode(0);
        ListNode* temp=root;
        for(int i:llarr){
            ListNode* newNode = new ListNode(i);
            temp->next = newNode;
            temp = temp->next;
        }
        
        return root->next; 
    }
};
 struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
class Solution {
public:

// Approach 3:
 ListNode* mergeKLists(vector<ListNode*>& lists) {
      if(lists.empty()) return NULL;
       priority_queue<ListNode*,vector<ListNode*>,Compare> p;

        for(ListNode* i : lists){
            if(i){

        p.push(i);
            }
        }

        ListNode* dummy = new ListNode(0);
        ListNode* root = dummy;

        while(!p.empty()){
            ListNode* temp = p.top();
            p.pop();
            root->next = temp;
            root = root->next;

            if(temp->next) {
                p.push(temp->next);
                }

        }

        return dummy->next;
    }

// Approach 2: Put all elements in min heap and pop out
 ListNode* mergeKLists(vector<ListNode*>& lists) {
     
        vector<int> llarr;
        priority_queue<int,vector<int>,greater<int>> p;

        for(ListNode* i:lists){
            ListNode* temp = i;

            while(temp){
                p.push(temp->val);
                temp=temp->next;
            }
        }

        ListNode* root = new ListNode(0);
        ListNode* temp = root;
        while(!p.empty()){
            temp->next = new ListNode(p.top());
            temp = temp->next;
            p.pop();
        }

        return root->next;

    }
  // Approach 1 : Just put all in an array, sort that array and build new linked list
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // code here
        vector<int> llarr;
        
        for(int i=0;i<lists.size();i++){
            ListNode* temp = lists[i];
            
            while(temp){
            llarr.push_back(temp->val);
            temp = temp->next;
            }
        }
        
        sort(llarr.begin(),llarr.end());
        
        ListNode* root = new ListNode(0);
        ListNode* temp=root;
        for(int i:llarr){
            ListNode* newNode = new ListNode(i);
            temp->next = newNode;
            temp = temp->next;
        }
        
        return root->next; 
    }
};
 struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
class Solution {
public:

// Approach 3:
 ListNode* mergeKLists(vector<ListNode*>& lists) {
      if(lists.empty()) return NULL;
       priority_queue<ListNode*,vector<ListNode*>,Compare> p;

        for(ListNode* i : lists){
            if(i){

        p.push(i);
            }
        }

        ListNode* dummy = new ListNode(0);
        ListNode* root = dummy;

        while(!p.empty()){
            ListNode* temp = p.top();
            p.pop();
            root->next = temp;
            root = root->next;

            if(temp->next) {
                p.push(temp->next);
                }

        }

        return dummy->next;
    }

// Approach 2: Put all elements in min heap and pop out
 ListNode* mergeKLists(vector<ListNode*>& lists) {
     
        vector<int> llarr;
        priority_queue<int,vector<int>,greater<int>> p;

        for(ListNode* i:lists){
            ListNode* temp = i;

            while(temp){
                p.push(temp->val);
                temp=temp->next;
            }
        }

        ListNode* root = new ListNode(0);
        ListNode* temp = root;
        while(!p.empty()){
            temp->next = new ListNode(p.top());
            temp = temp->next;
            p.pop();
        }

        return root->next;

    }
  // Approach 1 : Just put all in an array, sort that array and build new linked list
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // code here
        vector<int> llarr;
        
        for(int i=0;i<lists.size();i++){
            ListNode* temp = lists[i];
            
            while(temp){
            llarr.push_back(temp->val);
            temp = temp->next;
            }
        }
        
        sort(llarr.begin(),llarr.end());
        
        ListNode* root = new ListNode(0);
        ListNode* temp=root;
        for(int i:llarr){
            ListNode* newNode = new ListNode(i);
            temp->next = newNode;
            temp = temp->next;
        }
        
        return root->next; 
    }
};
 struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
class Solution {
public:

// Approach 3:
 ListNode* mergeKLists(vector<ListNode*>& lists) {
      if(lists.empty()) return NULL;
       priority_queue<ListNode*,vector<ListNode*>,Compare> p;

        for(ListNode* i : lists){
            if(i){

        p.push(i);
            }
        }

        ListNode* dummy = new ListNode(0);
        ListNode* root = dummy;

        while(!p.empty()){
            ListNode* temp = p.top();
            p.pop();
            root->next = temp;
            root = root->next;

            if(temp->next) {
                p.push(temp->next);
                }

        }

        return dummy->next;
    }

// Approach 2: Put all elements in min heap and pop out
 ListNode* mergeKLists(vector<ListNode*>& lists) {
     
        vector<int> llarr;
        priority_queue<int,vector<int>,greater<int>> p;

        for(ListNode* i:lists){
            ListNode* temp = i;

            while(temp){
                p.push(temp->val);
                temp=temp->next;
            }
        }

        ListNode* root = new ListNode(0);
        ListNode* temp = root;
        while(!p.empty()){
            temp->next = new ListNode(p.top());
            temp = temp->next;
            p.pop();
        }

        return root->next;

    }
  // Approach 1 : Just put all in an array, sort that array and build new linked list
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // code here
        vector<int> llarr;
        
        for(int i=0;i<lists.size();i++){
            ListNode* temp = lists[i];
            
            while(temp){
            llarr.push_back(temp->val);
            temp = temp->next;
            }
        }
        
        sort(llarr.begin(),llarr.end());
        
        ListNode* root = new ListNode(0);
        ListNode* temp=root;
        for(int i:llarr){
            ListNode* newNode = new ListNode(i);
            temp->next = newNode;
            temp = temp->next;
        }
        
        return root->next; 
    }
};
 struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
class Solution {
public:

// Approach 3:
 ListNode* mergeKLists(vector<ListNode*>& lists) {
      if(lists.empty()) return NULL;
       priority_queue<ListNode*,vector<ListNode*>,Compare> p;

        for(ListNode* i : lists){
            if(i){

        p.push(i);
            }
        }

        ListNode* dummy = new ListNode(0);
        ListNode* root = dummy;

        while(!p.empty()){
            ListNode* temp = p.top();
            p.pop();
            root->next = temp;
            root = root->next;

            if(temp->next) {
                p.push(temp->next);
                }

        }

        return dummy->next;
    }

// Approach 2: Put all elements in min heap and pop out
 ListNode* mergeKLists(vector<ListNode*>& lists) {
     
        vector<int> llarr;
        priority_queue<int,vector<int>,greater<int>> p;

        for(ListNode* i:lists){
            ListNode* temp = i;

            while(temp){
                p.push(temp->val);
                temp=temp->next;
            }
        }

        ListNode* root = new ListNode(0);
        ListNode* temp = root;
        while(!p.empty()){
            temp->next = new ListNode(p.top());
            temp = temp->next;
            p.pop();
        }

        return root->next;

    }
  // Approach 1 : Just put all in an array, sort that array and build new linked list
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // code here
        vector<int> llarr;
        
        for(int i=0;i<lists.size();i++){
            ListNode* temp = lists[i];
            
            while(temp){
            llarr.push_back(temp->val);
            temp = temp->next;
            }
        }
        
        sort(llarr.begin(),llarr.end());
        
        ListNode* root = new ListNode(0);
        ListNode* temp=root;
        for(int i:llarr){
            ListNode* newNode = new ListNode(i);
            temp->next = newNode;
            temp = temp->next;
        }
        
        return root->next; 
    }
};
 struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
class Solution {
public:

// Approach 3:
 ListNode* mergeKLists(vector<ListNode*>& lists) {
      if(lists.empty()) return NULL;
       priority_queue<ListNode*,vector<ListNode*>,Compare> p;

        for(ListNode* i : lists){
            if(i){

        p.push(i);
            }
        }

        ListNode* dummy = new ListNode(0);
        ListNode* root = dummy;

        while(!p.empty()){
            ListNode* temp = p.top();
            p.pop();
            root->next = temp;
            root = root->next;

            if(temp->next) {
                p.push(temp->next);
                }

        }

        return dummy->next;
    }

// Approach 2: Put all elements in min heap and pop out
 ListNode* mergeKLists(vector<ListNode*>& lists) {
     
        vector<int> llarr;
        priority_queue<int,vector<int>,greater<int>> p;

        for(ListNode* i:lists){
            ListNode* temp = i;

            while(temp){
                p.push(temp->val);
                temp=temp->next;
            }
        }

        ListNode* root = new ListNode(0);
        ListNode* temp = root;
        while(!p.empty()){
            temp->next = new ListNode(p.top());
            temp = temp->next;
            p.pop();
        }

        return root->next;

    }
  // Approach 1 : Just put all in an array, sort that array and build new linked list
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // code here
        vector<int> llarr;
        
        for(int i=0;i<lists.size();i++){
            ListNode* temp = lists[i];
            
            while(temp){
            llarr.push_back(temp->val);
            temp = temp->next;
            }
        }
        
        sort(llarr.begin(),llarr.end());
        
        ListNode* root = new ListNode(0);
        ListNode* temp=root;
        for(int i:llarr){
            ListNode* newNode = new ListNode(i);
            temp->next = newNode;
            temp = temp->next;
        }
        
        return root->next; 
    }
};
 struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
class Solution {
public:

// Approach 3:
 ListNode* mergeKLists(vector<ListNode*>& lists) {
      if(lists.empty()) return NULL;
       priority_queue<ListNode*,vector<ListNode*>,Compare> p;

        for(ListNode* i : lists){
            if(i){

        p.push(i);
            }
        }

        ListNode* dummy = new ListNode(0);
        ListNode* root = dummy;

        while(!p.empty()){
            ListNode* temp = p.top();
            p.pop();
            root->next = temp;
            root = root->next;

            if(temp->next) {
                p.push(temp->next);
                }

        }

        return dummy->next;
    }

// Approach 2: Put all elements in min heap and pop out
 ListNode* mergeKLists(vector<ListNode*>& lists) {
     
        vector<int> llarr;
        priority_queue<int,vector<int>,greater<int>> p;

        for(ListNode* i:lists){
            ListNode* temp = i;

            while(temp){
                p.push(temp->val);
                temp=temp->next;
            }
        }

        ListNode* root = new ListNode(0);
        ListNode* temp = root;
        while(!p.empty()){
            temp->next = new ListNode(p.top());
            temp = temp->next;
            p.pop();
        }

        return root->next;

    }
  // Approach 1 : Just put all in an array, sort that array and build new linked list
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // code here
        vector<int> llarr;
        
        for(int i=0;i<lists.size();i++){
            ListNode* temp = lists[i];
            
            while(temp){
            llarr.push_back(temp->val);
            temp = temp->next;
            }
        }
        
        sort(llarr.begin(),llarr.end());
        
        ListNode* root = new ListNode(0);
        ListNode* temp=root;
        for(int i:llarr){
            ListNode* newNode = new ListNode(i);
            temp->next = newNode;
            temp = temp->next;
        }
        
        return root->next; 
    }
};
 struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
class Solution {
public:

// Approach 3:
 ListNode* mergeKLists(vector<ListNode*>& lists) {
      if(lists.empty()) return NULL;
       priority_queue<ListNode*,vector<ListNode*>,Compare> p;

        for(ListNode* i : lists){
            if(i){

        p.push(i);
            }
        }

        ListNode* dummy = new ListNode(0);
        ListNode* root = dummy;

        while(!p.empty()){
            ListNode* temp = p.top();
            p.pop();
            root->next = temp;
            root = root->next;

            if(temp->next) {
                p.push(temp->next);
                }

        }

        return dummy->next;
    }

// Approach 2: Put all elements in min heap and pop out
 ListNode* mergeKLists(vector<ListNode*>& lists) {
     
        vector<int> llarr;
        priority_queue<int,vector<int>,greater<int>> p;

        for(ListNode* i:lists){
            ListNode* temp = i;

            while(temp){
                p.push(temp->val);
                temp=temp->next;
            }
        }

        ListNode* root = new ListNode(0);
        ListNode* temp = root;
        while(!p.empty()){
            temp->next = new ListNode(p.top());
            temp = temp->next;
            p.pop();
        }

        return root->next;

    }
  // Approach 1 : Just put all in an array, sort that array and build new linked list
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // code here
        vector<int> llarr;
        
        for(int i=0;i<lists.size();i++){
            ListNode* temp = lists[i];
            
            while(temp){
            llarr.push_back(temp->val);
            temp = temp->next;
            }
        }
        
        sort(llarr.begin(),llarr.end());
        
        ListNode* root = new ListNode(0);
        ListNode* temp=root;
        for(int i:llarr){
            ListNode* newNode = new ListNode(i);
            temp->next = newNode;
            temp = temp->next;
        }
        
        return root->next; 
    }
};
 struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
class Solution {
public:

// Approach 3:
 ListNode* mergeKLists(vector<ListNode*>& lists) {
      if(lists.empty()) return NULL;
       priority_queue<ListNode*,vector<ListNode*>,Compare> p;

        for(ListNode* i : lists){
            if(i){

        p.push(i);
            }
        }

        ListNode* dummy = new ListNode(0);
        ListNode* root = dummy;

        while(!p.empty()){
            ListNode* temp = p.top();
            p.pop();
            root->next = temp;
            root = root->next;

            if(temp->next) {
                p.push(temp->next);
                }

        }

        return dummy->next;
    }

// Approach 2: Put all elements in min heap and pop out
 ListNode* mergeKLists(vector<ListNode*>& lists) {
     
        vector<int> llarr;
        priority_queue<int,vector<int>,greater<int>> p;

        for(ListNode* i:lists){
            ListNode* temp = i;

            while(temp){
                p.push(temp->val);
                temp=temp->next;
            }
        }

        ListNode* root = new ListNode(0);
        ListNode* temp = root;
        while(!p.empty()){
            temp->next = new ListNode(p.top());
            temp = temp->next;
            p.pop();
        }

        return root->next;

    }
  // Approach 1 : Just put all in an array, sort that array and build new linked list
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // code here
        vector<int> llarr;
        
        for(int i=0;i<lists.size();i++){
            ListNode* temp = lists[i];
            
            while(temp){
            llarr.push_back(temp->val);
            temp = temp->next;
            }
        }
        
        sort(llarr.begin(),llarr.end());
        
        ListNode* root = new ListNode(0);
        ListNode* temp=root;
        for(int i:llarr){
            ListNode* newNode = new ListNode(i);
            temp->next = newNode;
            temp = temp->next;
        }
        
        return root->next; 
    }
};
 struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
class Solution {
public:

// Approach 3:
 ListNode* mergeKLists(vector<ListNode*>& lists) {
      if(lists.empty()) return NULL;
       priority_queue<ListNode*,vector<ListNode*>,Compare> p;

        for(ListNode* i : lists){
            if(i){

        p.push(i);
            }
        }

        ListNode* dummy = new ListNode(0);
        ListNode* root = dummy;

        while(!p.empty()){
            ListNode* temp = p.top();
            p.pop();
            root->next = temp;
            root = root->next;

            if(temp->next) {
                p.push(temp->next);
                }

        }

        return dummy->next;
    }

// Approach 2: Put all elements in min heap and pop out
 ListNode* mergeKLists(vector<ListNode*>& lists) {
     
        vector<int> llarr;
        priority_queue<int,vector<int>,greater<int>> p;

        for(ListNode* i:lists){
            ListNode* temp = i;

            while(temp){
                p.push(temp->val);
                temp=temp->next;
            }
        }

        ListNode* root = new ListNode(0);
        ListNode* temp = root;
        while(!p.empty()){
            temp->next = new ListNode(p.top());
            temp = temp->next;
            p.pop();
        }

        return root->next;

    }
  // Approach 1 : Just put all in an array, sort that array and build new linked list
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // code here
        vector<int> llarr;
        
        for(int i=0;i<lists.size();i++){
            ListNode* temp = lists[i];
            
            while(temp){
            llarr.push_back(temp->val);
            temp = temp->next;
            }
        }
        
        sort(llarr.begin(),llarr.end());
        
        ListNode* root = new ListNode(0);
        ListNode* temp=root;
        for(int i:llarr){
            ListNode* newNode = new ListNode(i);
            temp->next = newNode;
            temp = temp->next;
        }
        
        return root->next; 
    }
};
 struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
class Solution {
public:

// Approach 3:
 ListNode* mergeKLists(vector<ListNode*>& lists) {
      if(lists.empty()) return NULL;
       priority_queue<ListNode*,vector<ListNode*>,Compare> p;

        for(ListNode* i : lists){
            if(i){

        p.push(i);
            }
        }

        ListNode* dummy = new ListNode(0);
        ListNode* root = dummy;

        while(!p.empty()){
            ListNode* temp = p.top();
            p.pop();
            root->next = temp;
            root = root->next;

            if(temp->next) {
                p.push(temp->next);
                }

        }

        return dummy->next;
    }

// Approach 2: Put all elements in min heap and pop out
 ListNode* mergeKLists(vector<ListNode*>& lists) {
     
        vector<int> llarr;
        priority_queue<int,vector<int>,greater<int>> p;

        for(ListNode* i:lists){
            ListNode* temp = i;

            while(temp){
                p.push(temp->val);
                temp=temp->next;
            }
        }

        ListNode* root = new ListNode(0);
        ListNode* temp = root;
        while(!p.empty()){
            temp->next = new ListNode(p.top());
            temp = temp->next;
            p.pop();
        }

        return root->next;

    }
  // Approach 1 : Just put all in an array, sort that array and build new linked list
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // code here
        vector<int> llarr;
        
        for(int i=0;i<lists.size();i++){
            ListNode* temp = lists[i];
            
            while(temp){
            llarr.push_back(temp->val);
            temp = temp->next;
            }
        }
        
        sort(llarr.begin(),llarr.end());
        
        ListNode* root = new ListNode(0);
        ListNode* temp=root;
        for(int i:llarr){
            ListNode* newNode = new ListNode(i);
            temp->next = newNode;
            temp = temp->next;
        }
        
        return root->next; 
    }
};
 struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
class Solution {
public:

// Approach 3:
 ListNode* mergeKLists(vector<ListNode*>& lists) {
      if(lists.empty()) return NULL;
       priority_queue<ListNode*,vector<ListNode*>,Compare> p;

        for(ListNode* i : lists){
            if(i){

        p.push(i);
            }
        }

        ListNode* dummy = new ListNode(0);
        ListNode* root = dummy;

        while(!p.empty()){
            ListNode* temp = p.top();
            p.pop();
            root->next = temp;
            root = root->next;

            if(temp->next) {
                p.push(temp->next);
                }

        }

        return dummy->next;
    }

// Approach 2: Put all elements in min heap and pop out
 ListNode* mergeKLists(vector<ListNode*>& lists) {
     
        vector<int> llarr;
        priority_queue<int,vector<int>,greater<int>> p;

        for(ListNode* i:lists){
            ListNode* temp = i;

            while(temp){
                p.push(temp->val);
                temp=temp->next;
            }
        }

        ListNode* root = new ListNode(0);
        ListNode* temp = root;
        while(!p.empty()){
            temp->next = new ListNode(p.top());
            temp = temp->next;
            p.pop();
        }

        return root->next;

    }
  // Approach 1 : Just put all in an array, sort that array and build new linked list
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // code here
        vector<int> llarr;
        
        for(int i=0;i<lists.size();i++){
            ListNode* temp = lists[i];
            
            while(temp){
            llarr.push_back(temp->val);
            temp = temp->next;
            }
        }
        
        sort(llarr.begin(),llarr.end());
        
        ListNode* root = new ListNode(0);
        ListNode* temp=root;
        for(int i:llarr){
            ListNode* newNode = new ListNode(i);
            temp->next = newNode;
            temp = temp->next;
        }
        
        return root->next; 
    }
};
 struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
class Solution {
public:

// Approach 3:
 ListNode* mergeKLists(vector<ListNode*>& lists) {
      if(lists.empty()) return NULL;
       priority_queue<ListNode*,vector<ListNode*>,Compare> p;

        for(ListNode* i : lists){
            if(i){

        p.push(i);
            }
        }

        ListNode* dummy = new ListNode(0);
        ListNode* root = dummy;

        while(!p.empty()){
            ListNode* temp = p.top();
            p.pop();
            root->next = temp;
            root = root->next;

            if(temp->next) {
                p.push(temp->next);
                }

        }

        return dummy->next;
    }

// Approach 2: Put all elements in min heap and pop out
 ListNode* mergeKLists(vector<ListNode*>& lists) {
     
        vector<int> llarr;
        priority_queue<int,vector<int>,greater<int>> p;

        for(ListNode* i:lists){
            ListNode* temp = i;

            while(temp){
                p.push(temp->val);
                temp=temp->next;
            }
        }

        ListNode* root = new ListNode(0);
        ListNode* temp = root;
        while(!p.empty()){
            temp->next = new ListNode(p.top());
            temp = temp->next;
            p.pop();
        }

        return root->next;

    }
  // Approach 1 : Just put all in an array, sort that array and build new linked list
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // code here
        vector<int> llarr;
        
        for(int i=0;i<lists.size();i++){
            ListNode* temp = lists[i];
            
            while(temp){
            llarr.push_back(temp->val);
            temp = temp->next;
            }
        }
        
        sort(llarr.begin(),llarr.end());
        
        ListNode* root = new ListNode(0);
        ListNode* temp=root;
        for(int i:llarr){
            ListNode* newNode = new ListNode(i);
            temp->next = newNode;
            temp = temp->next;
        }
        
        return root->next; 
    }
};