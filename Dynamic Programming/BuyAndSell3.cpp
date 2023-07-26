/*
    Buy and Sell Stock – III

    Problem Statement:  You are given an array prices where prices[i] is the price of a given stock on the ith day.
                        Find the maximum profit you can achieve. You may complete at most two transactions.
                        Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

    Problem Link:   https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
                    https://www.codingninjas.com/studio/problems/best-time-to-buy-and-sell-stock-iii_1071012

    Refer:  https://takeuforward.org/data-structure/buy-and-sell-stock-iii-dp-37/
            https://www.youtube.com/watch?v=-uQGzhYj8BQ&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=38
*/

#include<bits/stdc++.h>
using namespace std;

//Recursive 
//Time Complexity-> Exponential
//Space Complexity-> O(n) -> auxillary space
int maxProfitR(int i, int buy, int cap, int n, vector<int> &prices){
    if(cap == 0|| i==n) return 0;
    //Take and not take 
    if(buy){
        //                          If buy the stock          if i don't buy the stocks
        return max(-prices[i] + maxProfitR(i+1,0,cap,n,prices), 0+maxProfitR(i+1,1,cap,n,prices));
    }
    else{
        //                      If sell the stock       if i don't sell the stocks
        return max(prices[i]+maxProfitR(i+1,1,cap-1,n,prices), 0+maxProfitR(i+1,0,cap,n,prices));
    }
}

//Recursive 2
//Time Complexity-> Exponential
//Space Complexity-> O(n) -> auxillary space
int maxProfitR2(int i, int trans, int n, vector<int> &prices){
    if(trans == 4|| i==n) return 0;
    //Take and not take 
    if(trans % 2 == 0){
        //                          If buy the stock          if i don't buy the stocks
        return max(-prices[i] + maxProfitR2(i+1,trans+1,n,prices), 0+maxProfitR2(i+1,trans,n,prices));
    }
    else{
        //                      If sell the stock       if i don't sell the stocks
        return max(prices[i]+maxProfitR2(i+1,trans+1,n,prices), 0+maxProfitR2(i+1,trans,n,prices));
    }
}

//Memomization 
//Time Complexity -> O(n*2) -> O(n)
//Space Complexity-> O(n*2) + O(n) -> O(n)+O(n)
int maxProfitM(int i, int buy, int n, int cap,vector<int> &prices, vector<vector<vector<int>>> &dp){
    if(cap == 0|| i==n) return 0;

    if(dp[i][buy][cap] != -1)    return dp[i][buy][cap];
    //Take and not take 
    if(buy){
        //                          If buy the stock          if i don't buy the stocks
        return dp[i][buy][cap] = max(-prices[i] + maxProfitM(i+1,0,n,cap,prices,dp), 0+maxProfitM(i+1,1,n,cap,prices,dp));
    }
        //                      If sell the stock       if i don't sell the stocks
    return dp[i][buy][cap] =  max(prices[i]+maxProfitM(i+1,1,n,cap-1,prices,dp), 0+maxProfitM(i+1,0,n,cap,prices,dp));
}

//Memomization 2
//Time Complexity -> O(n*2) -> O(n)
//Space Complexity-> O(n*2) + O(n) -> O(n)+O(n)
int maxProfitM2(int i, int trans, int n,vector<int> &prices, vector<vector<int>> &dp){
    if(trans == 4|| i==n) return 0;

    if(dp[i][trans] != -1)    return dp[i][trans];
    //Take and not take 
    if(trans %2 == 0){
        //                          If buy the stock          if i don't buy the stocks
        return dp[i][trans] = max(-prices[i] + maxProfitM2(i+1,trans+1,n,prices,dp), 0+maxProfitM2(i+1,trans,n,prices,dp));
    }
        //                      If sell the stock       if i don't sell the stocks
    return dp[i][trans] =  max(prices[i]+maxProfitM2(i+1,trans+1,n,prices,dp), 0+maxProfitM2(i+1,trans,n,prices,dp));
}

//Tabulation 
//Time Complexity-> O(n)
//Space Complexity-> O(n*2)
int maxProfitT(int n, vector<int> &prices){
    vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(2, vector<int> (3,0)));

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
        for(int buy = 0; buy<=1; buy++){
            for(int cap = 1; cap<=2;cap++){
                if(buy == 1){
                    dp[i][buy][cap] = max(-prices[i] + dp[i+1][0][cap], 0 + dp[i+1][1][cap]);
                }
                else
                    dp[i][buy][cap] =  max(prices[i]+dp[i+1][1][cap-1], 0 + dp[i+1][0][cap]);
            }
        }
    }
    return dp[0][1][2];
}

//Tabulation 2
//Time Complexity-> O(n)
//Space Complexity-> O(n*2)
int maxProfitT2(int n, vector<int> &prices){
    //Because it needs n and 4 index value to evaluate the curr value
    vector<vector<int>> dp(n+1, vector<int> (5,0));

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
        for(int trans = 3; trans>=0; trans--){
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
int maxProfitTS(int n, vector<int> &prices){
    vector<vector<int>> prev(2,vector<int>(3,0)), curr(2,vector<int>(3,0));

    for(int i=n-1;i>=0;i--){
        for(int buy = 0; buy<=1; buy++){
            for(int cap = 1; cap<=2;cap++){
                if(buy == 1){
                    curr[buy][cap] = max(-prices[i] + prev[0][cap], 0 + prev[1][cap]);
                }
                else
                    curr[buy][cap] =  max(prices[i]+prev[1][cap-1], 0 + prev[0][cap]);
            }
        }
        prev = curr;
    }
    return prev[1][2];
}

//Tabulation Space Optimisation 
//Time Complexity-> O(n)
//Space Complexity-> O(1)
int maxProfitTS2(int n, vector<int> &prices){
    vector<int> prev(5,0), curr(5,0);

    for(int i=n-1;i>=0;i--){
        for(int trans = 3; trans>=0; trans--){
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
    int n;
    cin>>n;
    vector<int> prices(n);
    for(auto &i:prices) cin>>i;

    //vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(3,-1)));
    vector<vector<int>> dp(n,vector<int>(4,-1));

    cout<<maxProfitTS2(n,prices);

    return 0;
}