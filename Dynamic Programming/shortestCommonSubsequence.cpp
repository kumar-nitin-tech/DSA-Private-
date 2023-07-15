/*
    Shortest Common Supersequence

    Problem statement:  We are given two strings ‘S1’ and ‘S2’. We need to return their shortest common supersequence. A 
                        supersequence is defined as the string which contains both the strings S1 and S2 as subsequences.

    Problem Link:   https://leetcode.com/problems/shortest-common-supersequence/
                    https://www.codingninjas.com/studio/problems/shortest-supersequence_4244493?source=youtube&campaign=striver_dp_videos

    Refer:  https://takeuforward.org/data-structure/shortest-common-supersequence-dp-31/
            https://www.youtube.com/watch?v=xElxAuBcvsU&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=32
*/

#include<bits/stdc++.h>
using namespace std;

//Tabulation
//Time Complexity:  O(n*m)
//Space Complexity: O(n*m)
void scsT(string &s, string &t){
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
    int i = n, j=m;
    string ans = "";
    while(i>0 && j>0){
        if(s[i-1] == t[j-1]){
            ans += s[i-1];
            i--;j--;
        }
        else if(dp[i-1][j] > dp[i][j-1]){
            ans += s[i-1];
            i--;
        }
        else{
            ans += t[j-1];
            j--;
        }
    }

    while(i>0){
        ans += s[i-1];
        i--;
    }
    while(j>0){
        ans += t[j-1];
        j--;
    }

    reverse(ans.begin(), ans.end());

    cout<<ans;
}


int main(){
    string s,t;
    cin>>s>>t;
    scsT(s,t);
    return 0;
}