/*
    Matrix Chain Multiplication | Partition DP

    Problem Statement:  Given a chain of matrices A1,…, An denoted by an array of size n+1, find out the minimum number of operations to 
                        multiply these n matrices.

    Problem Link:   https://www.codingninjas.com/studio/problems/matrix-chain-multiplication_624880

    Refer:  https://takeuforward.org/dynamic-programming/matrix-chain-multiplication-dp-48/
            https://www.youtube.com/watch?v=vRVfmbCFW7Y&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=51

*/

#include<bits/stdc++.h>
using namespace std;

//Recursion Approach
//Time Complexity:  O(2^n) -> Exponential 
//Space Complexity: O(n) -> auxillary space
int mcmOperationR(int i, int j, vector<int> &arr){
    //base case:
    if(i == j)  return 0;

    int mini = 1e9;
    //For partition we run a loop
    for(int k=i; k<j; k++){
        int operation = arr[i-1] * arr[k] * arr[j] + mcmOperationR(i,k, arr) + mcmOperationR(k+1, j, arr);
        mini = min(mini, operation); 
    }
    return mini;
}

//Memomization
//Time Complexity:  O(n^3)
//Space Complexity: O(n^2) + O(n)
int mcmOperationM(int i, int j, vector<int> &arr, vector<vector<int>> &dp){
    if(i == j)  return 0;

    if(dp[i][j] != -1)  return dp[i][j];

    int mini = 1e9;

    for(int k=i; k<j; k++){
        int op = arr[i-1] * arr[k] * arr[j] + mcmOperationM(i,k,arr,dp) + mcmOperationM(k+1,j,arr,dp);
        mini = min(mini, op);
    }
    return dp[i][j] = mini;
}

//Tablulation
//Time Complexity:
//Space Complexity:
int mcmOperationT(vector<int> &arr){
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int> (n,0));
    //base case:
    //if( i == j) return 0;

    // for(int i=0; i<arr.size(); i++){
    //     dp[i][i] = 0;
    // }
    
    //nested loop
    for(int i=n-1; i>=1; i--){
        for(int j=i+1; j<n; j++){
            int mini = 1e9;
            for(int k=i; k<j; k++){
                int op = arr[i-1] * arr[k] * arr[j] + dp[i][k] + dp[k+1][j];
                mini = min(mini, op);
            }
            dp[i][j] = mini;
        }
    }
    return dp[1][n-1];
}

int main(){
    int n;
    cin>>n;
    vector<int> arr(n);
    for(auto &i:arr)    cin>>i;
    vector<vector<int>> dp(n, vector<int> (n, -1));
    cout<<mcmOperationT(arr);
    return 0;
}