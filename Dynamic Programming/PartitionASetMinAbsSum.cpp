/*
    Partition A Set Into Two Subsets With Minimum Absolute Sum Difference
    Problem Statement:  You are given an integer array nums of 2 * n integers.
                        You need to partition nums into two arrays of length n to minimize the absolute difference of the sums of the arrays.
                        To partition nums, put each element of nums into one of the two arrays.
                        Return the minimum possible absolute difference.

    Problem Link :  https://www.codingninjas.com/codestudio/problems/partition-a-set-into-two-subsets-such-that-the-difference-of-subset-sums-is-minimum_842494?source=youtube&campaign=striver_dp_videos
                    https://leetcode.com/problems/partition-array-into-two-arrays-to-minimize-sum-difference/
    
    Refer:  https://takeuforward.org/data-structure/partition-set-into-2-subsets-with-min-absolute-sum-diff-dp-16/
            https://www.youtube.com/watch?v=GS_OqZb2CWc&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=19
*/
#include<bits/stdc++.h>
using namespace std;

//time complexity and logic is same as SubsetofK Problem
int minSubsetSumDifferenceT(vector<int> &arr, int n){
    int sum = 0;
    for(auto i:arr) sum+=i;

    vector<vector<bool>> dp(n, vector<bool>(sum+1,0));

    for(int i=0;i<n;i++)    dp[i][0] = 1;
    if(arr[0] <= sum)   dp[0][arr[0]] = 1;

    for(int i=1;i<n;i++){
        for(int target = 1;target<=sum;target++){
            bool notTake = dp[i-1][target];
            bool take = 0;
            if(arr[i] <= target)   take = dp[i-1][target-arr[i]];
            dp[i][target] = take || notTake;
        }
    }

    //dp[n-1][col 0..sum]
    int mini = 1e9;
    for(int i=0;i<=sum/2;i++){
        if(dp[n-1][i] == 1){
            mini = min(mini,abs( (sum - i) - i));
        }
    }
    return mini;
}

int minSubsetSumDifferenceTS(vector<int> &arr, int n){
    int sum = 0;
    for(auto i:arr) sum+=i;

    vector<bool> prev(sum,0), temp(sum,0);

    prev[0] = temp[0] = true;
    if(arr[0] <= sum)   prev[arr[0]] = 1;

    for(int i=1;i<n;i++){
        for(int target = 1;target<=sum;target++){
            bool notTake = prev[target];
            bool take = 0;
            if(arr[i] <= target)   take = prev[target-arr[i]];
            temp[target] = take || notTake;
        }
        prev = temp;
    }

    //dp[n-1][col 0..sum]
    int mini = 1e9;
    for(int i=0;i<=sum/2;i++){
        if(prev[i] == 1){
            mini = min(mini,abs( (sum - i) - i));
        }
    }
    return mini;
}

int main(){
    int n;
    cin>>n;
    vector<int> arr(n);
    for(auto &i:arr){
        cin>>i;
    }

    cout<<minSubsetSumDifferenceTS(arr,n);

    return 0;
}