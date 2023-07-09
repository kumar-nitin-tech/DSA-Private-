/*
    Problem Statement:  A thief wants to rob a store. He is carrying a bag of capacity W.
                        The store has ‘n’ items of infinite supply. Its weight is given by the ‘wt’ array and its value by the ‘val’ array.
                        He can either include an item in its knapsack or exclude it but can’t partially have it as a fraction. 
                        We need to find the maximum value of items that the thief can steal. 
                        He can take a single item any number of times he wants and put it in his knapsack.

    Problem Link:   https://www.codingninjas.com/studio/problems/unbounded-knapsack_1215029?source=youtube&campaign=striver_dp_videos
                    https://practice.geeksforgeeks.org/problems/knapsack-with-duplicate-items4201/1

    Refer:  https://takeuforward.org/data-structure/unbounded-knapsack-dp-23/
            https://www.youtube.com/watch?v=OgvOZ6OrJoY&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=24
    
    Note: cd D:/Coding/C++/DSA/Dynamic Programming/DP Notes/ Unbounded KnapSack
*/

#include<bits/stdc++.h>
using namespace std;

//Recursion
//TC: >>O(2^n) -> Exponential
//SC: O(N) -> Auxiallry Space 
int unboundedKnapSackR(int i, int W, vector<int> &wt, vector<int> &val){
    if(i==0) return ((int)(W/wt[0])) * val[0];

    int notPick = 0 + unboundedKnapSackR(i-1,W,wt,val);
    int pick = 0;
    if(wt[i] <= W)   pick = val[i] + unboundedKnapSackR(i,W-wt[i],wt,val);
    return max(notPick,pick);
}

//Memomization
//TC: O(n*target)
//SC: O(n*target) + O(n)
int unboundedKnapSackM(int i, int W, vector<int> &wt, vector<int> &val, vector<vector<int>> &dp){
    if(i==0) return ((int)(W/wt[0])) * val[0];
    if(dp[i][W] != -1)  return dp[i][W];     
    int notPick = 0 + unboundedKnapSackM(i-1,W,wt,val,dp);
    int pick = 0;
    if(wt[i] <= W)   pick = val[i] + unboundedKnapSackM(i,W-wt[i],wt,val,dp);
    return dp[i][W]=max(notPick,pick);
}

//Tabulation
//TC: O(n*target)
//SC: O(n*target)
int unboundedKnapSackT(int W, vector<int> &wt, vector<int> &val){
    int n = wt.size();
    vector<vector<int>> dp(n, vector<int> (W+1,0));

    for(int w = 0; w<=W;w++){
        dp[0][w] = (w/wt[0])*val[0];
    }

    for(int i=1;i<n;i++){
        for(int w = 0;w<=W;w++){
            int notPick = 0 + dp[i-1][w];
            int pick = 0;
            if(wt[i] <= w)   pick = val[i] + dp[i][w-wt[i]];
            dp[i][w]=max(notPick,pick);
        }
    }

    return dp[n-1][W];
}

//Space Optimisation
//TC:
//SC:
int unboundedKnapSackTS(int W, vector<int> &wt, vector<int> &val){
    int n = wt.size();
    vector<int> prev(W+1,0);

    for(int w = 0; w<=W;w++){
        prev[w] = (w/wt[0])*val[0];
    }

    for(int i=1;i<n;i++){
        for(int w = 0;w<=W;w++){
            int notPick = 0 + prev[w];
            int pick = 0;
            if(wt[i] <= w)   pick = val[i] + prev[w-wt[i]];
            prev[w]=max(notPick,pick);
        }
    }

    return prev[W];
}

int main(){
    int n,W;
    cin>>n>>W;
    vector<int> wt(n), val(n);
    for(auto &i:wt)    cin>>i;
    for(auto &i:val)   cin>>i;
    vector<vector<int>> dp(n,vector<int> (W+1,-1));
    cout<<unboundedKnapSackTS(W,wt,val);

    return 0;
}