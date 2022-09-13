#include<bits/stdc++.h>
using namespace std;

class graph{
    public:
    unordered_map<int,vector<int>>adj;

    void insertEdges(int u, int v, bool direction){
        //direction -> 1 Directed graph
        //direction -> 0 undirected graph
        if(direction){
            adj[u].push_back(v);
        }
        else{
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }

    void print(){
        for(auto i:adj){
            cout<<i.first<<"->";
            for(auto j:i.second){
                cout<<j<<" ";
            }
            cout<<"\n";
        }
    }
};

int main(){
    graph dg;
    dg.insertEdges(0,1,1);
    dg.insertEdges(1,2,1);
    dg.insertEdges(2,3,1);
    dg.insertEdges(3,1,1);
    dg.insertEdges(3,4,1);
    dg.insertEdges(4,0,1);
    dg.print();
    return 0;
}