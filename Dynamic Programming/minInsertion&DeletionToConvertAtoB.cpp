/*
    Minimum Insertions/Deletions to Convert String A to String B

    Problem statement:  Given two strings str1 and str2. The task is to remove or insert the minimum number of characters from/in 
                        str1 so as to transform it into str2. It could be possible that the same character needs to be removed/deleted from one point of str1 and inserted to some another point.

    Problem Link:   https://practice.geeksforgeeks.org/problems/minimum-number-of-deletions-and-insertions0209/1
                    https://www.codingninjas.com/studio/problems/can-you-make_4244510?source=youtube&campaign=striver_dp_videos

    Refer:  https://takeuforward.org/data-structure/minimum-insertions-deletions-to-convert-string-dp-30/
            https://www.youtube.com/watch?v=yMnH0jrir0Q&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=31
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

    return s.size() + t.size() - (2*(dp[n][m]));
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

    return s.size() + t.size() - (2*(prev[m]));
}

int main(){
    string s,t;
    cin>>s>>t;
    int i = s.size(), j = t.size();
    vector<vector<int>> dp(i+1,vector<int>(j+1,-1));
    int del = s.size() - lcsM(s.size(),t.size(),s,t,dp), ins = t.size()-lcsM(i,j,s,t,dp);
    cout<<lcsTS(s,t);
    return 0;
}