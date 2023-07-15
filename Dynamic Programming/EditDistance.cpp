/*
    Edit Distance 

    Problem Statement:  Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.
                        You have the following three operations permitted on a word:

                        Insert a character
                        Delete a character
                        Replace a character

    Problem Link:   https://leetcode.com/problems/edit-distance/
                    https://www.codingninjas.com/studio/problems/edit-distance_630420?source=youtube&campaign=striver_dp_videos

    Refer:  https://takeuforward.org/data-structure/edit-distance-dp-33/
            https://www.youtube.com/watch?v=fJaKO8FbDdo&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=34
*/
#include<bits/stdc++.h>
using namespace std;

//Recursion
//Time Complexity:Exponential
//Space Complexity: O(n+n)-> Auxillary Space
int editDistanceR(int i, int j, string &s, string &t){
    if(j==0)    return i;
    if(i==0)    return j;

    if(s[i-1] == t[j-1])    return editDistanceR(i-1,j-1,s,t);

    //              Insert                          Delete                      Replace
    return 1+ min(editDistanceR(i,j-1,s,t), min(editDistanceR(i-1,j,s,t), editDistanceR(i-1,j-1,s,t)));
}

//Memomization
//Time Complexity: O(n*m)
//Space Complexity: O(n*m) + O(n+m)
int editDistanceM(int i, int j, string &s, string &t, vector<vector<int>> &dp){
    if(j==0)    return i;
    if(i==0)    return j;

    if(dp[i][j] != -1)  return dp[i][j];

    if(s[i-1] == t[j-1])    return dp[i][j]=editDistanceM(i-1,j-1,s,t,dp);

    //              Insert                          Delete                      Replace
    return dp[i][j]=1 + min(editDistanceM(i,j-1,s,t,dp), min(editDistanceM(i-1,j,s,t,dp), editDistanceM(i-1,j-1,s,t,dp)));
}

//Tabulation
//Time Complexity:
//Space Complexity:
int editDistanceT(string &s, string &t){
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n+1,vector<int>(m+1,0));
    for(int i=0;i<=n;i++)   dp[i][0] = i;
    for(int j=1;j<=m;j++)   dp[0][j] = j;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s[i-1] == t[j-1])   dp[i][j]=dp[i-1][j-1];

            //              Insert                     Delete         Replace
            else    dp[i][j] = 1 + min(dp[i][j-1], min(dp[i-1][j], dp[i-1][j-1]));
        }
    }
    return dp[n][m];
}

//Tabulation Space Optimization
//Time Complexity:
//Space Complexity:
int editDistanceTS(string &s, string &t){
   int n = s.size(), m = t.size();
    vector<int> prev(m+1,0), curr(m+1,0);

    for(int j=1;j<=m;j++)   prev[j] = j;

    for(int i=1;i<=n;i++){
        //base case if(j==0)    return i;
        curr[0] = i;
        for(int j=1;j<=m;j++){
            if(s[i-1] == t[j-1])   curr[j]=prev[j-1];

            //              Insert                     Delete         Replace
            else    curr[j] = 1 + min(curr[j-1], min(prev[j], prev[j-1]));
        }
        prev = curr;
    }
    return prev[m];
}

int main(){
    string s,t;
    cin>>s>>t;
    int n = s.size(), m = t.size();

    vector<vector<int>> dp(n+1,vector<int>(m+1,-1));

    cout<<editDistanceTS(s,t);
    return 0;
}