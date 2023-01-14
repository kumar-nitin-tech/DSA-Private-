/*
    Kosraju's Algorithm
*/
#include<bits/stdc++.h>
using namespace std;

class graph{
    public:
    unordered_map<int,vector<int>> adjList;

    void addEdges(int u, int v){
        adjList[u].push_back(v);
    }
};

void dfs(unordered_map<int,vector<int>> &adjList, stack<int> &st, int node, vector<int> &vis){
    vis[node] = 1;
    for(auto i:adjList[node]){
        if(!vis[i]){
            dfs(adjList,st,i,vis);
        }
    }
    st.push(node);
}
void DFS( unordered_map<int,vector<int>> &transpose,  vector<int> &vis, int node, vector<int> &temp){
    vis[node] = 1;
    temp.push_back(node);
    for(auto it:transpose[node]){
        if(!vis[it]){
            DFS(transpose,vis,it,temp);
        }
    }
}

vector<vector<int>> kosarajuAlgorithm(unordered_map<int,vector<int>> &adjList, int nodes){
    vector<vector<int>> ans;
    vector<int> temp;
    //1. Topological Sort
    stack<int> st;
    vector<int> vis(nodes,0);
    for(int i=0;i<nodes;i++){
        if(!vis[i]){
            dfs(adjList,st,i,vis);
        }
    }

    //Transpose the graph
    unordered_map<int,vector<int>> transpose;
    for(int i=0;i<nodes;i++){
        vis[i] = 0;
        for(auto it:adjList[i]){
            transpose[it].push_back(i);
        }
    }

    //DFS for counting
    while(!st.empty()){
        int top = st.top();
        st.pop();
        if(!vis[top]){
            temp.clear();
            DFS(transpose,vis,top,temp);
            ans.push_back(temp);
        }
    } 
    return ans;
}

int main(){
    int nodes, vertices;
    cin>>nodes>>vertices;
    vector<vector<int>> edges(vertices, vector<int>(2));
    for(int i=0;i<vertices;i++){
        for(int j=0;j<2;j++){
            cin>>edges[i][j];
        }
    }
    
    graph gph;
    for(auto i:edges){
        int u = i[0];
        int v = i[1];
        gph.addEdges(u,v);
    }
    vector<vector<int>> ans = kosarajuAlgorithm(gph.adjList,nodes);

    for(auto i:ans){
        for(auto it:i){
            cout<<it<<" ";
        }
        cout<<endl;
    }
    return 0;
}