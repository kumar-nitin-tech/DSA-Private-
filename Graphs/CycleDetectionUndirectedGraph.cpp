/*
    Detect Cycle in the Undirected Graph
*/

#include<bits/stdc++.h>
using namespace std;

class graph{
    public:
    unordered_map<int,vector<int>>adjList;

    void addEdges(int u, int v){
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
    void print(){
        for(auto i:adjList){
            cout<<i.first<<" -> ";
            for(auto j:i.second){
                cout<<j<<" ";
            }
            cout<<endl;
        }
    }
};

//bfs Util function
bool bfsCycleUtil(unordered_map<int,vector<int>>&adjList, vector<bool>&visited, int i){
    queue<pair<int,int>>q;
    q.push({i,-1});
    visited[i] = 1;
    while(!q.empty()){
        int node = q.front().first;
        int parent = q.front().second;
        q.pop();

        for(auto j:adjList[node]){
            if(visited[j] == 1 && parent != j){
                return true;
            }
            else if(!visited[j]){
                q.push({j,node});
                visited[j] = 1;
            }
        }
    }
    return false;
}

//Time Complexity: O(n+e)
//Space Complexity: O(n+e)+O(n)
//BFS Traversal for Cycle Detection
bool bfsCycleDetection(unordered_map<int,vector<int>>&adjList, int node){
    vector<bool>visited(node,0);

    for(int i=0;i<node;i++){
        if(!visited[i]){
            if(bfsCycleUtil(adjList,visited,i)){
                return true; 
            }
        }
    }
}


bool dfsUtil(unordered_map<int,vector<int>>&adjList, int node, int parent, vector<bool>&visited){
    visited[node] = 1;
    for(auto i:adjList[node]){
        if(!visited[i]){
            if(dfsUtil(adjList,i,node,visited)){
                return true;
            }
        }
        else if(i != parent){
            return true;
        }
    }
    return false;
}

//DFS Traversal for Cycle Detection 
//Time Complexity: O(n)
//Space Complexity: O(n)
bool dfsCyclDetection(unordered_map<int,vector<int>>&adjList, int node){
    vector<bool>visited(node,0);
    for(int i=0;i<node;i++){
        if(!visited[i]){
            if( dfsUtil(adjList,i,-1,visited)){
                return true;
            }
        }
    }
}

int main(){
    int node,vertex;
    cin>>node>>vertex;
    vector<pair<int,int>>edges(vertex);
    for(auto &i:edges){
        cin>>i.first>>i.second;
    }
    graph gph;
    for(auto i:edges){
        gph.addEdges(i.first,i.second);
    }
    if(dfsCyclDetection(gph.adjList,node)){
        cout<<"Yes";
    }
    else{
        cout<<"No";
    }
    //cout<<bfsCycleDetection(gph.adjList,node);

    return 0;
}