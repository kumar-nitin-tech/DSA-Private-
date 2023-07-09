/*
    Longest Common Subsequence

    Problem Statement:  Given two strings text1 and text2, return the length of their longest common subsequence. If there is                  no common subsequence, return 0.
                        A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.
                        For example, "ace" is a subsequence of "abcde".
                        A common subsequence of two strings is a subsequence that is common to both strings.

    Problem Link:   https://leetcode.com/problems/longest-common-subsequence/
                    https://www.codingninjas.com/studio/problems/longest-common-subsequence_624879?source=youtube&campaign=striver_dp_videos

    Refer:  https://takeuforward.org/data-structure/longest-common-subsequence-dp-25/
            https://www.youtube.com/watch?v=NPZn9jBrX8U&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=28
*/

#include<bits/stdc++.h>
using namespace std;

//Recursion
//Time Complexity:  O(2^n * 2^m) -> Exponential
//Space Complexity: O(n)
int lcsR(int ind1, int ind2, string s1, string s2){
    
    //Base Case
    //if(ind1<0 || ind2<0)    return 0;

    //Base case if shift the index:
    if(ind1 == 0 || ind2 == 0)  return 0;

    if(s1[ind1-1] == s2[ind2-1])    return 1 + lcsR(ind1-1,ind2-1,s1,s2);

    return max(lcsR(ind1-1,ind2,s1,s2), lcsR(ind1,ind2-1,s1,s2));
}

//Memomization
//Time Complexity:  O(n*m)
//Space Complexity: O(n*m) + O(n+m )
int lcsM(int ind1, int ind2, string s1, string s2, vector<vector<int>> &dp){
         //Base Case
    //if(ind1<0 || ind2<0)    return 0;

    //Base case if shift the index:
    if(ind1 == 0 || ind2 == 0)  return 0;

    if(dp[ind1][ind2] != -1)    return dp[ind1][ind2];

    if(s1[ind1-1] == s2[ind2-1])   return dp[ind1][ind2] = 1 + lcsM(ind1-1,ind2-1,s1,s2,dp);

    return dp[ind1][ind2] = max(lcsM(ind1-1,ind2,s1,s2,dp), lcsM(ind1,ind2-1,s1,s2,dp));
}

//Tabulation
//Time Complexity:  O(n*m)
//Space Complexity: O(n*m)
int lcsT(string &s, string &t){
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n+1,vector<int> (m+1,0));

    for(int i = 0;i<=n;i++)  dp[i][0] = 0;

    for(int j = 0;j<=m;j++)  dp[0][j] = 0;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){

            if(s[i-1] == t[j-1])  dp[i][j] = 1 + dp[i-1][j-1];

            else    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }

    return dp[n][m];

}

//Space Optimization
//Time Complexity:  O(n*m)
//Space Complexity: O(m)
int lcsTS(string &s, string &t){
    int n = s.size(), m = t.size();
    vector<int> prev(m+1,0), curr(m+1,0);

    for(int j = 0;j<=m;j++)  prev[j] = 0;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){

            if(s[i-1] == t[j-1])  curr[j] = 1 + prev[j-1];

            else    curr[j] = max(prev[j], curr[j-1]);
        }
        prev = curr;
    }

    return prev[m];
}

int main(){
    string s,t;
    cin>>s>>t;
    int ind1 = s.size(), ind2 = t.size();
    vector<vector<int>> dp(ind1+1,vector<int>(ind2+1,-1));
    cout<<lcsTS(s,t);
    return 0;
}