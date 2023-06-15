/*
You have been given an N*M matrix filled with integer numbers, find the maximum sum that can be obtained 
from a path starting from any cell in the first row to any cell in the last row. From a cell in a row, 
you can move to another cell directly below that row, or diagonally below left or right. So from a 
particular cell (row, col), we can move in three directions i.e.
Down: (row+1, col)
Down Left Diagonal
Down Right Diagonal
https://takeuforward.org/data-structure/minimum-maximum-falling-path-sum-dp-12/
*/

#include<bits/stdc++.h>
using namespace std;

//Recursive Approach
//TC: O(3^n)
int getMaxPathSumR(int i, int j, vector<vector<int>> &matrix, int m){
    
    //It should checkd first because if at i ==0 j is <0 or >=m it would give garbage value
    if(j>=m || j<0)
        return -1e9;
    
    if(i==0){
        return matrix[i][j];
    }

    int up = matrix[i][j] + getMaxPathSumR(i-1,j,matrix,m);
    int leftDiagonal = matrix[i][j] +getMaxPathSumR(i-1,j-1,matrix,m);
    int rightDiagonal = matrix[i][j] + getMaxPathSumR(i-1,j+1,matrix,m);
    return max(up,max(leftDiagonal,rightDiagonal));
}

//Memomization
//TC: O(n*m)
int getMaxPathSumM(int i, int j, int m, vector<vector<int>> &matrix, vector<vector<int>> &dp){
    if(j>=m || j<0)
        return -1e9;
    
    if(i==0){
        return matrix[i][j];
    }

    if(dp[i][j] != -1) return dp[i][j];

    int up = matrix[i][j] + getMaxPathSumR(i-1,j,matrix,m);
    int leftDiagonal = matrix[i][j] +getMaxPathSumR(i-1,j-1,matrix,m);
    int rightDiagonal = matrix[i][j] + getMaxPathSumR(i-1,j+1,matrix,m);
    return dp[i][j] = max(up,max(leftDiagonal,rightDiagonal));
}

//Tabulation
//TC: O(n*m)
int getMaxPathSumT(vector<vector<int>> &matrix, vector<vector<int>> &dp){ 
    int n=matrix.size();
    int m=matrix[0].size();
    for(int j=0;j<m;j++){
        dp[0][j] = matrix[0][j];
    }
    for(int i=1;i<n;i++){
        for(int j=0;j<m;j++){
            int up = matrix[i][j] + dp[i-1][j];

            int leftDiagonal = matrix[i][j];
            if(j-1>=0)   leftDiagonal += dp[i-1][j-1];
            else leftDiagonal += -1e8;

            int rightDiagonal = matrix[i][j];
            if(j+1<m)   rightDiagonal += dp[i-1][j+1];
            else rightDiagonal += -1e8;

            dp[i][j] = max(up,max(leftDiagonal,rightDiagonal));
        }
    }
    int maxAns = INT_MIN;
    for(int i=0;i<m;i++){
        maxAns = max(maxAns,dp[n-1][i]);
    }
    return maxAns;
}

//Space Optimisation
//TC: O(n*m)
int getMaxPathSumTS(vector<vector<int>> &matrix){
     int n=matrix.size();
    int m=matrix[0].size();
    vector<int> prev(m,-1);
    for(int j=0;j<m;j++){
        prev[j] = matrix[0][j];
    }
    for(int i=1;i<n;i++){
        vector<int> temp(m,-1);
        for(int j=0;j<m;j++){
            int up = matrix[i][j] + prev[j];

            int leftDiagonal = matrix[i][j];
            if(j-1>=0)   leftDiagonal += prev[j-1];
            else leftDiagonal += -1e8;

            int rightDiagonal = matrix[i][j];
            if(j+1<m)   rightDiagonal += prev[j+1];
            else rightDiagonal += -1e8;

            temp[j] = max(up,max(leftDiagonal,rightDiagonal));
        }
        prev = temp;
    }
    int maxAns = INT_MIN;
    for(int i=0;i<m;i++){
        maxAns = max(maxAns,prev[i]);
    }
    return maxAns;
}

int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> matrix(n,vector<int>(m));
    for(auto &i:matrix){
        for(auto &j:i){
            cin>>j;
        }
    }
    // int maxAns = INT_MIN;
    vector<vector<int>> dp(n,vector<int> (m,-1));
    // for(int i=0;i<m;i++){
    //     int temp = getMaxPathSumT(matrix,dp);
    //     maxAns = max(maxAns,temp);
    // }
    cout<<getMaxPathSumTS(matrix);
    
    return 0;
}