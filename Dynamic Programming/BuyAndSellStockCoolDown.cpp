/*
    Best Time to Buy and Sell Stock with Cooldown

    Problem Statement:  You are given an array prices where prices[i] is the price of a given stock on the ith day.
                        Find the maximum profit you can achieve. You may complete as many transactions as you like (i.e., buy one and sell one share of the stock multiple times) with the following restrictions:
                        After you sell your stock, you cannot buy stock on the next day (i.e., cooldown one day).
                        Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

    Problem Link:   https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/
                    https://www.codingninjas.com/studio/problems/best-time-to-buy-and-sell-stock-with-cooldown_3125969

    Refer:  https://takeuforward.org/data-structure/buy-and-sell-stocks-with-cooldown-dp-39/
            https://www.youtube.com/watch?v=IGIe46xw3YY&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=40
*/

#include<bits/stdc++.h>
using namespace std;

//Recursion
//Time Complexity: Exponential
//Space Complexity: O(N)
int stockProfitR(int i, int buy, vector<int> &prices){
    //base case would be same as for ul transcation
    //As we are doing i+2 there can be case of out of bound of case
    if(i>=prices.size())    return 0;

    if(buy == 1) return max(-prices[i] + stockProfitR(i+1,0,prices), 0+stockProfitR(i+1,1,prices));

    //Cooldown is when we sell a stock I can't buy it on next day but I can buy on day after that 
    else    return max( prices[i] + stockProfitR(i+2,1,prices), 0 + stockProfitR(i+1,0,prices));
}

//Memomization
//Time Complexity: O(N*2)
//Space Complexity: O(N*2) + O(N)
int stockProfitM(int i, int buy, vector<int> &prices, vector<vector<int>> &dp){
    if(i>=prices.size())    return 0;

    if(dp[i][buy] != -1)    return dp[i][buy];

    if(buy) return dp[i][buy] = max(-prices[i] + stockProfitM(i+1,0,prices,dp), 0+stockProfitM(i+1,1,prices,dp));

    return dp[i][buy] = max(prices[i]+stockProfitM(i+2,1,prices,dp), 0+stockProfitM(i+1,0,prices,dp));
}

//Tabulation
//Time Complexity:O(N)
//Space Complexity:O(N*2)
int stockProfitT(vector<int> &prices){
    int n = prices.size();
    vector<vector<int>> dp(n+2, vector<int>(2,0));

    for(int i=n-1;i>=0;i--){
        dp[i][1] = max(-prices[i] + dp[i+1][0], 0 + dp[i+1][1]);

        dp[i][0] = max(prices[i] + dp[i+2][1], 0 + dp[i+1][0]);
    }
    return dp[0][1];
}

//Space Oprimisation
//Time Complexity:
//Space Complexity:
int stockProfitTS(vector<int> &prices){
    int n = prices.size();
    vector<int> front1(2,0), front2(2,0), curr(2,0);

    for(int i=n-1;i>=0;i--){
        curr[1] = max(-prices[i] + front1[0], front1[1]);

        curr[0] = max(prices[i] + front2[1], front1[0]);

        front2 = front1;
        front1 = curr;
    }
    return curr[1];
}

int main(){
    int n;
    cin>>n;
    vector<int> prices(n);
    for(auto &i:prices) cin>>i;

    vector<vector<int>> dp(n, vector<int> (2,-1));
    cout<<stockProfitTS(prices);
    return 0;
}