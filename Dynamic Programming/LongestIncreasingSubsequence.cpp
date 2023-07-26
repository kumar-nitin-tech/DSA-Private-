/*
    Longest Increasing Subsequence

    Problem Statement:  Given an integer array nums, return the length of the longest strictly increasing subsequence.

    Problem Link:   https://leetcode.com/problems/longest-increasing-subsequence/
                    https://www.codingninjas.com/studio/problems/longest-increasing-subsequence_630459

    Refer:  https://takeuforward.org/data-structure/longest-increasing-subsequence-dp-41/
            https://www.youtube.com/watch?v=ekcwMsSIzVc&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=42
*/

#include<bits/stdc++.h>
using namespace std;

//Recursion
//Time Complexity:
//Space Complexity:
int lisR(int i, int prevind, vector<int> &arr){
    //base case:
    if(i == arr.size()) return 0;

    //not take
    int notTake = lisR(i+1,prevind, arr);

    //take
    int take = 0;
    if(prevind == -1 || arr[i] > arr[prevind]) take = 1 + lisR(i+1,i,arr);

    return max(take,notTake);
}

//Memomization
//Time Complexity:
//Space Complexity:
int lisM(int i, int prevind, vector<int> &arr, vector<vector<int>>  &dp){
     //base case:
    if(i == arr.size()) return 0;

    //Coordinate approach
    if(dp[i][prevind+1] != -1)    return dp[i][prevind+1];

    //not take
    int notTake = lisM(i+1,prevind, arr,dp);

    //take
    int take = 0;
    if(arr[i] > arr[prevind] || prevind == -1) take = 1 + lisM(i+1,i,arr,dp);

    return dp[i][prevind+1] = max(take,notTake);
}

//Tabulation
//Time Complexity:
//Space Complexity:
int lisT(vector<int> &arr){
    int n = arr.size();
    vector<vector<int>> dp(n+1,vector<int>(n+1,0));

    for(int i = n-1; i>=0; i--){
        for(int prevind = i-1; prevind>=-1; prevind--){
            //not take
            int notTake = dp[i+1][prevind+1];

            //take
            int take = 0;
            if(arr[i] > arr[prevind] || prevind == -1) take = 1 + dp[i+1][i+1];

            dp[i][prevind+1] = max(take,notTake);
        }
    }
    return dp[0][0];
}

//Space Optimisation
int lisTS(vector<int> &arr){
    int n = arr.size();
    vector<int> prev(n+1,0), curr(n+1,0);

    for(int i = n-1; i>=0; i--){
        for(int prevind = i-1; prevind>=-1; prevind--){
            //not take
            int notTake = prev[prevind+1];

            //take
            int take = 0;
            if(arr[i] > arr[prevind] || prevind == -1) take = 1 + prev[i+1];

            curr[prevind+1] = max(take,notTake);
        }
        prev = curr;
    }
    return prev[0];
}

//Most Optimised Solution
int lisO(vector<int> &arr){
    int n = arr.size();
    vector<int> dp(n, 1), hash(n);
    int maxi = 1;
    //Last Index store the index of lenght LIS
    int lastIndex = 0;
    for(int i=0;i<n;i++){
        hash[i] = i;
        for(int prev = 0; prev<i; prev++){
            if(arr[prev] < arr[i] && 1+dp[prev] > dp[i]){
                dp[i] = 1+dp[prev];
                hash[i] = prev;
            }
        }
        if(dp[i] > maxi){
            maxi = dp[i];
            lastIndex = i;
        }
    }

    vector<int> temp;
    //1st element would be the lastIndex value 
    temp.push_back(arr[lastIndex]);
    while(hash[lastIndex] != lastIndex){
        lastIndex = hash[lastIndex];
        temp.push_back(arr[lastIndex]);
    }
    reverse(temp.begin(), temp.end());
    for(auto i:temp)    cout<<i<<" ";
    return maxi;
}

//Using Binary Search Approach is used in the LIS
//Time Complexity: O(N logN)
//Space Complexity: O(N) -> for creating temp array
int longestIncreasingSubsequence(vector<int> &arr){
    //we create a temp array to store the subsequence
    vector<int> temp;
    //We first push the first element 
    temp.push_back(arr[0]);

    //Iterate over the array
    for(int i=1; i<arr.size(); i++){
        //We check the element can be put in the subsequence
        if(arr[i] > temp.back()){
            //If previous element is smaller than current element we push it in the LIS temo array.
            temp.push_back(arr[i]);
        }
        else{
            //Here if the element is not available to push in the LIS means its is smaller than prev
            //We try to overwrite the temp array using lower bound in binary search
            //Lower bound will find the index for first element which is equal to arr[i], or greater than arr[i]
            int ind = lower_bound(temp.begin(), temp.end(), arr[i]) - temp.begin();

            temp[ind] = arr[i];
        }
    }
    return temp.size();
}


int main(){
    int n;
    cin>>n;
    vector<int> arr(n);
    for(auto &i:arr)    cin>>i;

    vector<vector<int>> dp(n, vector<int>(n+1,-1));
    cout<<longestIncreasingSubsequence(arr);
    return 0;
}