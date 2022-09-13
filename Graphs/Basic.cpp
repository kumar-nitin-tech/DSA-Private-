#include<bits/stdc++.h>
using namespace std;
//Undirected Graphs representation
void adjacencyMatrix(){
    //Adjanecy Matrix method to represent matrix
    //n-> No. of nodes in the graphs, m->no. of edges in the graphs
    int u,v,n,m;
    cin>>n>>m;
    //Defining the 2d matrix for graph
    vector<vector<int>>adjGraph(n,vector<int>(m));
    for(int i=0;i<m;i++){
        cin>>v>>u;
        adjGraph[u][v] = 1;
        adjGraph[v][u] = 1;
    }

    for(auto i:adjGraph){
        for(auto j:i){
            cout<<j<<" ";
        }
        cout<<"\n";
    }

}

void adjacnecyList(){
    int n,m;
    cin>>n>>m;
    //using map and mapping indices with list
    cout<<"using map data structure\n";
    unordered_map<int,vector<int>>adjList;
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
    for(auto i:adjList){
        cout<<i.first<<"->";
        for(auto j:i.second){
            cout<<j<<" ";
        }
        cout<<"\n";
    }


    //using vector,array
    cout<<"using vector:\n";
    vector<int> adjList2[n];
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        adjList2[u].push_back(v);
        adjList2[v].push_back(u);
    }

    for(int i=0;i<n;i++){
        for(auto j:adjList2[i]){
            cout<<j<<" ";
        }
        cout<<endl;
    }

}

int main(){

    //Adjaency List
    adjacnecyList();
    return 0;
}