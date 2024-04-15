/*
    Find minimum number of coins

    Problem Statement:  Given a value V, if we want to make a change for V Rs, and we have an infinite supply of each of the denominations in Indian currency, i.e., we have an 
                        infinite supply of { 1, 2, 5, 10, 20, 50, 100, 500, 1000} valued coins/notes, what is the minimum number of coins and/or notes needed to make the change.  

    Problem Link:   https://www.naukri.com/code360/problems/find-minimum-number-of-coins_975277

    Refer:  https://takeuforward.org/data-structure/find-minimum-number-of-coins/

*/

#include<bits/stdc++.h>
using namespace std;

vector<int> coin = {1,2,5,10,20,50,100,500,1000};

//Minimum Coin
//TC: O(1)
//SC: O(1)

//This approach only give the minium required for the value
int minimumCoin(int value){
    //we iterate from back in coin array 
    int countCoin = 0;
    for(int i=coin.size()-1; i>=0; i--){
        if(coin[i] <= value){
            int curr = value/coin[i];
            value -= (curr*coin[i]);
            countCoin += curr;
        }
    }
    return countCoin;
}

//For the coin 
//TC: O(V)
//SC: O(N)
void minimumCoinSecond(int value){
    vector<int> ans;
    for(int i=coin.size()-1; i>=0; i--){
        while(value >= coin[i]){
            value -= coin[i];
            ans.push_back(coin[i]);
        }
    }

    cout<<"Coin used are:"<<endl;
    for(auto i:ans){
        cout<<i<<" ";
    }
    cout<<endl;
    cout<<"Minimum coin are: "<<ans.size()<<endl;
}

int main(){
    int value;
    cin>>value;
    minimumCoinSecond(value);
    return 0;
}