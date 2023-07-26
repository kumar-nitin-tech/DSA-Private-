/*
    Buy and Sell Stocks With Transaction Fee

    Problem Statement:  You are given an array prices where prices[i] is the price of a given stock on the ith day, and an integer 
                        fee representing a transaction fee.
                        Find the maximum profit you can achieve. You may complete as many transactions as you like, but you need to pay the transaction fee for each transaction.

    Problem Link:   https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/
                    https://www.codingninjas.com/studio/problems/best-time-to-buy-and-sell-stock-with-transaction-fee_3118974

    Refer:  https://takeuforward.org/data-structure/buy-and-sell-stocks-with-transaction-fees-dp-40/
            https://www.youtube.com/watch?v=k4eK-vEmnKg&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=41
*/

#include<bits/stdc++.h>
using namespace std;

//Recursion
//Time Complexity: Exponential
//Space Complexity: O(N)
int stockProfitR(int i, int buy, int fee, vector<int> &prices){
    //base case would be same as for ul transcation
    //As we are doing i+2 there can be case of out of bound of case
    if(i>=prices.size())    return 0;

    if(buy == 1) return max(-prices[i] + stockProfitR(i+1,0,fee,prices), 0+stockProfitR(i+1,1,fee,prices));

    //Cooldown is when we sell a stock I can't buy it on next day but I can buy on day after that 
    else    return max( prices[i] + stockProfitR(i+1,1,fee,prices) - fee, 0 + stockProfitR(i+1,0,fee,prices));
}

//Memomization
//Time Complexity: O(N*2)
//Space Complexity: O(N*2) + O(N)
int stockProfitM(int i, int buy, int fee, vector<int> &prices, vector<vector<int>> &dp){
    if(i>=prices.size())    return 0;

    if(dp[i][buy] != -1)    return dp[i][buy];

    if(buy) return dp[i][buy] = max(-prices[i] + stockProfitM(i+1,0,fee,prices,dp), 0+stockProfitM(i+1,1,fee,prices,dp));

    return dp[i][buy] = max(prices[i]+stockProfitM(i+1,1,fee,prices,dp) - fee, 0+stockProfitM(i+1,0,fee,prices,dp));
}

//Tabulation
//Time Complexity:O(N)
//Space Complexity:O(N*2)
int stockProfitT(int fee, vector<int> &prices){
    int n = prices.size();
    vector<vector<int>> dp(n+1, vector<int>(2,0));

    for(int i=n-1;i>=0;i--){
        dp[i][1] = max(-prices[i] + dp[i+1][0], 0 + dp[i+1][1]);

        dp[i][0] = max(prices[i] + dp[i+1][1] -fee, 0 + dp[i+1][0]);
    }
    return dp[0][1];
}

//Space Oprimisation
//Time Complexity: O(N)
//Space Complexity: O(1)
int stockProfitTS(int fee,vector<int> &prices){
    int n = prices.size();
    int aheadBuy,aheadSell, currBuy, currSell;

    aheadBuy = aheadSell = 0;

    for(int i=n-1;i>=0;i--){
        currBuy = max(-prices[i] + aheadSell, aheadBuy);

        currSell = max(prices[i] + aheadBuy - fee,aheadSell);

        aheadBuy = currBuy;
        aheadSell = currSell;
    }
    return currBuy;
}

int main(){
    int n, fee;
    cin>>n>>fee;
    vector<int> prices(n);
    for(auto &i:prices) cin>>i;

    vector<vector<int>> dp(n, vector<int> (2,-1));
    cout<<stockProfitTS(fee,prices);
    return 0;
}