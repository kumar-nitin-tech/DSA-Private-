/*
    Minimum Coins

    Problem Statement:  You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.
                        Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins,
                        return -1.
                        You may assume that you have an infinite number of each kind of coin.

    Problem Link:   https://www.codingninjas.com/codestudio/problems/minimum-elements_3843091?leftPanelTab=0
                    https://leetcode.com/problems/coin-change/

    Refer:  https://takeuforward.org/data-structure/minimum-coins-dp-20/
            https://www.youtube.com/watch?v=myPeWb3Y68A&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=22

    Note:   D:\Coding\C++\DSA\Dynamic Programming\DP Notes\Minimum Coin.pdf
*/

#include<bits/stdc++.h>
using namespace std;

//Recursion
//TC: >>O(2^n) -> Exponential
//SC: O(N) -> Auxiallry Space 
int minimumElementsR(vector<int> &num, int k, int i){
    if(i==0){
        if(k%num[i] ==0)  return k/num[0];
        else return 1e9;
    }

    int notPick = 0+minimumElementsR(num,k,i-1);
    int pick = 1e9;
    if(num[i] <= k) pick = 1+minimumElementsR(num,k-num[i],i);
    return min(notPick,pick);
}

//Memomization
//TC: O(n*k)
//SC: O(n*k) + O(n)
int minimumElementsM(vector<int> &num, int k, int i, vector<vector<int>> &dp){
    if(i==0){
        if(k%num[i] ==0)  return k/num[0];
        else return 1e9;
    }
    if(dp[i][k] != -1)  return dp[i][k];
    int notPick = 0+minimumElementsM(num,k,i-1,dp);
    int pick = 1e9;
    if(num[i] <= k) pick = 1+minimumElementsM(num,k-num[i],i,dp);
    return dp[i][k] = min(notPick,pick);
}

//Tabulation
//TC: O(n*k)
//SC: O(n*k)
int minimumElementsT(vector<int> &num, int x){
    int n = num.size();
    vector<vector<int>> dp(n,vector<int> (x+1,0));

    //base case
    for(int i=0;i<=x;i++){
        if(i%num[0] == 0)   dp[0][i] = i/num[0];
        else dp[0][i] = 1e9;
    }

    //nested loop
    for(int i=1;i<n;i++){
        for(int target = 0; target<=x; target++){
            int notPick = 0+dp[i-1][target];
            int pick = 1e9;
            if(num[i] <= target) 
                pick = 1+dp[i][target-num[i]];

            dp[i][target] = min(pick,notPick);
        }
    }

    return dp[n-1][x];
}

//Space Optimisation
//TC:
//SC:
int minimumElementsTS(vector<int> &num, int x){
    int n = num.size();
    vector<int> prev(x+1,0), curr(x+1,0);

    //base case
    for(int i=0;i<=x;i++){
        if(i%num[0] == 0)   prev[i] = i/num[0];
        else prev[i] = 1e9;
    }

    //nested loop
    for(int i=1;i<n;i++){
        for(int target = 0; target<=x; target++){
            int notPick = 0+prev[target];
            int pick = 1e9;
            if(num[i] <= target) 
                pick = 1+curr[target-num[i]];

            curr[target] = min(pick,notPick);
        }
        prev = curr;
    }

    return prev[x];
}

int main(){
    int n,k;
    cin>>n>>k;
    vector<int> num(n);
    for(auto &i:num)    cin>>i;

    vector<vector<int>> dp(n,vector<int> (k+1,-1));
    cout<<minimumElementsTS(num,k);
    return 0;
}