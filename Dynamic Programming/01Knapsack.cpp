/*
    0/1 Knapsack 

    Problem Statement:  A thief wants to rob a store. He is carrying a bag of capacity W. 
                        The store has ‘n’ items. Its weight is given by the ‘wt’ array and its value by the ‘val’ array.
                        He can either include an item in its knapsack or exclude it but can’t partially have it as a fraction. 
                        We need to find the maximum value of items that the thief can steal.

    Problem Link:   https://www.codingninjas.com/codestudio/problems/0-1-knapsack_920542?source=youtube&campaign=striver_dp_videos

    Refer:  https://takeuforward.org/data-structure/0-1-knapsack-dp-19/
            https://www.youtube.com/watch?v=GqOmJHQZivw&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=22
*/

#include<bits/stdc++.h>
using namespace std;

//Recursion
//TC: O(2^n)
//SC: O(n) Auxiallary Space 
int knapSackR(vector<int> &weight, vector<int> &value, int i, int maxWeight){
    if(i==0){
        if(weight[0] <= maxWeight)  return value[0];
        else return 0;
    }

    int notTake = 0 + knapSackR(weight,value,i-1,maxWeight);
    int Take = -1e9;
    if(weight[i] <= maxWeight)  Take = value[i] + knapSackR(weight,value,i-1, maxWeight-weight[i]);

    return max(Take,notTake);
}

//Memomization
//TC: O(n*w) w = maxWeight
//SC: O(n*w) + O(n)
int knapSackM(vector<int> &weight, vector<int> &value, int i, int maxWeight, vector<vector<int>> &dp){
    if(i==0){
        if(weight[0] <= maxWeight)  return value[0];
        else return 0;
    }

    if(dp[i][maxWeight] != -1)  return dp[i][maxWeight];

    int notTake = 0 + knapSackM(weight,value,i-1,maxWeight,dp);
    int Take = -1e9;
    if(weight[i] <= maxWeight)  Take = value[i] + knapSackM(weight,value,i-1, maxWeight-weight[i],dp);

    return dp[i][maxWeight] = max(Take,notTake);
}

//Tabulation
//TC: O(n*w) w = maxWeight
//SC: O(n*w)
int knapSackT(vector<int> &weight, vector<int> &value, int n, int maxWeight){
    vector<vector<int>> dp(n, vector<int> (maxWeight+1,0));
    //base Case
    // We can take every value which has weight less than maz weight, so from weight of 0 index to maxWeight we can take
    for(int i = weight[0]; i<=maxWeight;i++) dp[0][i] = value[0];

    //Nested Loops
    //Recursion start from n-1 to 0
    for(int i=1;i<n;i++){
        //In Recursion weight is from MaxWeight to 0
        for(int w = 0;w<=maxWeight;w++){
            int notTake = 0 + dp[i-1][w];
            int take = -1e9;
            if(weight[i] <= w)  take = value[i] + dp[i-1][w- weight[i]];

            dp[i][w] = max(take,notTake);
        }
    }
    return dp[n-1][maxWeight];
}

//Sapce Optimisation
//TC: O(n*w) w = maxWeight
//SC: O(n)
int knapSackTS(vector<int> &weight, vector<int> &value, int n, int maxWeight){
    vector<int> prev(maxWeight+1,0);
    //base Case
    // We can take every value which has weight less than maz weight, so from weight of 0 index to maxWeight we can take
    for(int i = weight[0]; i<=maxWeight;i++) prev[i] = value[0];

    //Nested Loops
    //Recursion start from n-1 to 0
    for(int i=1;i<n;i++){
        //In Recursion weight is from MaxWeight to 0
        for(int w = maxWeight;w>=0;w--){
            int notTake = 0 + prev[w];
            int take = -1e9;
            if(weight[i] <= w)  take = value[i] + prev[w- weight[i]];

            prev[w] = max(take,notTake);
        }
    }
    return prev[maxWeight];
} 

int main(){
    int n,maxWeight;
    cin>>n>>maxWeight;
    vector<int> weight(n), value(n);

    for(auto &i:weight) cin>>i;
    for(auto &i:value) cin>>i;

    vector<vector<int>> dp(n, vector<int>(maxWeight+1,-1));
    cout<<knapSackTS(weight,value,n,maxWeight);
    return 0;
}