/*
    DIjkstra's Algorithm using Priority Queue
*/
#include<bits/stdc++.h>
using namespace std;

//making adjacency list including weight/dist
class graph{
    public:
    unordered_map<int,vector<pair<int,int>>>adjList;

    void addEdges(int u, int v, int wt){
        adjList[u].push_back({v,wt});
        adjList[v].push_back({u,wt});
    }
};

//function for shortest path in undirected graph using dijsktra's algorithm
vector<int> shortestPathDijsktraAlgo(unordered_map<int,vector<pair<int,int>>>&adjList, int nodes, int src){
    //minHeap            nd  dist
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    vector<int>dist(nodes,INT_MAX);
    dist[src] = 0;
    pq.push({src,0});
    while(!pq.empty()){
        auto top = pq.top();
        pq.pop();
        int node = top.first;
        int wt = top.second;
        for(auto i:adjList[node]){
            if(dist[node] + i.second < dist[i.first]){
                dist[i.first] = i.second + wt;
                pq.push({i.first,dist[i.first]});
            }
        }
    }

    return dist;
}

//function for dijkstra's algo using sets
vector<int> shortestPathDijsktraAlgoSets(unordered_map<int,vector<pair<int,int>>>&adjList, int nodes, int src){
    set<pair<int,int>> st;
    vector<int> dist(nodes,INT_MAX);
    dist[src] = 0;
    st.insert({src,0});
    //V = no. of edges
    //Heap size for worst case is v^2
    //O(V)
    while(!st.empty()) {
        //O(log(heapSize))
        auto it = *st.begin();
        int node = it.first;
        int wt = it.second;
        st.erase(it);
        //O(ne); ne = worst case would be V-1
        for(auto i:adjList[node]){
            int adjNode = i.first;
            if(wt + i.second < dist[adjNode]){
                if(dist[i.first] != INT_MAX){
                    st.erase({adjNode,dist[adjNode]});
                }
                dist[adjNode] = wt + i.second;
                //O(log(heapSize))
                st.insert({adjNode,dist[adjNode]});
            }
        }
    }
    return dist;
}

int main(){
    int nodes,vertices,weight,src;
    cin>>nodes>>vertices>>src;
    vector<pair<int,pair<int,int>>>edges(vertices);
    for(auto &i:edges){
        //      u            v               wt
        cin>>i.first>>i.second.first>>i.second.second;
    }
    graph gph;
    for(auto i:edges){
        gph.addEdges(i.first,i.second.first,i.second.second);
    }

    vector<int>dist = shortestPathDijsktraAlgoSets(gph.adjList,nodes,src);
    for(auto i:dist){
        cout<<i<<" ";
    }
    return 0;
}