/*
    This is the code for MST using kruskal Algorithm which is using Disjoint Set DS
*/

#include<bits/stdc++.h>
using namespace std;

//Disjoint DS

class disjoint{
    vector<int>parent,rank;

    public:
    disjoint(int node){
        parent.resize(node+1);
        rank.resize(node+1,0);

        for(int i=0;i<=node;i++){
            parent[i] = i;
        }
    }

    int findParent(int node){
        if(parent[node] == node){
            return node;
        }
        return parent[node] = findParent(parent[node]);
    }

    void unionByRank(int u, int v){
        int ulpU = findParent(u);
        int ulpV = findParent(v);
        if(ulpU == ulpV)
            return;

        if(rank[ulpU] > rank[ulpV]){
            parent[ulpV] = ulpU;
        }
        else if(rank[ulpV] > rank[ulpU]){
            parent[ulpU] = ulpV;
        }
        else if(rank[ulpV] == rank[ulpU]) {
            parent[ulpU] = ulpV;
            rank[ulpU]++;
        }
    }

};

//Kruskal Algorithm to find MST 
//Time Complexity : O(nlogn + n)
vector<pair<int,int>> kruskalAlgoMST(vector<pair<int,pair<int,int>>>&edges, int nodes, int &mstSum){
    //TC O(n log n)
    sort(edges.begin(),edges.end());
    vector<pair<int,int>>ans;
    disjoint ds(nodes);
    //Tc O(n)
    for(auto i:edges){
        int wt = i.first;
        int u = i.second.first;
        int v = i.second.second;
        //Tc O(4 alpha)
        if(ds.findParent(u) != ds.findParent(v)){
            mstSum += wt;
            ans.push_back({u,v});
            ds.unionByRank(u,v);
        }
    }
    return ans;
}

int main(){
    int nodes, vertices;
    cin>>nodes>>vertices;
    //We are taking input as wt, u,v
    vector<pair<int,pair<int,int>>>edges(vertices);
    for(auto &i:edges){
        //    wt        u               v
        cin>>i.first>>i.second.first>>i.second.second;
    }
    int mstSum = 0;
    vector<pair<int,int>>ans = kruskalAlgoMST(edges,nodes,mstSum);
    for(auto i:ans){
        cout<<i.first<<" "<<i.second<<"\n";
    }
    cout<<mstSum;
    return 0;
}