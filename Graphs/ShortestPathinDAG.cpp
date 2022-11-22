/*
    Algorithm:
    1. DO Topological Sort
    2. One by one remove element from sorted stack and update distance array
    
    Intuition :
    Processing the vertices in topological order ensures that by the time you get to a vertex,
    you’ve already processed all the vertices that can precede it which reduces the computation time significantly. 
*/
#include<bits/stdc++.h>
using namespace std;

class graph{
    public:
    unordered_map<int,vector<pair<int,int>>>adjList;

    void addEdges(int u, int v, int wt){
        pair<int,int> p = make_pair(v,wt);
        adjList[u].push_back(p);
    }
};

void dfs(vector<bool>&vis, int node, stack<int>&s, unordered_map<int,vector<pair<int,int>>>&adjList){
    vis[node] = 1;
    for(auto i:adjList[node]){
        if(!vis[i.first]){
            dfs(vis,i.first,s,adjList);
        }
    }
    s.push(node);
}

void topoLogicalSort(unordered_map<int,vector<pair<int,int>>>&adjList, int nodes, int src, stack<int>&s){
    vector<bool>vis(nodes,false);
    for(int i = src;i<nodes;i++){
        if(!vis[i]){
            dfs(vis,i,s,adjList);
        }
    }
}

vector<int> shortestPathDAG(unordered_map<int,vector<pair<int,int>>>&adjList, int nodes, int src){
    stack<int> s;
    topoLogicalSort(adjList,nodes,src,s);
    vector<int>dist(nodes,INT_MAX);
    dist[src] = 0;

    while(!s.empty()){
        int top = s.top();
        s.pop();
        if(dist[top] != INT_MAX){
            for(auto i:adjList[top]){
                if(i.second+dist[top] < dist[i.first]){
                    dist[i.first] = i.second + dist[top];
                }
            }
        }
    }

    return dist;
}

int main(){
    int nodes,vertice,src;
    cin>>nodes>>vertice>>src;

    vector<pair<int,pair<int,int>>> edges(vertice);
    for(auto &i:edges){
        cin>>i.first>>i.second.first>>i.second.second;
    }
    graph gph;
    for(auto i:edges){
        gph.addEdges(i.first,i.second.first,i.second.second);
    }
    vector<int> ans = shortestPathDAG(gph.adjList,nodes,src);

    for(auto i:ans){
        cout<<i<<" ";
    }
    return 0;
}