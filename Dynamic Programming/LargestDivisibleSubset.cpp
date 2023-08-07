/*
    Largest Divisible Subset

    Problem Statement:  Given a set of distinct positive integers nums, return the largest subset answer such that every pair (answer
                        [i], answer[j]) of elements in this subset satisfies:

                        answer[i] % answer[j] == 0, or
                        answer[j] % answer[i] == 0
                        If there are multiple solutions, return any of them.

    Problem Link:   https://leetcode.com/problems/largest-divisible-subset/
                    https://www.codingninjas.com/studio/problems/divisible-set_3754960

    Refer:  https://takeuforward.org/data-structure/longest-divisible-subset-dp-44/
            https://www.youtube.com/watch?v=gDuZwBW9VvM&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=45
*/

#include<bits/stdc++.h>
using namespace std;

//Optimal approach
//TC:   O(n^2) + O(n)
//SC:   O(n)
vector<int> LDS(vector<int> &arr){
    int n = arr.size();
    vector<int> dp(n, 1), hash(n);
    sort(arr.begin(), arr.end());
    int maxi = 1;
    //Last Index store the index of lenght LIS
    int lastIndex = 0;
    for(int i=0;i<n;i++){
        hash[i] = i;
        for(int prev = 0; prev<i; prev++){
            if(arr[i] % arr[prev] == 0 && 1+dp[prev] > dp[i]){
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
    
    return temp;
}


int main(){
    int n;
    cin>>n;
    vector<int> arr(n);

    for(auto &i:arr)    cin>>i;

    vector<int> ans = LDS(arr);

    for(auto i:ans) cout<<i<<" ";
    return 0;
}