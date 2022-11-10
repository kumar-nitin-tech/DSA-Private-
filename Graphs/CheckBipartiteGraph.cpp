//We have given a Graph we have to check whether it if bipartite grpah or not
//Bipartite graph : A graph is said to be bipartite if we can color it the graph with 2 colors such that no adjacnet nodes are of same color

#include<bits/stdc++.h>
using namespace std;

class graph{
    public:
    unordered_map<int,vector<int>>adjList;
    void addEdges(int u, int v){
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
};


//BFS Traversal
//Time Commplexity: O(n)
//Space Complexity: O(n)
bool checkBipartiteBFS(unordered_map<int,vector<int>>&adjList, int start ,vector<int>&color){
    queue<int>q;
    q.push(start);
    color[start] = 0;
    while(!q.empty()){
        int front = q.front();
        q.pop();
        for(auto it:adjList[front]){
            //if node is not colored than color it with opposite color of its adjacent node
            if(color[it] == -1){
                color[it] = !color[front];
                q.push(it);
            }
            //if colored node is of same color of previous node than it violate the bipartite condition henc retunr false
            else if(color[front] == color[it]){
                return false;
            }
        }
    }
    //if after all senarios the loop does not return false then by elimination method the graph is bipartite hence return true
    return true;
}

//DFS Traversal
bool checkBipartiteDFS(unordered_map<int,vector<int>>&adjList, int start, int opp,vector<int>&color){
    color[start] = opp;
    for(auto it:adjList[start]){
        if(color[it] == -1){
            if(checkBipartiteDFS(adjList,it,!opp,color) == false){
                return false;
            }
        }
        else if(color[it] == color[start]){
            return false;
        }
    }
    return true;
}

bool isBipartite(unordered_map<int,vector<int>>&adjList, int nodes){
    vector<int>color(nodes,-1);
    for(int i=0;i<nodes;i++){
        if(color[i] ==-1){
            // return checkBipartite(adjList,i,nodes,color);
            if(checkBipartiteDFS(adjList,i,0,color) == false){
                return false;
            }
        }
    }
    return true;
}

int main(){
    int nodes, vertex;
    cin>>nodes>>vertex;
    vector<pair<int,int>>edges(vertex);
    for(auto &i:edges){
        cin>>i.first>>i.second;
    }

    graph gph;
    for(auto i:edges){
        gph.addEdges(i.first,i.second);
    }

    cout<<isBipartite(gph.adjList,nodes);

    return 0;
}