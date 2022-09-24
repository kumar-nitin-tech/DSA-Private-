/*
    DFS :Depth First Traversal

    Time Complexity:O(n+e)
    Space Complexity: O(n+e)+O(n); AdjList, Visited Array Space
*/

#include<bits/stdc++.h>
using namespace std;

class graph{
    public:
    unordered_map<int,vector<int>>adList;
    
    void addEdges(int u,int v){
        adList[u].push_back(v);
        adList[v].push_back(u);
    }
};

void dfsUtil(int n,vector<bool>&visited,vector<int>&ans,unordered_map<int,vector<int>>&adList){

    ans.push_back(n);
    visited[n] = 1;

    for(auto i: adList[n]){
        if(!visited[i]){
            dfsUtil(i,visited,ans,adList);
        }
    }
}

vector<int> dfsTraversal(unordered_map<int,vector<int>>&adList, int node){
    vector<bool>visited(node);
    vector<int>ans;
    for(int i=0;i<node;i++){
        if(!visited[i]){
            dfsUtil(i,visited,ans,adList);
        }
    }
    return ans;
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
    vector<int>ans;
    ans = dfsTraversal(gph.adList,node);
    for(auto i:ans){
        cout<<i<<" ";
    }
    return 0;
}