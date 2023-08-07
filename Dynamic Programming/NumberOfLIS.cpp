/*
    Number of Longest Increasing Subsequences

    Problem Statement:  Given an integer array nums, return the number of longest increasing subsequences.

    Problem Link:   https://leetcode.com/problems/number-of-longest-increasing-subsequence/
                    https://www.codingninjas.com/studio/problems/number-of-longest-increasing-subsequence_3751627

    Refer:  https://takeuforward.org/data-structure/number-of-longest-increasing-subsequences-dp-47/
            https://www.youtube.com/watch?v=cKVl1TFdNXg&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY

*/

#include<bits/stdc++.h>
using namespace std;

//Optimal Approach -> We use algorithmic approach to find lis 
//TC: O(n2) + O(n)
//Sc: O(n)
int numberOfLIS(vector<int> &arr){
    int n = arr.size();
    //We declare 2 array one for keep LIS lenght and another for counting the occurence
    vector<int> dp(n,1), count(n,1);
    int maxi = 1;
    //Iterate from 1->n in the arr
    for(int i=1; i<n; i++){
        //Iterating from 0->i for checking the prev
        for(int j=0; j<i; j++){
            //checking if arr[i] > arr[j] than we can make a LIS and we update the dp[i] to max of dp[i] or 1+dp[j]-> which prev
            if(arr[i] > arr[j] && 1+dp[j]> dp[i]){
                dp[i] = 1+dp[i];
                //We doesn;t fing any element whose count can be added
                count[i] = count[j];
            }
            //This means if find adding 1 to prev and it is same with my current than there is count of previous and current as total occurence of the that element
            else if(arr[i] > arr[j] && 1+dp[j] == dp[i]){
                count[i] += count[j];
            }
        }
        maxi = max(maxi,dp[i]);
    }

    int nos = 0;
    //We find the all count of LIS 
    for(int i=0; i<n; i++){
        if(dp[i] == maxi){
            nos += count[i];
        }
    }
    return nos;
}

int main(){
    int n;
    cin>>n;
    vector<int> arr(n);
    for(auto &i:arr)    cin>>i;
    return 0;
}