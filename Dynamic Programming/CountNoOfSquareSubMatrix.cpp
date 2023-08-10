/*
    Count Square Submatrices with All Ones

    Problem Statement:  Given an n * m matrix of ones and zeros, return how many square submatrices have all ones.

    Problem Link:   https://www.codingninjas.com/studio/problems/count-square-submatrices-with-all-ones_3751502?source=youtube&
                    campaign=striver_dp_videos
                    https://leetcode.com/problems/count-square-submatrices-with-all-ones/

    Refer:  https://takeuforward.org/data-structure/count-square-submatrices-with-all-1s-dp-on-rectangles-dp-56/
            https://www.youtube.com/watch?v=auS1fynpnjo&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=61

*/

#include<bits/stdc++.h>
using namespace std;

int countNoOfSquare(vector<vector<int>> &arr){
    int n = arr.size(), m = arr[0].size();
    vector<vector<int>> dp(n, vector<int> (m,0));
    for(int i=0; i<n; i++){
        dp[i][0] = arr[i][0];
    }  

    for(int j=0; j<m; j++){
        dp[0][j] = arr[0][j];
    }

    for(int i=1; i<n; i++){
        for(int j=1; j<m; j++){
            if(arr[i][j] == 0)  dp[i][j] = 0;

            else    dp[i][j] = min(dp[i-1][j] , min(dp[i][j-1], dp[i-1][j-1])) + 1;
        }
    }

    int sum = 0;
    for(auto i:dp){
        for(auto j:i){
            sum += j;
        }
    }
    return sum;
}

int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> arr(n, vector<int> (m));
    for(auto &i:arr){
        for(auto &j:i)  cin>>j;
    }
    cout<<countNoOfSquare(arr);
    return 0;
}