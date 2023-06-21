/*
    Counts Subsets with Sum K
    Problem Statement:  We are given an array ‘ARR’ with N positive integers and an integer K.
                        We need to find the number of subsets whose sum is equal to K.

    Problem Link:   https://www.codingninjas.com/codestudio/problems/number-of-subsets_3952532?source=youtube&campaign=striver_dp_videos
                    https://leetcode.com/problems/subarray-sum-equals-k/

    Refer:  https://takeuforward.org/data-structure/count-subsets-with-sum-k-dp-17/
            https://www.youtube.com/watch?v=ZHyb-A2Mte4&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=18

*/

#include<bits/stdc++.h>
using namespace std;

int countSubsetSumR(vector<int> &arr, int i, int k){
    if(i == 0){
        if(k == 0 && arr[0] == 0)   return 2;
        if(k == 0 || arr[0] == k)   return 1;
        return 0;
    }

    int notPick = countSubsetSumR(arr,i-1,k);
    int Pick = 0;
    if(arr[i] <= k) Pick = countSubsetSumR(arr,i-1,k-arr[i]);

    return notPick+Pick;
}

int countSubsetSumM(vector<int> &arr, int i, int k, vector<vector<int>> &dp){
    if(i == 0){
        if(k == 0 && arr[0] == 0)   return 2;
        if(k == 0 || arr[0] == k)   return 1;
        return 0;
    }
    if(dp[i][k] != -1)  return dp[i][k];
    int notPick = countSubsetSumM(arr,i-1,k,dp);
    int Pick = 0;
    if(arr[i] <= k) Pick = countSubsetSumM(arr,i-1,k-arr[i],dp);

    return dp[i][k] = notPick+Pick;
}

int countSubsetSumT(vector<int> &arr, int n, int k){
    vector<vector<int>> dp(n,vector<int>(k+1,0));
    
    for(int i=0;i<n;i++){
        if(arr[i] == 0) dp[i][0] = 2;
        else    dp[i][0] = 1;
    };
    if(arr[0] <= k && arr[0] != 0)  dp[0][arr[0]] = 1;
    

    for(int i=1;i<n;i++){
        for(int target = 0; target<=k; target++){
            int notPick = dp[i-1][target];
            int Pick = 0;
            if(arr[i] <= target) Pick = dp[i-1][target-arr[i]];

            dp[i][target] = notPick+Pick;
        }
    }
    return dp[n-1][k];
}

int subarraySum(vector<int>& arr, int k) {
        int n = arr.size();
        map<pair<int,int>,int> dp;

    for(int i=0;i<n;i++){
        if(arr[i] == 0) dp[{i,0}] = 2;
        else    dp[{i,0}] = 1;
    };
    if(arr[0] <= k && arr[0] != 0)  dp[{0,arr[0]}] = 1;
    

    for(int i=1;i<n;i++){
        for(int target = 0; target<=k; target++){
            int notPick = dp[{i-1,target}];
            int Pick = 0;
            if(arr[i] <= target) Pick = dp[{i-1,target-arr[i]}];

            dp[{i,target}] = notPick+Pick;
        }
    }
    return dp[{n-1,k}];
    }

int countSubsetSumTS(vector<int> &arr, int n, int k){
    vector<int> prev(k+1,0), curr(k+1,0);
    if(arr[0] == 0 )    prev[0] = curr[0] = 2;
    else    prev[0] = curr[0] = 1;
    //arr[0] != 0 because if arr[0] == 0 it would cahnge the prev [0] value from 2 to 1
    if(arr[0] <= k && arr[0] != 0)  prev[arr[0]] = 1;

    for(int i=1;i<n;i++){
        //Here we start target from 0 as now we are considering the zero target also
        for(int target = 0; target<=k; target++){
            int notPick = prev[target];
            int Pick = 0;
            if(arr[i] <= target) Pick = prev[target-arr[i]];

            curr[target ] = notPick+Pick;
        }
        prev = curr;
    }
    return prev[k];
}

int main(){
    int n,k;
    cin>>n>>k;
    vector<int> arr(n);
    for(auto &i:arr){
        cin>>i;
    }
    vector<vector<int>> dp(n,vector<int>(k+1,-1));
    cout<<subarraySum(arr,k);

    return 0;
}