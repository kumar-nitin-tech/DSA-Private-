/*
    Distinct Subsequences

    Problem Statement:  Given two strings s and t, return the number of distinct subsequences of s which equals t.

    Problem Link:   https://leetcode.com/problems/distinct-subsequences/
                    https://www.codingninjas.com/studio/problems/subsequence-counting_3755256?source=youtube&campaign=striver_dp_videos

    Refer:  https://takeuforward.org/data-structure/distinct-subsequences-dp-32/
            https://www.youtube.com/watch?v=nVG7eTiD2bY&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=38
*/

#include<bits/stdc++.h>
using namespace std;

//Recursion
//Time Complexity:Exponential
//Space Complexity: O(n+n)-> Auxillary Space
int countDistinctSubsequenceR(int i, int j, string &s, string &t){
    //base case:
    // if(j<0) return 1;
    // if(i<0) return 0;

    //Improved base case for 1-based indexing
    if(j==0)    return 1;
    if(i==0)    return 0;

    //                          Taking the char for subsequence counting    Not Taking the char 
    if(s[i-1] == t[j-1])    return countDistinctSubsequenceR(i-1,j-1,s,t) + countDistinctSubsequenceR(i-1,j,s,t);

    return countDistinctSubsequenceR(i-1,j,s,t);
}

//Memomization
//Time Complexity: O(n*m)
//Space Complexity: O(n*m) + O(n+m)
int countDistinctSubsequenceM(int i, int j, string &s, string &t, vector<vector<int>> &dp){
    //base case:
    if(j==0)    return 1;
    if(i==0)    return 0;

    //dp check
    if(dp[i][j] != -1)  return dp[i][j];

    if(s[i-1] == t[j-1])    return dp[i][j] = countDistinctSubsequenceM(i-1,j-1,s,t,dp) + countDistinctSubsequenceM(i-1,j,s,t,dp);

    return dp[i][j] = countDistinctSubsequenceM(i-1,j,s,t,dp);
}

//Tabulation
//Time Complexity:O(n*m)
//Space Complexity:O(n*m)
int countDistinctSubsequenceT(string &s, string &t){
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n+1, vector<int> (m+1,0));

    //base case:
    //if(j==0)  means for every i j==0 we have 1 in dp
    for(int i=0;i<=n;i++)    dp[i][0] = 1;

    //Nested Loops
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s[i-1] == t[j-1])  dp[i][j] = dp[i-1][j-1] + dp[i-1][j];

            else dp[i][j] = dp[i-1][j];
        }
    }
    return dp[n][m];
}

//Tabulation Space Optimization
//Time Complexity:O(n*m)
//Space Complexity:O(m)
int countDistinctSubsequenceTS(string &s, string &t){
    int n = s.size(), m = t.size();
    vector<int> prev(m+1,0);

    //base case:
    //if(j==0)  means for every i j==0 we have 1 in dp
    prev[0] = 1;

    //Nested Loops
    for(int i=1;i<=n;i++){
        for(int j=m;j>=1;j--){
            if(s[i-1] == t[j-1])  prev[j] = prev[j-1] + prev[j];

            else prev[j] = prev[j];
        }
    }
    return prev[m];
}

int main(){
    string s,t;
    cin>>s>>t;
    int n = s.size(), m = t.size();

    vector<vector<int>> dp(n+1,vector<int>(m+1,-1));

    cout<<countDistinctSubsequenceT(s,t);
    return 0;
}