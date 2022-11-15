/*
    MST: Spanning Tree whose total weight of the graph is minimum or equal to other wieght of the spanning tree of same graph
*/

#include<bits/stdc++.h>
using namespace std;

class graph{
    public:

    unordered_map<int,vector<pair<int,int>>>adjList;

    void addEdges(int u,int v,int wt){
        adjList[u].push_back({v,wt});
        adjList[v].push_back({u,wt});
    }
};

//Time Complexity: O(E logE)

vector<pair<int,int>>primsAlgo(unordered_map<int,vector<pair<int,int>>>&adjList, int nodes, int &mstSum, vector<pair<pair<int,int>,int>>&edges){
    //in priority queue we are storing {wt,node,parent}
    priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>,greater<pair<int,pair<int,int>>>>pq;

    vector<pair<int,int>>ans;

    vector<int>vis(nodes,0);
    //intialising the minHeap with starting node
    pq.push({0,{0,-1}});
    
    //TC E logE+E log E
    //TC O(E logE)
    while(!pq.empty()){
        //TC log E
        auto it = pq.top();
        pq.pop();
        int node = it.second.first;
        int weight = it.first;
        int parent = it.second.second;

        if(vis[node] == 1){
            continue;
        }
        vis[node] = 1;
        ans.push_back({parent,node});
        mstSum += weight;
        //push adjacent nodes in the minHeap
        
        //TC E+logE 
        for(auto i:adjList[node]){
            int adjNode = i.first;
            int nodeWt = i.second;
            if(!vis[adjNode]){
                pq.push({nodeWt,{adjNode,node}});
            }
        }
    }

    return ans;
}

int main(){
    int nodes, vertices;
    cin>>nodes>>vertices;
    vector<pair<pair<int,int>,int>>edges(vertices);
    for(auto &i:edges){
        cin>>i.first.first>>i.first.second>>i.second;
    }
    graph gph;
    for(auto i:edges){
        gph.addEdges(i.first.first,i.first.second,i.second);
    }
    int mstSum = 0;
    vector<pair<int,int>>mstList = primsAlgo(gph.adjList,nodes,mstSum,edges);
    for(int i =1;i<mstList.size();i++){
        cout<<mstList[i].first<<" "<<mstList[i].second<<"\n";
    }
    cout<<mstSum;
    return 0;
}