/*
    Buy and Sell Stock – IV

    Problem Statement:  You are given an integer array prices where prices[i] is the price of a given stock on the ith day, and an 
                        integer k.
                        Find the maximum profit you can achieve. You may complete at most k transactions: i.e. you may buy at most k times and sell at most k times.
                        Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

    Problem Link:   https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/
                    https://www.codingninjas.com/studio/problems/best-time-to-buy-and-sell-stock-iv_1080698

    Refer:  https://takeuforward.org/data-structure/buy-and-sell-stock-iv-dp-38/
            https://www.youtube.com/watch?v=IV1dHbk5CDc&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=39
*/

#include<bits/stdc++.h>
using namespace std;

//Recursive 
//Time Complexity-> Exponential
//Space Complexity-> O(n) -> auxillary space
int maxProfitR(int i, int trans, int n, int k, vector<int> &prices){
    //For 2 limit we have transcation of 4 
    if(trans == 2*k|| i==n) return 0;
    //Take and not take 
    if(trans % 2 == 0){
        //                          If buy the stock          if i don't buy the stocks
        return max(-prices[i] + maxProfitR(i+1,trans+1,n,k,prices), 0+maxProfitR(i+1,trans,n,k,prices));
    }
    else{
        //                      If sell the stock       if i don't sell the stocks
        return max(prices[i]+maxProfitR(i+1,trans+1,n,k,prices), 0+maxProfitR(i+1,trans,n,k,prices));
    }
}

//Memomization 2
//Time Complexity -> O(n*2) -> O(n)
//Space Complexity-> O(n*2) + O(n) -> O(n)+O(n)
int maxProfitM(int i, int trans, int n, int k, vector<int> &prices, vector<vector<int>> &dp){
    if(trans == 2*k|| i==n) return 0;

    if(dp[i][trans] != -1)    return dp[i][trans];
    //Take and not take 
    if(trans %2 == 0){
        //                          If buy the stock          if i don't buy the stocks
        return dp[i][trans] = max(-prices[i] + maxProfitM(i+1,trans+1,n,k,prices,dp), 0+maxProfitM(i+1,trans,n,k,prices,dp));
    }
        //                      If sell the stock       if i don't sell the stocks
    return dp[i][trans] =  max(prices[i]+maxProfitM(i+1,trans+1,n,k,prices,dp), 0+maxProfitM(i+1,trans,n,k,prices,dp));
}

//Tabulation 
//Time Complexity-> O(n)
//Space Complexity-> O(n*2)
int maxProfitT(int n,int k, vector<int> &prices){
    //Because it needs n and 4 index value to evaluate the curr value
    vector<vector<int>> dp(n+1, vector<int> ((2*k)+1,0));

//As we are already using all value as 0 and we have to assign 0 
    // //base case:
    // for(int i=0;i<n;i++){
    //     for(int buy = 0;buy<=1;buy++){
    //         dp[i][buy][0] = 0;
    //     }
    // }
    // for(int buy = 0; buy<=1; buy++){
    //     for(int cap = 0; cap<=2;cap++){
    //         dp[n][buy][cap] = 0;
    //     }
    // }

    for(int i=n-1;i>=0;i--){
        for(int trans = (2*k)-1; trans>=0; trans--){
            if(trans%2 == 0){
                dp[i][trans] = max(-prices[i] + dp[i+1][trans+1], 0 + dp[i+1][trans]);
            }
            else
                dp[i][trans] =  max(prices[i]+dp[i+1][trans+1], 0 + dp[i+1][trans]);
        }
    }
    return dp[0][0];
}


//Tabulation Space Optimisation 
//Time Complexity-> O(n)
//Space Complexity-> O(1)
int maxProfitTS(int n, int k, vector<int> &prices){
    vector<int> prev((2*k)+1,0), curr((2*k)+1,0);

    for(int i=n-1;i>=0;i--){
        for(int trans = (2*k)-1; trans>=0; trans--){
            if(trans%2 == 0){
                curr[trans] = max(-prices[i] + prev[trans+1], 0 + prev[trans]);
            }
            else
                curr[trans] =  max(prices[i]+prev[trans+1], 0 + prev[trans]);
        }
        prev = curr;
    }
    return prev[0];
}


int main(){
    int n,k;
    cin>>n>>k;
    vector<int> prices(n);
    for(auto &i:prices) cin>>i;

    //vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(3,-1)));
    vector<vector<int>> dp(n,vector<int>(2*k,-1));

    cout<<maxProfitT(n,k,prices);

    return 0;
}