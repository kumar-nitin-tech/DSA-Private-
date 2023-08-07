/*
    Burst Balloons

    Problem Statement:  You are given n balloons, indexed from 0 to n - 1. Each balloon is painted with a number on it represented by an 
                        array nums. You are asked to burst all the balloons.
                        If you burst the ith balloon, you will get nums[i - 1] * nums[i] * nums[i + 1] coins. If i - 1 or i + 1 goes out of bounds of the array, then treat it as if there is a balloon with a 1 painted on it.
                        Return the maximum coins you can collect by bursting the balloons wisely.

    Problem Link:   https://leetcode.com/problems/burst-balloons/
                    https://www.codingninjas.com/studio/problems/burst-balloons_628471

    Refer:  https://takeuforward.org/data-structure/burst-balloons-partition-dp-dp-51/
            https://www.youtube.com/watch?v=Yz4LlDSlkns&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=52
*/

#include<bits/stdc++.h>
using namespace std;

//Recursive 
//Time Complexity:
//Space Complexity:
int maximumCoinR(int i, int j, vector<int> &arr){
    if(i>j) return 0;

    int maxi = INT_MIN;
    for(int k=i; k<=j; k++){
        int cost = arr[i-1] * arr[k] * arr[j+1] + maximumCoinR(i,k-1,arr) + maximumCoinR(k+1,j,arr);
        maxi = max(maxi, cost);
    }
    return maxi;
}

//Recursive 
//Time Complexity:
//Space Complexity:
int maximumCoinM(int i, int j, vector<int> &arr, vector<vector<int>> &dp){
    if(i>j) return 0;

    if(dp[i][j] != -1)  return dp[i][j];

    int maxi = INT_MIN;
    for(int k=i; k<=j; k++){
        int cost = arr[i-1] * arr[k] * arr[j+1] + maximumCoinM(i,k-1,arr,dp) + maximumCoinM(k+1,j,arr,dp);
        maxi = max(maxi, cost);
    }
    return dp[i][j] = maxi;
}

//Tabulation
//Time Complexity:
//Space Complexity:
int maximumCoinT(vector<int> &arr, int n){
    vector<vector<int>> dp(n+1,vector<int> (n+1,0));

    for(int i=n; i>=1; i--){
        for(int j=1; j<=n; j++){
            if(i>j) continue;

            int maxi = INT_MIN;
            for(int k=i; k<=j; k++){
                int cost = arr[i-1] * arr[k] * arr[j+1] + dp[i][k-1] + dp[k+1][j];
                maxi = max(maxi, cost);
            }
            dp[i][j] = maxi;
        }
    }
    return dp[1][n];
}

int main(){
    int n;
    cin>>n;
    vector<int> arr(n);
    for(auto &i:arr)    cin>>i;
    arr.push_back(1);
    arr.insert(arr.begin(), 1);
    vector<vector<int>> dp(n+1,vector<int>(n+1,-1));
    cout<<maximumCoinT(arr,n);
    return 0;
}