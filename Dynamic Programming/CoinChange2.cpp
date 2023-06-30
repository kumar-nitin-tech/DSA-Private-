/*
    Problem Statement:  We are given an array Arr with N distinct coins and a target.
                        We have an infinite supply of each coin denomination. We need to find the number of ways we sum up the coin values to give us the target.

    Problem Link:   https://www.codingninjas.com/studio/problems/ways-to-make-coin-change_630471?source=youtube&campaign=striver_dp_videos
                    https://leetcode.com/problems/coin-change-ii/

    Refer:  https://takeuforward.org/data-structure/coin-change-2-dp-22/
            https://www.youtube.com/watch?v=HgyouUi11zk&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=23
    
    Note: cd D:/Coding/C++/DSA/Dynamic Programming/DP Notes/ Coin Change 2
*/

#include<bits/stdc++.h>
using namespace std;

//Recursion
//TC: >>O(2^n) -> Exponential
//SC: O(N) -> Auxiallry Space 
int coinChangeR(vector<int> &arr, int target, int i){
    if(i==0)    return target%arr[i] == 0;

    int notPick = coinChangeR(arr,target,i-1);
    int pick = 0;
    if(arr[i] <= target)    pick = coinChangeR(arr,target-arr[i],i);
    return pick+notPick;
}

//Memomization
//TC: O(n*target)
//SC: O(n*target) + O(n)
int coinChangeM(vector<int> &arr, int target, int i, vector<vector<int>> &dp){
    if(i==0)    return target%arr[i] == 0;
    if(dp[i][target] != -1) return dp[i][target];
    int notPick = coinChangeM(arr,target,i-1,dp);
    int pick = 0;
    if(arr[i] <= target)    pick = coinChangeM(arr,target-arr[i],i,dp);
    return dp[i][target] = pick+notPick;
}

//Tabulation
//TC: O(n*target)
//SC: O(n*target)
int coinChangeT(vector<int> &arr, int target){
    int n = arr.size();
    vector<vector<int>> dp(n,vector<int>(target+1,0));

    for(int t = 0; t<=target;t++){
        dp[0][t] = (t%arr[0] == 0);
    }

    for(int i=1;i<n;i++){
        for(int t=0;t<=target;t++){
            int notPick = dp[i-1][t];
            int pick = 0;
            if(arr[i] <= t) pick = dp[i][t-arr[i]];

            dp[i][t] = notPick+pick;
        }
    }
    return dp[n-1][target];
}

//Space Optimisation
//TC:
//SC:
int coinChangeTS(vector<int> &arr, int target){
    int n = arr.size();
    vector<int> prev(target+1,0), curr(target+1,0); 

    for(int t = 0; t<=target;t++){
        prev[t] = (t%arr[0] == 0);
    }

    for(int i=1;i<n;i++){
        for(int t=0;t<=target;t++){
            int notPick = prev[t];
            int pick = 0;
            if(arr[i] <= t) pick = curr[t-arr[i]];

            curr[t] = notPick+pick;
        }
        prev = curr;
    }
    return prev[target];
}

int main(){
    int n,target;
    cin>>n>>target;
    vector<int> arr(n);
    for(auto &i:arr)    cin>>i;

    vector<vector<int>> dp(n,vector<int> (target+1,-1));

    cout<<coinChangeM(arr,target ,n-1,dp);
    
    return 0;
}