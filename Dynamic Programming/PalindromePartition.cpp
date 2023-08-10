/*
    Palindrome Partitioning - II

    Problem Statement:  Given a string s, partition s such that every substring of the partition is a palindrome.
                        Return the minimum cuts needed for a palindrome partitioning of s.

    Problem Link:   https://leetcode.com/problems/palindrome-partitioning-ii/
                    https://www.codingninjas.com/studio/problems/palindrome-partitioning-ll_873266

    Refer:  https://takeuforward.org/data-structure/palindrome-partitioning-ii-front-partition-dp-53/\
            

*/

#include<bits/stdc++.h>
using namespace std;

//check Palindrome
bool isPalindrome(int i, int j, string s){
    while(i<j){
        if(s[i] != s[j])    return false;
        else{
            i++;
            j--;
        }
    }
    return true;
}

//Recursion
//TC:
//SC:
int minPartitionR(int i, int n, string &s){
    if(i==n)    return 0;
    int minCost = 1e9;
    for(int j=i; j<n; j++){
        if(isPalindrome(i,j,s)){
            int cost = 1 + minPartitionR(j+1,n,s);
            minCost = min(minCost,cost);
        }
    }
    return minCost;
}

//Memomization
//TC:
//SC:
int minPartitionM(int i, int n, string &s, vector<int> &dp){
    if(i==n)    return 0;
    if(dp[i] != -1) return dp[i];
    int minCost = 1e9;
    for(int j=i; j<n; j++){
        if(isPalindrome(i,j,s)){
            int cost = 1 + minPartitionM(j+1,n,s,dp);
            minCost = min(minCost,cost);
        }
    }
    return dp[i] = minCost;
}

//Tabulation
//TC:
//SC:
int minPartitionT(string &s){
    int n=s.size();
    vector<int> dp(n+1,0);
    for(int i=n-1; i>=0; i--){
        int minCost = 1e9;
            for(int j=i; j<n; j++){
            if(isPalindrome(i,j,s)){
                int cost = 1 + dp[j+1];
                minCost = min(minCost,cost);
            }
        }
        dp[i] = minCost;
    }
    return dp[0];
}

int minPartitionTS(string &s){
    int n=s.size();
    int next = 0;
    for(int i=n-1; i>=0; i--){
        int minCost = 1e9;
            for(int j=i; j<n; j++){
            if(isPalindrome(i,j,s)){
                int cost = 1 + next;
                minCost = min(minCost,cost);
            }
        }
        next = minCost;
    }
    return next;
}

int main(){
    string s;
    cin>>s;
    int n = s.size();
    vector<int> dp(n,-1);
    cout<<minPartitionTS(s)-1;
    return 0;
}