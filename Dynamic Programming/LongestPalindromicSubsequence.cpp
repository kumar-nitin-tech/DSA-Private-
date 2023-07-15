/*
    Longest Palindromic Subsequence

    Problem statement:  A subsequence is a sequence that can be derived from another sequence by deleting some or no elements without 
                        changing the order of the remaining elements.

    Problem Link:   https://leetcode.com/problems/longest-palindromic-subsequence/
                    https://www.codingninjas.com/studio/problems/longest-palindromic-subsequence_842787

    Refer:  https://takeuforward.org/data-structure/longest-palindromic-subsequence-dp-28/
            https://www.youtube.com/watch?v=6i_T5kkfv4A&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=29
*/

#include<bits/stdc++.h>
using namespace std;

//Recursion
//Time Complexity:  O(2^n * 2^m) -> Exponential
//Space Complexity: O(n)
int lcsR(int i, int j, string s, string t){
    
    //Base Case
    //if(i<0 || j<0)    return 0;

    //Base case if shift the index:
    if(i == 0 || j == 0)  return 0;

    if(s[i-1] == t[j-1])    return 1 + lcsR(i-1,j-1,s,t);

    return max(lcsR(i-1,j,s,t), lcsR(i,j-1,s,t));
}

//Memomization
//Time Complexity:  O(n*m)
//Space Complexity: O(n*m) + O(n+m )
int lcsM(int i, int j, string s, string t, vector<vector<int>> &dp){
         //Base Case
    //if(i<0 || j<0)    return 0;

    //Base case if shift the index:
    if(i == 0 || j == 0)  return 0;

    if(dp[i][j] != -1)    return dp[i][j];

    if(s[i-1] == t[j-1])   return dp[i][j] = 1 + lcsM(i-1,j-1,s,t,dp);

    return dp[i][j] = max(lcsM(i-1,j,s,t,dp), lcsM(i,j-1,s,t,dp));
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
    cin>>s;
    t=s;
    reverse(t.begin(), t.end());
    int i = s.size();
    vector<vector<int>> dp(i+1,vector<int>(i+1,-1));
    cout<<lcsTS(s,t);
    return 0;
}