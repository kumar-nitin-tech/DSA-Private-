#include<bits/stdc++.h>
using namespace std;

class graph{
    public:
    unordered_map<int,vector<int>>adjList;

    void addEdges(int u, int v){
        adjList[u].push_back(v);
    }
};

vector<int>TopologicalSort(unordered_map<int,vector<int>>&adjList, int nodes){
    vector<int>inDegree(nodes,0);
    vector<int>ans;
    for(auto i:adjList){
        for(auto j:i.second){
            inDegree[j]++;
        }
    }
    queue<int>q;
    for(int i=1;i<nodes;i++){
        if(inDegree[i] == 0){
            q.push(i);
        }
    }

    while(!q.empty()){
        int front = q.front();
        q.pop();
        ans.push_back(front);
        for(auto i:adjList[front]){
            inDegree[i]--;
            if(inDegree[i] == 0){
                q.push(i);
            }
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
    graph gph;
    for(auto i:edges){
        gph.addEdges(i.first,i.second);
    }

    vector<int>ans = TopologicalSort(gph.adjList,nodes);
    for(auto i:ans){
        cout<<i<<" ";
    }

    return 0;
}