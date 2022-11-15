/*
    Shortest Path between 2 nodes in Undirected Graphs and distance between 2 nodes are 1
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
};

//TC: O(n+e)
vector<int> shortestPathBetweenTwoNodes(unordered_map<int,vector<int>>&adjList, int nodes, int s,int t){
    vector<bool>vis(nodes,0);
    vector<int>parent(nodes);

    queue<int>q;
    q.push(s);
    vis[s] = 1;
    parent[s] = -1;
    //TC = O(n)
    while(!q.empty()){
        int front = q.front();
        q.pop();
        for(auto i:adjList[front]){
            if(!vis[i]){
                vis[i] = 1;
                parent[i] = front;
                q.push(i);
            }
        }
    }

    vector<int>ans;
    int curr = t;
    ans.push_back(t);
    while(curr != s){
        curr = parent[curr];
        ans.push_back(curr);
    }
    reverse(ans.begin(),ans.end());
    return ans;
}

int main(){
    int nodes,vertices;
    cin>>nodes>>vertices;
    vector<pair<int,int>> edges(vertices);
    for(auto &i:edges){
        cin>>i.first>>i.second;
    }
    //input 2 nodes whose path is to find
    int s,t;
    cin>>s>>t;
    graph gph;
    for(auto i:edges){
        gph.addEdges(i.first,i.second);
    }

    vector<int>ans = shortestPathBetweenTwoNodes(gph.adjList,nodes,s,t);

    for(auto i:ans){
        cout<<i<<" ";
    }
    return 0;
}