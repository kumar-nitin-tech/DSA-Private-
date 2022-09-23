/*
    BFS: Breadth First Serach or we can say Breqadth First Traversal
*/
#include<bits/stdc++.h>
using namespace std;

void addEdges(vector<pair<int,int>>&edges , unordered_map<int,vector<int>>&adjList){
    for(int i=0;i<edges.size();i++){
        int u = edges[i].first;
        int v = edges[i].second;

        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
}

vector<int> bfsTraversal(unordered_map<int,vector<int>>&adjList, int node){
    vector<bool>visited(node,0);
    vector<int>ans;
    for(int i=0;i<node;i++){
        if(!visited[i]){
            queue<int>q;
            q.push(i);
            visited[i] = 1;
            while(!q.empty()){
                int curr = q.front();
                q.pop();
                ans.push_back(curr);

                for(auto j:adjList[i]){
                    if(!visited[j]){
                        q.push(j);
                        visited[j] = 1;
                    }
                }
            }
        }   
    }
    return ans;
}

void print(unordered_map<int,vector<int>>&adjList){
    for(auto i:adjList){
        cout<<i.first<<" -> ";
        for(auto j:i.second){
            cout<<j<<" ";
        }
        cout<<endl;
    }
}

int main(){
    int node,vertex;
    cin>>node>>vertex;
    vector<pair<int,int>>edges(vertex);
    for(int i=0;i<vertex;i++){
        cin>>edges[i].first>>edges[i].second;
    }
    unordered_map<int,vector<int>>adjList;
    addEdges(edges,adjList);
    print(adjList);
    cout<<"\n\n";
    vector<int>ans;
    ans = bfsTraversal(adjList,node);
    for(auto i:ans){
        cout<<i<<" ";
    }
    return 0;
}