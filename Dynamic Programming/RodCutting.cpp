/*
    Rod Cutting Problem

    Problem Statement:  We are given a rod of size ‘N’. It can be cut into pieces. 
                        Each length of a piece has a particular price given by the price array.
                        Our task is to find the maximum revenue that can be generated by selling the rod after cutting (if required) into pieces.

    Problem Link:   https://www.codingninjas.com/studio/problems/rod-cutting-problem_800284?source=youtube&campaign=striver_dp_videos
                    https://practice.geeksforgeeks.org/problems/rod-cutting0840/1

    Refer:  https://takeuforward.org/data-structure/rod-cutting-problem-dp-24/
            https://www.youtube.com/watch?v=mO8XpGoJwuo&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=26
*/

#include<bits/stdc++.h>
using namespace std;

//Recursion
//TC: O(2^n)
//SC: O(n) Auxiallary Space 
int cutRodR(int n, int i, vector<int> &prices){
    //base case
    if(i==0) return n*prices[0];

    int notTake = 0 + cutRodR(n,i-1,prices);
    int take = INT_MIN;
    int rodLength = i+1;
    if(rodLength<=n)    take = prices[i] + cutRodR(n-rodLength,i,prices);
    return max(notTake,take);
}

//Memomization
//TC: O(n^2)
//SC: O(n^2) + O(n)
int cutRodM(int n, int i,vector<int> &prices, vector<vector<int>> &dp){
        //base case
    if(i==0) return n*prices[0];
    
    if(dp[i][n] != -1)  return dp[i][n];
    int notTake = 0 + cutRodM(n,i-1,prices,dp);
    int take = INT_MIN;
    int rodLength = i+1;
    if(rodLength<=n)    take = prices[i] + cutRodM(n-rodLength,i,prices,dp);
    return dp[i][n] = max(notTake,take);
}

//Tabulation
//TC: O(n^2)
//SC: O(n^2)
int cutRodT(int n, vector<int> &prices){
    vector<vector<int>> dp(n,vector<int>(n+1,0));

    //base case:
    for(int i=0;i<=n;i++){
        dp[0][i] = i*prices[0];
    }

    for(int ind=1;ind<n;ind++){
        for(int N=0;N<=n;N++){
            int notTake = 0 + dp[ind-1][N];
            int take = INT_MIN;
            if(ind+1<=N)    take = prices[ind] + dp[ind][N-(ind+1)];
            dp[ind][N] = max(notTake,take);
        }
    }
    return dp[n-1][n];
}

//Sapce Optimisation
//TC: O(n^2)
//SC: O(n)
int cutRodTS(int n, vector<int> &prices){
    vector<int> prev(n+1,0);
    //base case:
    for(int i=0;i<=n;i++){
        prev[i] = i*prices[0];
    }

    for(int ind=1;ind<n;ind++){
        for(int N=0;N<=n;N++){
            int notTake = 0 + prev[N];
            int take = INT_MIN;
            if(ind+1<=N)    take = prices[ind] + prev[N-(ind+1)];
            prev[N] = max(notTake,take);
        }
    }
    return prev[n];
} 


int main(){
    int n;
    cin>>n;
    vector<int> prices(n);
    for(auto &i:prices) cin>>i;
    vector<vector<int>> dp(n,vector<int>(n+1,-1));
    cout<<cutRodTS(n,prices);
    return 0;
}