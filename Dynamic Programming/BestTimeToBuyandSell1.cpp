/*
    Stock Buy and Sell

    Problem Statement:  We are given an array Arr[] of length n. It represents the price of a stock on ‘n’ days. The following 
                        guidelines need to be followed:
                            We can buy and sell a stock only once.
                            We can buy and sell the stock on any day but to sell the stock, we need to first buy it on the same or any previous day.
                        We need to tell the maximum profit one can get by buying and selling this stock.

    Problem Link:   https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
                    https://www.codingninjas.com/studio/problems/stocks-are-profitable_893405?source=youtube&campaign=striver_dp_videos

    Refer:  https://takeuforward.org/data-structure/stock-buy-and-sell-dp-35/
            https://www.youtube.com/watch?v=excAOvwF_Wk&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=36
*/

#include<bits/stdc++.h>
using namespace std;

int maxiProfit(vector<int> &arr){
    int profit = 0, mini = arr[0];

    for(int i=1;i<arr.size();i++){
        int cost = arr[i] - mini;
        profit = max(profit,cost);
        mini = min(mini,arr[i]);
    }
    return profit;
}

int main(){
    int n;
    cin>>n;
    vector<int> arr(n);
    for(auto &i:arr)    cin>>i;

    cout<<maxiProfit(arr);
    return 0;
}