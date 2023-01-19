/*
    In a candy store, there are N different types of candies available and the prices of all the N different types of candies are provided to you.
You are now provided with an attractive offer.
You can buy a single candy from the store and get at most K other candies ( all are different types ) for free.
Now you have to answer two questions. Firstly, you have to find what is the minimum amount of money you have to spend to buy all the N different candies. Secondly, 
you have to find what is the maximum amount of money you have to spend to buy all the N different candies.
In both the cases you must utilize the offer i.e. you buy one candy and get K other candies for free.
*/

#include<bits/stdc++.h>
using namespace std;

//minimum amount for buying all candies
vector<int> amount(int n, int k, vector<int> &priceCandy){
    sort(priceCandy.begin(), priceCandy.end());
    int minAmt = 0;
    int buy = 0;
    int free = n-1;
    while(buy <= free){
        minAmt += priceCandy[buy];
        buy++;
        free -= k;
    }
    int maxAmt=0;
    buy = n-1;
    free = 0;
    while(buy >= free){
        maxAmt += priceCandy[buy];
        buy--;
        free += k;
    }
    vector<int> ans;
    ans.push_back(minAmt);
    ans.push_back(maxAmt);
    return ans;
}

int main(){
    int n,k;
    cin>>n>>k;
    vector<int> priceCandy(n);
    for(auto &i:priceCandy){
        cin>>i;
    }
    vector<int>ans = amount(n,k,priceCandy);
    for(auto i:ans){
        cout<<i<<" ";
    }
    return 0;
}