/*
    Print Longest Common Subsequence

    Problem Statement:  print the actual string of the longest common subsequence. 

    Refer:  https://takeuforward.org/data-structure/print-longest-common-subsequence-dp-26/
            https://www.youtube.com/watch?v=-zI4mrF2Pb4&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=27
*/

#include<bits/stdc++.h>
using namespace std;

//Tabulation
//Time Complexity:  O(n*m)
//Space Complexity: O(n*m)
void printLcsT(string &s, string &t){
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
    int ansSize = dp[n][m];
    string ans = "";

    for(int k=1;k<=ansSize;k++)  ans += "$";

    int ind = ansSize-1;
    int i = n,j=m;
    //Backtracking to print the LCS
    while(i>0 && j>0){
        if(s[i-1] == t[j-1]){
            ans[ind--] = s[i-1];
            i--;j--;
        }
        else if (s[i-1] > t[j-1]){
            i--;
        }
        else    j--;
    }

    cout<<ans;
}

int main(){
    string s,t;
    cin>>s>>t;
    int ind1 = s.size(), ind2 = t.size();

    printLcsT(s,t);
    return 0;
}