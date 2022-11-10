#include<bits/stdc++.h>
using namespace std;

//DSU Union by rank
class DisJoint{
    vector<int>rank,parent,size;
    public:
    DisJoint(int n){
        //Resizing to n+1 so that it would take 1 base indexing also
        rank.resize(n+1,0);
        parent.resize(n+1);
        size.resize(n+1,1);

        //In this step we are assiging the parent to each which is the node itself as it is single node
        for(int i=0;i<=n;i++){
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

    void UnionRank(int u, int v){
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
        else {
            parent[ulpV] = ulpU;
            rank[ulpU] ++;
        }
    }

    void unionSize(int u, int v){
        int ulpU = findParent(u);
        int ulpV = findParent(v);
        if(ulpU == ulpV) return;
        if(size[ulpU] > size[ulpV]){
            parent[ulpV] = ulpU;
            size[ulpU] += size[ulpV];
        }
        else if(rank[ulpV] > rank[ulpU]){
            parent[ulpU] = ulpV;
            size[ulpV] += size[ulpU];
        }
        else {
            parent[ulpV] = ulpU;
            size[ulpU] += size[ulpV];
        }

    }
};

int main(){
    DisJoint ds(7);
    ds.unionSize(1, 2); 
    ds.unionSize(2, 3); 
    ds.unionSize(4, 5); 
    ds.unionSize(6, 7); 
    ds.unionSize(5, 6); 
    // if 3 and 7 same or not 
    if(ds.findParent(3) == ds.findParent(7)) {
        cout << "Same\n"; 
    }
    else cout << "Not same\n"; 

    ds.unionSize(3, 7); 

    if(ds.findParent(3) == ds.findParent(7)) {
        cout << "Same\n"; 
    }
    else cout << "Not same\n"; 
	return 0;
    return 0;
}