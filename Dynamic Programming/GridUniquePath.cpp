/*
Given two values M and N, which represent a matrix[M][N]. We need to find the total unique paths from the top-left cell (matrix[0][0])
to the rightmost cell (matrix[M-1][N-1]).
*/

#include<bits/stdc++.h>
using namespace std;

//recursive approach
//TC: O(2^n*m)
//SC: O(n-1 + m-1)
int UniquePathRecursive(int i, int j){
    if(i == 0 && j==0){
        return 1;
    }
    if(i<0 || j<0){
        return 0;
    }

    int upper = UniquePathRecursive(i-1,j);
    int left = UniquePathRecursive(i,j-1);
    return left + upper;
}

//Oprimized to Memomization
//TC: O(n*m)
//SC: O(n-1 + m-1) + O(n*m)
int UniquePathMemo(int i, int j, vector<vector<int>> &dp){
    if(i == 0 && j==0){
        return 1;
    }
    if(i<0 || j<0){
        return 0;
    }

    if(dp[i][j] != -1){
        return dp[i][j];
    }

    int upper = UniquePathMemo(i-1,j,dp);
    int left = UniquePathMemo(i,j-1,dp);
    return dp[i][j] = left + upper;
}

//Tabulation
//TC: O(n*m)
//SC: O(n*m)

int UniquePathTab(int m, int n, vector<vector<int>> &dp){
    for(int i=0;i<m;i++){
        for(int j = 0;j<n;j++){
            if(i==0 && j==0){
                dp[i][j] = 1;
            }
            else{
                int up =0, left = 0;
                if(i>0) up = dp[i-1][j];
                if(j>0) left = dp[i][j-1];

                dp[i][j] = up+left;
            }
        }
    }
    return dp[m-1][n-1];
}

//Space Optimised
//TC: O(n*m)
//TC: O(n)
int UniquePathSpace(int m , int n){
    vector<int> prevRow(n,0);
    for(int i=0;i<m;i++){
        vector<int> row(n,0);
        for(int j=0;j<n;j++){
            if(i==0 && j==0){
                row[j] = 1;
            }
            else{
                int up =0, left = 0;
                if(i>0) up = prevRow[j];
                if(j>0) left = row[j-1];

                row[j]= up+left;
            }
        }
        prevRow = row;
    }
    return prevRow[n-1];
}


//Most Optimal Solution
//TC: O(m-1) or O(n-1)
//SC: O(1)
int UniquePathOptimalCombination(int m, int n){
    int N = m+n-2;
    int r = m-1;
    int ans = 1;
    for(int i=1;i<=r;i++){
        ans = ans*(N-r+i)/i;
    }
    return ans;
}


int main(){
    int n,m;
    cin>>m>>n;
    vector<vector<int>> dp(m,vector<int> (n,-1));
    cout<<UniquePathOptimalCombination(m,n);
    return 0;
}