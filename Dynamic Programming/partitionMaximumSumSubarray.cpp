/*
    Partition Array for Maximum Sum

    Problem Statement:  Given an integer array arr, partition the array into (contiguous) subarrays of length at most k. After 
                        partitioning, each subarray has their values changed to become the maximum value of that subarray.
                        Return the largest sum of the given array after partitioning.

    Problem Link:   https://leetcode.com/problems/partition-array-for-maximum-sum/
                    https://www.codingninjas.com/studio/problems/partition-array-for-maximum-sum_3755255

    Refer:  https://takeuforward.org/data-structure/partition-array-for-maximum-sum-front-partition-dp-54/
            https://www.youtube.com/watch?v=PhWWJmaKfMc&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=58
*/

#include<bits/stdc++.h>
using namespace std;

//Recursion
//Time Complexity: Exponential 
//Space Complexity: O(n)
int maxSumR(int i, int k, int n, vector<int> &arr){
    //base case
    if(i==n)    return 0;

    //partition
    int len = 0, maxi = INT_MIN, maxSum = INT_MIN;
    for(int j=i; j<min(n, i+k); j++){
        len++;
        maxi = max(maxi, arr[j]);
        int sum = len*maxi + maxSumR(j+1,k,n,arr);
        maxSum = max(maxSum,sum);
    }
    return maxSum;
}

//Memomization
//Time Complexity:  O(n*k)
//Space Complexity: O(n) + O(n)
int maxSumM(int i, int k, int n, vector<int> &arr, vector<int> &dp){
    //base case
    if(i==n)    return 0;

    //dp check
    if(dp[i] != -1)  return dp[i];

    //partition
    int len = 0, maxi = INT_MIN, maxSum = INT_MIN;
    for(int j=i; j<min(n, i+k); j++){
        len++;
        maxi = max(maxi, arr[j]);
        int sum = len*maxi + maxSumM(j+1,k,n,arr,dp);
        maxSum = max(maxSum,sum);
    }
    return dp[i] = maxSum;
}

//Tabulation
//Time Complexity: O(n*k)
//Space Complexity: O(n)
int maxSumT(int k, vector<int> &arr){
    int n = arr.size();
    vector<int> dp(n+1,0);

    for(int i=n-1; i>=0; i--){
        int len = 0, maxi = INT_MIN, maxSum = INT_MIN;
        for(int j=i; j<min(n, i+k); j++){
            len++;
            maxi = max(maxi, arr[j]);
            int sum = len*maxi + dp[j+1];
            maxSum = max(maxSum,sum);
        }
        dp[i] = maxSum;
    }
    return dp[0];
}

int main(){
    int n,k;
    cin>>n>>k;
    vector<int> arr(n);
    for(auto &i:arr)    cin>>i;
    vector<int> dp(n,-1);
    cout<<maxSumT(k,arr);
    return 0;
}