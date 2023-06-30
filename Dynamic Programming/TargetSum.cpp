/*
    Target Sum
    Problem Statement:  We are given an array ‘ARR’ of size ‘N’ and a number ‘Target’. 
                        Our task is to build an expression from the given array where we can place a ‘+’ or ‘-’ sign in front of an integer.
                        We want to place a sign in front of every integer of the array and get our required target. 
                        We need to count the number of ways in which we can achieve our required target.

    Problem Link:   https://www.codingninjas.com/studio/problems/target-sum_4127362?source=youtube&campaign=striver_dp_videos

    Refer:  https://takeuforward.org/data-structure/target-sum-dp-21/
            https://www.youtube.com/watch?v=b3GD8263-PQ&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=22
*/

#include<bits/stdc++.h>
using namespace std;

//Recursion
//TC: >>O(2^n) -> Exponential
//SC: O(N) -> Auxiallry Space 
int targetSumR(vector<int> &arr, int k, int i){
    if(i==0){
        if(k==0 && arr[i] == 0) return 2;
        if(k==0 || arr[i] == k) return 1;
        return 0;
    }

   int notPick = targetSumR(arr,k,i-1);
   int pick = 0;
   if(arr[i] <= k)  pick = targetSumR(arr,k-arr[i],i-1);
   return pick+notPick; 
}

//Memomization
//TC: O(n*k)
//SC: O(n*k) + O(n)
int targetSumM(vector<int> &arr, int k, int i, vector<vector<int>> &dp){
    if(i==0){
        if(k==0 && arr[i] == 0) return 2;
        if(k==0 || arr[i] == k) return 1;
        return 0;
    }
    if(dp[i][k] != -1)  return dp[i][k];
   int notPick = targetSumM(arr,k,i-1,dp);
   int pick = 0;
   if(arr[i] <= k)  pick = targetSumM(arr,k-arr[i],i-1,dp);
   return dp[i][k] = pick+notPick; 
}

//Tabulation
//TC: O(n*k)
//SC: O(n*k)
int targetSumT(vector<int> &arr, int k){
    int n = arr.size();
    vector<vector<int>> dp(n,vector<int> (k+1,0));
    if(arr[0] == 0) dp[0][0] = 2;
    else dp[0][0] = 1;

    if(arr[0] <= k && arr[0] != 0)  dp[0][arr[0]] = 1;
    
    for(int i=1;i<n;i++){
        for(int t=0;t<=k;t++){
            int notPick = dp[i-1][t];
            int pick = 0;
            if(arr[i] <= t)  pick = dp[i-1][t-arr[i]];
            dp[i][t] = pick+notPick; 
        }
    }
    
    return dp[n-1][k];
}

//Space Optimisation
//TC:
//SC:
int targetSumTS(vector<int> &arr, int k){
    int n = arr.size();
    vector<int> prev(k+1,0), curr(k+1,0);

    //base case
    if(arr[0] == 0) prev[0] = 2;
    else prev[0] = 1;

    if(arr[0] <= k && arr[0] != 0)  prev[arr[0]] = 1;
    //nested loop
    for(int i=1;i<n;i++){
        for(int target = 0; target<=k; target++){
           int notPick = prev[target];
            int pick = 0;
            if(arr[i] <= target)  pick = prev[target-arr[i]];
            curr[target] = pick+notPick; 
        }
        prev = curr;
    }

    return prev[k];
}

int main(){
    int n,k;
    cin>>n>>k;
    vector<int> arr(n);
    for(auto &i:arr)    cin>>i;

    vector<vector<int>> dp(n,vector<int> (k+1,-1));
    int totalSum = 0;
    for(auto i:arr) totalSum+=i;

    if(totalSum-k >= 0 && (totalSum-k) % 2 == 0){
        cout<<targetSumTS(arr,(totalSum-k)/2);
    }
    else cout<<-1;
    return 0;
}