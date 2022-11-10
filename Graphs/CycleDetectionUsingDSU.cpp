#include<bits/stdc++.h>
using namespace std;

class disJoint{
    vector<int>rank,parent;
    public:
    disJoint(int nodes){
        rank.resize(nodes+1,0);
        parent.resize(nodes+1);

        for(int i=0;i<=nodes;i++){
            parent[i] = i;
        }
    }

    int findParent(int node){
        if(parent[node] == node){
            return node;
        }
        //Path Compression
        return parent[node] = findParent(parent[node]);
    }

    void unionByRank(int u, int v){
        int ulpU = findParent(u), ulpV = findParent(v);
        if(ulpU == ulpV){
            return;
        }

        if(rank[ulpV] > rank[ulpU]){
            parent[ulpU] = ulpV;
        }

        else if(rank[ulpU] > rank[ulpV]){
            parent[ulpV] = ulpU;
        }

        else{
            parent[ulpU] = ulpV;
            //rank would increase of the ultimate new parent in this case its v as u is been connected to v so v is ultimate parent of graph
            rank[ulpV] ++;
        }
    }

};

bool isCycleUndirectedGraph(vector<pair<int,int>>&edges, int nodes){
    pair<int,int>vertices;
    disJoint dsu(nodes);
    for(int i=0;i<edges.size();i++){
        vertices = edges[i];
        int u = vertices.first;
        int v = vertices.second;
        if(dsu.findParent(u) != dsu.findParent(v)){
            dsu.unionByRank(u,v);
        }
        else if(dsu.findParent(u) == dsu.findParent(v)){
            return true;
        }
    }
    return false;
}

int main(){
    int nodes,vertex;
    cin>>nodes>>vertex;
    vector<pair<int,int>>edges(vertex);
    for(auto &i:edges){
        cin>>i.first>>i.second;
    }

    cout<<isCycleUndirectedGraph(edges,nodes);

    return 0;
}