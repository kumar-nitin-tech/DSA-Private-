/*
    Count Partitions With Given Difference

    Problem Statement:  We are given an array ‘ARR’ with N positive integers and an integer D.
                        We need to count the number of ways we can partition the given array into two subsets, S1 and S2 such that S1 – S2 = D
                        and S1 is always greater than or equal to S2.

    Problem Link:   https://www.codingninjas.com/codestudio/problems/partitions-with-given-difference_3751628?source=youtube&campaign=striver_dp_videos

    Refer:  https://takeuforward.org/data-structure/count-partitions-with-given-difference-dp-18/
            https://www.youtube.com/watch?v=zoilQD1kYSg&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=19

*/

#include<bits/stdc++.h>
using namespace std;

//Recursion
//TC: O(2^n)
//SC: O(n)
int countPartitionR(int i, int k, vector<int> &arr){
     if(i == 0){
        if(k == 0 && arr[0] == 0)   return 2;
        if(k == 0 || arr[0] == k)   return 1;
        return 0;
    }

    int notPick = countPartitionR(i-1,k,arr);
    int Pick = 0;
    if(arr[i] <= k) Pick = countPartitionR(i-1,k-arr[i],arr);

    return notPick+Pick;
}

//Memomization
//TC:O(n*k)
//SC:O(n*k) + O(n)
int countPartitionM(vector<int> &arr, int i, int k, vector<vector<int>> &dp){
    if(i == 0){
        if(k == 0 && arr[0] == 0)   return 2;
        if(k == 0 || arr[0] == k)   return 1;
        return 0;
    }
    if(dp[i][k] != -1)  return dp[i][k];
    int notPick = countPartitionM(arr,i-1,k,dp);
    int Pick = 0;
    if(arr[i] <= k) Pick = countPartitionM(arr,i-1,k-arr[i],dp);

    return dp[i][k] = notPick+Pick;
}

//Tabulation
//TC: O(n*k)
//SC:O(n*k)
int countPartitionT(int n, int k, vector<int> &arr){
    vector<vector<int>> dp(n,vector<int>(k+1,0));
    if(arr[0] == 0) dp[0][0] = 2;
    else dp[0][0] = 1;
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

//Space Optimized
//TC: O(n*k)
//SC:O(k)
int countPartitionTS(int n, int k, vector<int> &arr){
    vector<int> prev(k+1,0), curr(k+1,0);
    if(arr[0] == 0 )    prev[0] = 2;
    else    prev[0] = 1;
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
    int n,d;
    cin>>n>>d;
    vector<int> arr(n);
    for(auto &i:arr){
        cin>>i;
    }

    int totalSum =0;
    for(auto i:arr){
        totalSum += i;
    }

    if(totalSum-d >=0 && (totalSum-d)%2 == 0){
        cout<<countPartitionTS(n,(totalSum-d)/2,arr);
    }
    else    cout<<0;
    return 0;
}