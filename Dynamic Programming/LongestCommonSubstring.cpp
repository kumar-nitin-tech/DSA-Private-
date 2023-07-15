/*
    Longest Common Substring

    Problem statement:  A substring of a string is a subsequence in which all the characters are consecutive. Given two strings, 
                        we need to find the longest common substring.

    Problem Link:   https://www.codingninjas.com/studio/problems/longest-common-substring_1235207?source=youtube&
                    campaign=striver_dp_videos

    Refer:  https://takeuforward.org/data-structure/longest-common-substring-dp-27/
            https://www.youtube.com/watch?v=_wP9mWNPL5w&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=28
*/

#include<bits/stdc++.h>
using namespace std;

//Recursion
//Time Complexity:  O(2^n * 2^m) -> Exponential
//Space Complexity: O(n)
int lcsR(int i, int j, string s, string t, int ans){
    //Base Case
    //if(i<0 || j<0)    return 0;

    //Base case if shift the index:
    if(i==0 || j==0)    return ans;

    if(s[i-1] == t[j-1])    ans = lcsR(i-1,j-1,s,t,ans+1);

    ans = max(ans,max(lcsR(i-1,j,s,t,0), lcsR(i,j-1,s,t,0)));
    return ans;
}

//Memomization
//Time Complexity:  O(n*m)
//Space Complexity: O(n*m) + O(n+m )
int lcsM(int i, int j, string s, string t, vector<vector<int>> &dp, int ans =0){
         //Base Case
    //if(i<0 || j<0)    return 0;

    //Base case if shift the index:
    if(i==0 || j==0)    return ans;

    if(dp[i][j] != -1)  return dp[i][j];

    if(s[i-1] == t[j-1])    ans = lcsR(i-1,j-1,s,t,ans+1);

    ans = max(ans,max(lcsR(i-1,j,s,t,0), lcsR(i,j-1,s,t,0)));
    return dp[i][j] = ans;
}

//Tabulation
//Time Complexity:  O(n*m)
//Space Complexity: O(n*m)
int lcsT(string &s, string &t){
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n+1,vector<int> (m+1,0));

    for(int i = 0;i<=n;i++)  dp[i][0] = 0;

    for(int j = 0;j<=m;j++)  dp[0][j] = 0;

    int ans = 0;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){

            if(s[i-1] == t[j-1]){\
                dp[i][j] = 1 + dp[i-1][j-1];
                ans = max(ans,dp[i][j]);
            }

            else    dp[i][j] = 0;
        }
    }

    return ans;

}

//Space Optimization
//Time Complexity:  O(n*m)
//Space Complexity: O(m)
int lcsTS(string &s, string &t){
    int n = s.size(), m = t.size();
    vector<int> prev(m+1,0), curr(m+1,0);

    for(int j = 0;j<=m;j++)  prev[j] = 0;
    int ans = 0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){

            if(s[i-1] == t[j-1]){
                curr[j] = 1 + prev[j-1];
                ans = max(ans,curr[j]);
            }
            else    curr[j] = 0;
        }
        prev = curr;
    }

    return ans;
}

int main(){
    string s,t;
    cin>>s>>t;
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n+1,vector<int>(m+1,-1));
    cout<<lcsTS(s,t);
    return 0;
}