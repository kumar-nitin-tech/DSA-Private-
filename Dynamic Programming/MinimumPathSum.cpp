 /*
 Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right, which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

Detail explanation : https://takeuforward.org/data-structure/minimum-path-sum-in-a-grid-dp-10/
 */

#include<bits/stdc++.h>
using namespace std;

//Recrusion Approach
int minSumPathR(int i, int j, vector<vector<int>> &grid){
    if(i == 0 && j==0){
        return grid[i][j];
    }
    if(i<0 || j<0){
        return 1e9;
    }
    int up = grid[i][j] + minSumPathR(i-1,j,grid);
    int left  = grid[i][j] + minSumPathR(i,j-1, grid);
    return min(up,left);
}

//Memomization as over lapping sub proble  m are there
int minSumPathM(int i, int j,vector<vector<int>> &grid, vector<vector<int>> &dp){
    if(i == 0 && j==0){
        return grid[i][j];
    }
    if(i<0 || j<0){
        return 1e9;
    }
    if(dp[i][j] != -1){
        return dp[i][j];
    }
    int up = grid[i][j] + minSumPathM(i-1,j,grid,dp);
    int left  = grid[i][j] + minSumPathM(i,j-1, grid,dp);
    return dp[i][j] = min(up,left);
}


//Tabulation
int minSumPathT(vector<vector<int>> &grid, vector<vector<int>> &dp){
    int n=grid.size();
    int m = grid[0].size();
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(i == 0 && j==0) dp[i][j] = grid[i][j];
            else{
                int up = grid[i][j], left = grid[i][j];
                if(i>0) up+=dp[i-1][j];
                else up+=1e9;
                if(j>0) left+=dp[i][j-1];
                else left+=1e9;

                dp[i][j] = min(up,left);
            }
        }
    }
    return dp[n-1][m-1];
}

//Space Optimization
int minSumPathTS(vector<vector<int>> &grid){
    int n =grid.size();
    int m = grid[0].size();
    vector<int> prev(m,0);
    for(int i=0;i<n;i++){
        vector<int> temp(m,0);
        for(int j=0;j<m;j++){
            if(i==0 && j==0) temp[j] = grid[i][j];
            else{
                int up = grid[i][j], left = grid[i][j];
                if(i>0) up+=prev[j];
                else up+=1e9;
                if(j>0) left+=temp[j-1];
                else left+=1e9;

                temp[j] = min(up,left);
            }
        }
        prev = temp;
    }
    return prev[m-1];
}


int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> grid(n, vector<int>(m));
    for(auto &i: grid){
        for(auto &j:i){
            cin>>j;
        }
    }
    vector<vector<int>> dp(n,vector<int>(m,-1));
    cout<<minSumPathTS(grid);
    return 0;
}