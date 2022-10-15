//Topological Sort
//U come before v
//Linear Order 

#include<bits/stdc++.h>
using namespace std;

class graph{
    public:
    unordered_map<int,vector<int>>adjList;

    void addEdges(int u, int v){
        adjList[u].push_back(v);
    }
};


//DFS traversal
void dfs(vector<bool>&visited, int node,stack<int>&st, unordered_map<int,vector<int>>&adjList){
    visited[node] = 1;
    for(auto i:adjList[node]){
        if(!visited[i]){
            dfs(visited,i,st,adjList);
        }
    }
    st.push(node);

}


// Main function for topological Sort 
//Time Complexity:O(n)
//Space Complexity : O(n)
vector<int> topologicalSort(unordered_map<int,vector<int>>&adjList, int nodes){
    vector<int>ans;
    vector<bool>visited(nodes,0);
    stack<int>st;
    for(int i=0;i<nodes;i++){
        if(!visited[i]){
            dfs(visited,i,st,adjList);
        }
    }
    while(!st.empty()){
        ans.push_back(st.top());
        st.pop();
    }
    return ans;
}

int main(){
    int node,vertices;
    cin>>node>>vertices;
    vector<pair<int,int>>edges(vertices);
    for(auto &i:edges){
        cin>>i.first>>i.second;
    }
    graph gph;
    for(auto i:edges){
        gph.addEdges(i.first,i.second);
    }
    vector<int>ans(node);
    ans = topologicalSort(gph.adjList,node);
    for(int i=0;i<node;i++){
        cout<<ans[i]<<" ";
    }
    return 0;
}