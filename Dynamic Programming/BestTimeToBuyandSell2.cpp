/*
    Buy and Sell Stock – II

    Problem Statement:  You are given an integer array prices where prices[i] is the price of a given stock on the ith day.
                        On each day, you may decide to buy and/or sell the stock. You can only hold at most one share of the stock at any time. However, you can buy it then immediately sell it on the same day.

                        Find and return the maximum profit you can achieve.

    Problem Link:   https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/
                    https://www.codingninjas.com/studio/problems/selling-stock_630282?source=youtube&campaign=striver_dp_videos

    Refer:  https://takeuforward.org/data-structure/buy-and-sell-stock-ii-dp-36/
            https://www.youtube.com/watch?v=nGJmxkUJQGs&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=37
*/

#include<bits/stdc++.h>
using namespace std;

//Recursive 
//Time Complexity-> Exponential
//Space Complexity-> O(n) -> auxillary space
int maxProfitR(int i, int buy, int n, vector<int> &prices){

    if(i==n){
        return 0;
    }

    int profit = 0;
    //Take and not take 
    if(buy){
        //                          If buy the stock          if i don't buy the stocks
        profit = max(-prices[i] + maxProfitR(i+1,0,n,prices), 0+maxProfitR(i+1,1,n,prices));
    }
    else{
        //                      If sell the stock       if i don't sell the stocks
        profit = max(prices[i]+maxProfitR(i+1,1,n,prices), 0+maxProfitR(i+1,0,n,prices));
    }
    return profit;
}

//Memomization 
//Time Complexity -> O(n*2) -> O(n)
//Space Complexity-> O(n*2) + O(n) -> O(n)+O(n)
int maxProfitM(int i, int buy, int n, vector<int> &prices, vector<vector<int>> &dp){
     if(i==n){
        return 0;
    }

    if(dp[i][buy] != -1)    return dp[i][buy];

    int profit = 0;
    //Take and not take 
    if(buy){
        //                          If buy the stock          if i don't buy the stocks
        profit = max(-prices[i] + maxProfitM(i+1,0,n,prices,dp), 0+maxProfitM(i+1,1,n,prices,dp));
    }
    else{
        //                      If sell the stock       if i don't sell the stocks
        profit = max(prices[i]+maxProfitM(i+1,1,n,prices,dp), 0+maxProfitM(i+1,0,n,prices,dp));
    }
    return dp[i][buy] = profit;
}

//Tabulation 
//Time Complexity-> O(n)
//Space Complexity-> O(n*2)
int maxProfitT(int n, vector<int> &prices){
    vector<vector<int>> dp(n+1,vector<int> (2,0));

    dp[n][0] = dp[n][1] = 0;
    for(int i=n-1;i>=0;i--){
        for(int buy = 0; buy<=1; buy++){
            int profit = 0;
            //Take and not take 
            if(buy){
                //                          If buy the stock          if i don't buy the stocks
                profit = max(-prices[i] + dp[i+1][0], 0+ dp[i+1][1]);
            }
            else{
                //                      If sell the stock       if i don't sell the stocks
                profit = max(prices[i]+dp[i+1][1], 0+ dp[i+1][0]);
            }
            dp[i][buy] = profit;
        }
    }
    return dp[0][1];
}

//Tabulation Space Optimisation 
//Time Complexity-> O(n)
//Space Complexity-> O(1)
int maxProfitTS(int n, vector<int> &prices){
    vector<int> prev(2,0), curr(2,0);

    prev[0] = prev[1] = 0;
    for(int i=n-1;i>=0;i--){
        for(int buy = 0; buy<=1; buy++){
            int profit = 0;
            //Take and not take 
            if(buy){
                //                          If buy the stock          if i don't buy the stocks
                profit = max(-prices[i] + prev[0], 0+ prev[1]);
            }
            else{
                //                      If sell the stock       if i don't sell the stocks
                profit = max(prices[i]+prev[1], 0+ prev[0]);
            }
            curr[buy] = profit;
        }
        prev = curr;
    }
    return prev[1];
}

//Space Oprimisation with variable
int maxProfitTSS(int n, vector<int> &prices){
    int aheadBuy, aheadNotBuy, currBuy, currNotBuy;
    aheadBuy = aheadNotBuy = 0;
    for(int i=n-1; i>=0;i--){
        currBuy = max(-prices[i] + aheadNotBuy, 0+ aheadBuy);
        currNotBuy = max(prices[i]+aheadBuy, 0+ aheadNotBuy);

        aheadBuy = currBuy;
        aheadNotBuy = currNotBuy;
    }   
    return aheadBuy;
}


int main(){
    int n;
    cin>>n;
    vector<int> prices(n);
    for(auto &i:prices) cin>>i;

    vector<vector<int>> dp(n, vector<int>(2,-1));

    cout<<maxProfitTSS(n,prices);

    return 0;
}