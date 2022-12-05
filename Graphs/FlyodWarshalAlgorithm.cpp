#include<bits/stdc++.h>
using namespace std;

//Update the given matrix 
void flyodAlgoShortestPath(vector<vector<int>> &adjMatrix){
    int n = adjMatrix.size();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(adjMatrix[i][j] == -1){
                adjMatrix[i][j] = 1e9;
            }
            if(i==j){
                adjMatrix[i][j] = 0;
            }
        }
    }

    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                adjMatrix[i][j] = min(adjMatrix[i][j] , adjMatrix[i][k] + adjMatrix[k][j]);
            }
        }
    }

    //negative cycle
    for(int i=0;i<n;i++){
        if(adjMatrix[i][i] < 0){
            return;
        }
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(adjMatrix[i][j] == 1e9){
                adjMatrix[i][j] = -1;
            }
        }
    }
}

int main(){
    int nodes;
    cin>>nodes;
    vector<vector<int>> adjMatrix(nodes,vector<int>(nodes));
    for(int i=0;i<nodes;i++){
        for(int j=0;j<nodes;j++){
            cin>>adjMatrix[i][j];
        }
    }
    flyodAlgoShortestPath(adjMatrix);
    for(int i=0;i<nodes;i++){
        for(int j=0;j<nodes;j++){
            cout<<adjMatrix[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}