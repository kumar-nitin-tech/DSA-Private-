#include<bits/stdc++.h>
using namespace std;

//function for bell man ford algorithm 
//TC: O(V*E) V= vertices of graph and E = edges of graph
vector<int> shortestDistance(int nodes, int src, vector<vector<int>> &edges){
    //store distance in dist vector
    vector<int> dist(nodes, 1e6);
    dist[src] = 0;
    for(int i=0; i < nodes;i++){
        for(int j=0;j<edges.size();j++){
            int u = edges[j][0];
            int v= edges[j][1];
            int wt = edges[j][2];
            if(dist[u] + wt < dist[v]){
                dist[v] =dist[u] + wt;
            }
        }
    }

    //checking negative cycle
    bool flag = 0;
    for(int j=0;j<edges.size();j++){
            int u = edges[j][0];
            int v= edges[j][1];
            int wt = edges[j][2];
            if(dist[u] + wt < dist[v]){
                flag = 1;
            }
    }
    if(flag == 1){
        return {-1};
    }
    return dist;
}

int main(){
    int nodes,vertex,src;
    cin>>nodes>>vertex>>src;
    vector<vector<int>> edges(vertex,vector<int>(3));
    for(int i=0;i<vertex;i++){
        cin>>edges[i][0] >> edges[i][1] >> edges[i][2];
    }
    vector<int>ans =shortestDistance(nodes,src,edges);

    for(auto i:ans){
        cout<<i<<" ";
    }
    return 0;
}