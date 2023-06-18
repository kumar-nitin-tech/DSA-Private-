/*
    Partition Equal Subset Sum
    Problem Statement : We are given an array ‘ARR’ with N positive integers.
                        We need to find if we can partition the array into two subsets such that the sum of elements of each subset is equal to the other.

    Refer : https://takeuforward.org/data-structure/partition-equal-subset-sum-dp-15/
            https://www.youtube.com/watch?v=7win3dcgo3k&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=17
    
    Problem Link: https://www.codingninjas.com/codestudio/problems/partition-equal-subset-sum_892980?source=youtube&campaign=striver_dp_videos
                  https://leetcode.com/problems/partition-equal-subset-sum/
*/

#include<bits/stdc++.h>
using namespace std;

//Same as target subset sum
//TC: O(2^n) 
//SC: O(n) :auxillary stack space
bool canPartitionR(vector<int> &arr, int i, int k){
    if(k == 0)  return true;
    if(i == 0)  return arr[i] == k;

    bool notTake = canPartitionR(arr,i-1,k);
    bool take = false;
    if(arr[i] <= k) take = canPartitionR(arr,i-1,k-arr[i]);
    return take || notTake;
}

//TC: O(n*k) 
//SC: O(n*k)+O(n) :auxillary stack space
bool canPartitionM(vector<int> &arr, int k, int i, vector<vector<int>> &dp){
if(k == 0)  return true;
    if(i == 0)  return k == arr[i];

    if(dp[i][k] != -1)  return dp[i][k];
//not Taking the element 
    bool notTake = canPartitionM(arr,k,i-1,dp); 

//Taking the element 
    bool take = false;
    if(k >= arr[i]) take = canPartitionM(arr, k-arr[i],i-1,dp);

    return dp[i][k] = (take || notTake);
}

//TC: O(n*k) 
//SC: O(n*k)
bool canPartitionT(vector<int> &arr, int n, int k){
    //dp[n][k]
    vector<vector<bool>> dp(n,vector<bool>(k+1,0));

    //Base case
    //target == 0
    for(int i=0;i<n;i++){
        dp[i][0] = true;
    }
    
    //i==0
    //for only a[0] == target its true
    dp[0][arr[0]] = true;

    //nested loop 
    for(int i=1;i<n;i++){
        for(int target = 1; target<=k;target++){
            bool notTake = dp[i-1][target]; 

            //Taking the element 
            bool take = false;
            if(arr[i] <= target) take = dp[i-1][target-arr[i]];

            dp[i][target] = take || notTake;
        }
    }
    return dp[n-1][k];
}

//TC: O(n*k) 
//SC: O(k)
bool canPartitionTS(vector<int> &arr, int n, int k){
    //dp[n][k]
    vector<bool> prev(k+1,0), curr(k+1,0);
    prev[0] = curr[0] = 1;
    //Base case
    
    //i==0
    //for only a[0] == target its true
    prev[arr[0]] = true;

    //nested loop 
    for(int i=1;i<n;i++){
        for(int target = 1; target<=k;target++){
            bool notTake = prev[target]; 

            //Taking the element 
            bool take = false;
            if(arr[i] <= target) take = prev[target-arr[i]];

            curr[target] = take || notTake;
        }
        prev = curr;
    }
    return prev[k];
}

int main(){
    int n;
    cin>>n;
    vector<int> arr(n);
    for(auto &i:arr){
        cin>>i;
    }
    int sum = 0;
    for(auto i:arr){
        sum += i;
    }
    if(sum %2==0){
        cout<<canPartitionTS(arr,n,sum/2);
    }
    else    cout<<false;
    return 0;
}