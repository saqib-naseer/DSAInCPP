#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
  // Undirected Weighted
  
  cout<<"Enter vertex count and edges count"<<endl;
  int vertex,edge;
  cin>>vertex>>edge;

  // Simple vector can also be done
  //vector<vector<pair<int,int>>>adj(vertex+1);

  unordered_map<int,vector<pair<int,int>>> adj;
  
  int v,u,w;
  
  for(int i=0;i<edge;i++){
    cin>>v>>u>>w;    
    adj[v].push_back({u,w});
    adj[u].push_back({v,w});
  }

  // Display
 /* for(int i=0;i<adj.size();i++){
    cout<<i<<"-->";
    for(int j=0;j<adj[i].size();j++){
         cout<<"{"<<adj[i][j].first<< " " <<adj[i][j].second<< "} ";
    }
    cout<<endl;
  }
*/
  for(auto &node : adj) {

        cout << node.first << " -> ";

        for(pair<int,int> neighbour : node.second) {
            cout << "{"<<neighbour.first << " "<<neighbour.second<<"} ";
        }

        cout << endl;
    }

  
 /*   // Undirected 
  
  cout<<"Enter vertex count and edges count"<<endl;
  int vertex,edge;
  cin>>vertex>>edge;

  vector<vector<int>>adj(vertex+1);
  int v,u,w;
  
  for(int i=0;i<edge;i++){
    cin>>v>>u>>w;    
    adj[v].push_back(u);
    adj[u].push_back(v);
  }

  // Display
  for(int i=0;i<adj.size();i++){
    cout<<i<<"-->";
    for(int j=0;j<adj[i].size();j++){
          cout<<adj[i][j]<<" ";
    }
    cout<<endl;
  }
  */
}
