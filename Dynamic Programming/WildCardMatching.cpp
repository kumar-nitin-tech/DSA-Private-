/*
    Wild Card Matching

    Problem Statement:  Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*' 
                        where:
                        '?' Matches any single character.
                        '*' Matches any sequence of characters (including the empty sequence).
                        The matching should cover the entire input string (not partial).

    Problem Link:   https://leetcode.com/problems/wildcard-matching/
                    https://www.codingninjas.com/studio/problems/wildcard-pattern-matching_701650?source=youtube&campaign=striver_dp_videos

    Refer:  https://takeuforward.org/data-structure/wildcard-matching-dp-34/
            https://www.youtube.com/watch?v=ZmlQ3vgAOMo&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=40
*/

#include<bits/stdc++.h>
using namespace std;

//Recursive 
//Time Complexity:  Exponential
//Space Complexity: O(N+M)
bool wildCardMatchingR(int i, int j, string &s, string &t){
    if(i<0 && j<0)  return true;
    if(i<0 && j>=0) return false;
    if(j<0 && i>=0){
        for(int it= 0 ;it<=i; it++){
            if(s[it] != '*')    return false;
        }
        return true;
    } 

    //match
    if(s[i] == t[j] || s[i-1] == '?')  return wildCardMatchingR(i-1,j-1,s,t);

    if(s[i] == '*'){
        return wildCardMatchingR(i-1,j,s,t) || wildCardMatchingR(i,j-1,s,t);
    }
    return false;
}

//Memomization 
//Time Complexity:  O(n*m)
//Space Complexity: O(N*M) + O(N+M)
bool wildCardMatchingM(int i, int j,string &s, string &t, vector<vector<bool>> &dp){
    if(i==0 && j == 0)  return true;
    if(i==0 && j>0) return false;
    if(j==0 && i>0){
        for(int it= 1;it<=i; it++){
            if(s[it-1] != '*')    return false;
        }
        return true;
    } 

    if(dp[i][j] != -1)  return dp[i][j];  

    //match
    if(s[i-1] == t[j-1] || s[i-1] == '?')  return dp[i][j] = wildCardMatchingM(i-1,j-1,s,t,dp);

    if(s[i-1] == '*'){
        return dp[i][j] = wildCardMatchingM(i-1,j,s,t,dp) || wildCardMatchingM(i,j-1,s,t,dp);
    }
    return dp[i][j] = false;
}

//Tabulation 
//Time Complexity:  O(n*m)
//Space Complexity: O(N*M)
bool wildCardMatchingT(string &s, string &t){
    int n = s.size(), m = t.size();
    vector<vector<bool>> dp(n+1, vector<bool>(m+1,0));

    //base case:
    dp[0][0] = 1;

    for(int j=1;j<=m;j++)   dp[0][j] = 0;

    for(int i=1; i<=n;i++){
        bool flag = true;
        for(int it= 1;it<=i; it++){
            if(s[it-1] != '*'){
                flag = false;
                break;
            }
        }
        dp[i][0] = flag;
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s[i-1] == t[j-1] || s[i-1] == '?')  dp[i][j] = dp[i-1][j-1];

            else if(s[i-1] == '*'){
                dp[i][j] = dp[i-1][j] || dp[i][j-1];
            }
            else dp[i][j] = false;
        }
    }
    return dp[n][m];
}

//Tabulation Space Optimisation 
//Time Complexity:  O(n*m)
//Space Complexity: O(N*M)
bool wildCardMatchingTS(string &s, string &t){
    int n = s.size(), m = t.size();
    vector<int> prev(m+1,0), curr(m+1,0);

    //base case:
    prev[0] = 1;

    for(int j=1;j<=m;j++)   prev[j] = 0;

    for(int i=1;i<=n;i++){
        bool flag = true;
        for(int it= 1;it<=i; it++){
            if(s[it-1] != '*'){
                flag = false;
                break;
            }
        }
        curr[0] = flag;
        for(int j=1;j<=m;j++){
            if(s[i-1] == t[j-1] || s[i-1] == '?')  curr[j] = prev[j-1];

            else if(s[i-1] == '*'){
                curr[j] = prev[j] || curr[j-1];
            }
            else curr[j] = false;
        }
        prev = curr;
    }
    return prev[m];
}

int main(){
    string s,t;
    cin>>s>>t;
    int n = s.size(), m = t.size();
    vector<vector<bool>> dp(n+1,vector<bool> (m,-1));
    cout<<wildCardMatchingTS(s,t);
    return 0;
}