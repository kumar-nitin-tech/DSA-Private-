/*
    Cherry Pickup II
    
    Problem Description: 
        
    We are given an ‘N*M’ matrix. Every cell of the matrix has some chocolates on it, mat[i][j] gives us the number of chocolates.
    We have two friends ‘Alice’ and ‘Bob’. initially, Alice is standing on the cell(0,0) and Bob is standing on the cell(0, M-1). 
    Both of them can move only to the cells below them in these three directions: to the bottom cell (↓), to the bottom-right cell(↘), or to the bottom-left cell(↙).
    When Alica and Bob visit a cell, they take all the chocolates from that cell with them. 
    It can happen that they visit the same cell, in that case, the chocolates need to be considered only once.
    They cannot go out of the boundary of the given matrix, we need to return the maximum number of chocolates that Bob and Alice can together collect.

    refer : https://takeuforward.org/data-structure/3-d-dp-ninja-and-his-friends-dp-13/
            https://www.youtube.com/watch?v=QGfn7JeXK54&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=16
*/

#include<bits/stdc++.h>
using namespace std;

//Recursion
int maximumCherryR(int i,int j1, int j2,int m,int n, vector<vector<int>> &grid){
    //Out of bound base case
    if(j1<0 || j1>=m || j2<0 || j2>=m)  return -1e9;

    //destination base case
    if(i == n-1){
        if(j1==j2)  return grid[i][j1];
        else    return grid[i][j1]+grid[i][j2];
    }

    //Explore all paths
    int maxi = -1e9;
    //For every one path of alice there are 3 paths for bob
    for(int a=-1;a<= +1;a++){
        for(int b=-1;b<= +1;b++){
            int value = 0;
            if(j1==j2){
                value = grid[i][j1];
            }
            else value = grid[i][j1]+ grid[i][j2];

            value += maximumCherryR(i+1,j1+a,j2+b,m,n, grid);
            maxi = max(maxi,value);
        }
    }
    return maxi;
}

//Memomization
//Time Complexity: O(N*M*M) * 9
//Space Complexity: O(N*M*M) + O(N)
int maximumCherryM(int i,int j1, int j2,int m,int n, vector<vector<int>> &grid, vector<vector<vector<int>>> &dp){
    //Out of bound base case
    if(j1<0 || j1>=m || j2<0 || j2>=m)  return -1e9;

    //destination base case
    if(i == n-1){
        if(j1==j2)  return grid[i][j1];
        else    return grid[i][j1]+grid[i][j2];
    }
    if(dp[i][j1][j2] != -1) return dp[i][j1][j2];

    //Explore all paths
    int maxi = -1e9;
    //For every one path of alice there are 3 paths for bob
    for(int a=-1;a<= +1;a++){
        for(int b=-1;b<= +1;b++){
            int value = 0;
            if(j1==j2){
                value = grid[i][j1];
            }
            else value = grid[i][j1]+ grid[i][j2];

            value += maximumCherryM(i+1,j1+a,j2+b,m,n, grid,dp);
            maxi = max(maxi,value);
        }
    }
    return dp[i][j1][j2] = maxi;
}

//Tabulation
//Time Complexity: O(N*M*M)*9
//Space Complexity: O(N*M*M)
int maximumCherryT(int n,int m, vector<vector<int>> &grid, vector<vector<vector<int>>> &dp){
    //Base case
    for(int j1=0; j1<m; j1++){
        for(int j2=0; j2<m; j2++){
            
            if(j1==j2) 
                dp[n-1][j1][j2] = grid[n-1][j1];
            
            else
                dp[n-1][j1][j2] = grid[n-1][j1] + grid[n-1][j2];
        }
    }
    
    for(int i=n-2;i>=0;i--){
        for(int j1=0;j1<m;j1++){
            for(int j2=0;j2<m;j2++){

                int maxi = INT_MIN;
                //For every one path of alice there are 3 paths for bob

                for(int a=-1;a<= +1;a++){
                    for(int b=-1;b<= +1;b++){

                        int value = 0;

                        if(j1==j2){
                            value = grid[i][j1];
                        }
                        
                        else 
                            value = grid[i][j1]+ grid[i][j2];
                        
                        if((j1+a<0 || j1+a>=m) || j2+b<0 || j2+b>=m)
                            value += -1e9;    
                        
                        else
                            value += dp[i+1][j1+a][j2+b];
                        
                        maxi = max(maxi,value);
                    }
                }
                dp[i][j1][j2] = maxi;
            }
        }
    }
    return dp[0][0][m-1];
}

//Space Optimisation
//Time Complexity: O(N*M*M)*9
//Space Complexity: O(M*M)
int maximumCherryTS(int n, int m, vector<vector<int>> &grid){
    vector<vector<int>> prev(m,vector<int>(m));
    for(int j1=0; j1<m; j1++){
        for(int j2=0; j2<m; j2++){
            
            if(j1==j2) 
                prev[j1][j2] = grid[n-1][j1];
            
            else
               prev[j1][j2] = grid[n-1][j1] + grid[n-1][j2];
        }
    }
    for(int i=n-2;i>=0;i--){
        vector<vector<int>> temp(m,vector<int>(m));
        for(int j1=0;j1<m;j1++){
            for(int j2=0;j2<m;j2++){
                
                int maxi = INT_MIN;
                //For every one path of alice there are 3 paths for bob

                for(int a=-1;a<= +1;a++){
                    for(int b=-1;b<= +1;b++){

                        int value = 0;

                        if(j1==j2){
                            value = grid[i][j1];
                        }
                        
                        else 
                            value = grid[i][j1]+ grid[i][j2];
                        
                        if((j1+a<0 || j1+a>=m) || j2+b<0 || j2+b>=m)
                            value += -1e9;    
                        
                        else
                            value += prev[j1+a][j2+b];
                        
                        maxi = max(maxi,value);
                    }
                }
                temp[j1][j2] = maxi;
            }
        }
        prev = temp;
    }
    return prev[0][m-1];
}


int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> grid(n,vector<int>(m));
    for(auto &i:grid){
        for(auto &j:i){
            cin>>j;
        }
    }

    vector<vector<vector<int>>> dp(n,vector<vector<int>>(m,vector<int>(m,0)));

    cout<<maximumCherryTS(n,m,grid);
    return 0;
}