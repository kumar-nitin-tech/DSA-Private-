/*
    Subset Sum Equals to Target
    Problem Statement:  Given an array of integers nums and an integer k, return the total number of subarrays whose sum equals to k.
                        A subarray is a contiguous non-empty sequence of elements within an array.

    refer : https://takeuforward.org/data-structure/subset-sum-equal-to-target-dp-14/
            https://www.youtube.com/watch?v=fWX9xDmIzRI&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=15
*/

#include<bits/stdc++.h>
using namespace std;

//TC: O(2^n) 
//SC: O(n) :auxillary stack space
bool subSetForKR(int i, vector<int> &arr, int k){
    if(k == 0)  return true;
    if(i == 0)  return k == arr[i];

//not Taking the element 
    bool notTake = subSetForKR(i-1, arr, k); 

//Taking the element 
    bool take = false;
    if(k >= arr[i]) take = subSetForKR(i-1, arr, k-arr[i]);

    return take || notTake;
}

//TC: O(n*k) 
//SC: O(n*k)+O(n) :auxillary stack space
bool subSetForKM(vector<int> &arr, int k, int i, vector<vector<int>> &dp){
    if(k == 0)  return true;
    if(i == 0)  return k == arr[i];

    if(dp[i][k] != -1)  return dp[i][k];
//not Taking the element 
    bool notTake = subSetForKM(arr,k,i-1,dp); 

//Taking the element 
    bool take = false;
    if(k >= arr[i]) take = subSetForKM(arr, k-arr[i],i-1,dp);

    return dp[i][k] = (take || notTake);
}

//TC: O(n*k) 
//SC: O(n*k)
bool subSetForKT(vector<int> &arr, int k){
    int n = arr.size();
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
bool subSetForKTS(vector<int> &arr, int k){
    int n = arr.size();
    //dp[n][k]
    vector<bool> prev(k+1,0), curr(k+1,0);
    prev[0] = curr[0] = 1;
    //Base case
    
    //i==0
    //for only a[0] == target its true
    if(arr[0] <= k) prev[arr[0]] = true;

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
    int n,k;
    cin>>n>>k;
    vector<int> arr(n);
    for(auto &i:arr){
        cin>>i;
    }
    vector<vector<int>> dp(n,vector<int>(k+1,-1));
    cout<<subSetForKTS(arr,k);
    return 0;
}