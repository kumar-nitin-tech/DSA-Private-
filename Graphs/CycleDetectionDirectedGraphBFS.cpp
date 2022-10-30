//Directed Graph Detection using Kahns Algo BFS
#include<bits/stdc++.h>
using namespace std;
class graph{
    public:
    unordered_map<int,vector<int>>adjList;

    void addEdges(int u, int v){
        adjList[u].push_back(v);
    }
};

bool bfsDirectedGraphDetection(unordered_map<int,vector<int>>&adjList, int nodes){
    vector<int>indegree(nodes,0);
    for(auto i:adjList){
        for(auto j:i.second){
            indegree[j]++;
        }
    }
    //This represent whether the topological sort is valid or not if count is equal to no. of nodes than it is valid sort or else not
    int count = 0;
    queue<int>q;
    for(int i=0;i<nodes;i++){
        if(indegree[i] == 0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int front = q.front();
        q.pop();
        count ++;
        for(auto i:adjList[front]){
            indegree[i]--;
            if(indegree[i] == 0){
                q.push(i);
            }
        }
    }
    if(count == nodes){
        return false;
    }
    else{
        return true;
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

    cout<<bfsDirectedGraphDetection(gph.adjList,node);   
    return 0;
}