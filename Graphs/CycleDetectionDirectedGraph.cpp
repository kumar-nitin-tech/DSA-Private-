#include<bits/stdc++.h>
using namespace std;

class graph{
    public:
    unordered_map<int,vector<int>>adjList;

    void addEdges(int u, int v){
        adjList[u].push_back(v);
    }
};

//Time Complexity: O(n)
//Space Complexity: o(n)
bool dfsUtil(unordered_map<int,vector<int>>&adjList, vector<bool>&visited, vector<bool>&pathVisited, int node){
    visited[node] = 1;
    pathVisited[node] = 1;
    for(auto i:adjList[node]){
        if(!visited[i]){
            if(dfsUtil(adjList,visited,pathVisited,i)){
                return true;
            }
        }
        else if(pathVisited[i]){
            return true;
        }
    }
    pathVisited[node] = 0;
    return false;
}

bool dfsDirectedGraph(unordered_map<int,vector<int>>&adjList, int node){
    vector<bool>visited(node,0);
    vector<bool>pathVisited(node,0);
    for(int i=0;i<node;i++){
        if(!visited[i]){
            if(dfsUtil(adjList,visited,pathVisited,i)){
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

    cout<<dfsDirectedGraph(gph.adjList,node);
    return 0;
}
