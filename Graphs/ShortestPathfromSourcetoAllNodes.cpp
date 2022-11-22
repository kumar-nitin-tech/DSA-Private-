/*
    Given an Undirected Graph having unit weight, find the shortest path from the source to all other nodes in this graph. In this problem statement,
    we have assumed the source vertex to be ‘0’. If a vertex is unreachable from the source node, then return -1 for that vertex.
*/

#include<bits/stdc++.h>
using namespace std;

class graph {
    public:
    unordered_map<int,vector<int>>adjList;

    void addEdges(int u, int v){
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
};

//Tim Complexity: O(n+e)
vector<int> shortestPathFromSource(unordered_map<int,vector<int>>&adjList, int nodes, int src){
    vector<int>dist(nodes,1e9);

    queue<int>q;
    q.push(src);
    dist[src] = 0;
    while(!q.empty()){
        int front = q.front();
        q.pop();
        for(auto i:adjList[front]){
            if(dist[front]+1 < dist[i]){
                dist[i] = dist[front] + 1;
                q.push(i);
            }
        }
    }

    vector<int>ans(nodes,-1);
    for(int i=0;i<nodes;i++){
        if(dist[i] != 1e9){
            ans[i] = dist[i];
        }
    }
    return ans;
}

int main(){
    int nodes,vertices;
    cin>>nodes>>vertices;
    vector<pair<int,int>>edges(vertices);
    for(auto &i:edges){
        cin>>i.first>>i.second;
    }
    int src;
    cin>>src;

    graph gph;
    for(auto i:edges){
        gph.addEdges(i.first,i.second);
    }

    vector<int>ans = shortestPathFromSource(gph.adjList,nodes,src);

    for(auto i:ans){
        cout<<i<<" ";
    }
    
    return 0;
}