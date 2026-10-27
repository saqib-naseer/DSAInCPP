#include <iostream>
using namespace std;
#include <vector>

int main() {

   // Directed Graph
  int vertex, edge;
  
  cout<<"Enter Vertex and Edges"<<endl;
  cin>>vertex>> edge;

  vector<vector<int>>adj(vertex+1,vector<int>(vertex+1,0));

  int u,v,w;
  for(int i=0;i<edge;i++){
    cin>>u>>v>>w;
    adj[u][v]=w;
  }

  // Print 

  for(int i=0;i<adj.size();i++){
    for(int j=0;j<adj[i].size();j++){
      cout<<adj[i][j]<< " ";
    }
    cout<<endl;
  }

  /*
  // Undirected Graph
  int vertex, edge;
  
  cout<<"Enter Vertex and Edges"<<endl;
  cin>>vertex>> edge;

  vector<vector<int>>adj(vertex+1,vector<int>(vertex+1,0));

  int u,v,w;
  for(int i=0;i<edge;i++){
    cin>>u>>v>>w;
    adj[u][v]=w;
    adj[v][u]=w;
  }

  // Print 

  for(int i=0;i<adj.size();i++){
    for(int j=0;j<adj[i].size();j++){
      cout<<adj[i][j]<< " ";
    }
    cout<<endl;
  }
  */
  
}
