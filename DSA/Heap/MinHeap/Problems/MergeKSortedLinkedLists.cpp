
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