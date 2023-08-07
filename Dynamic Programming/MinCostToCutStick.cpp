/*
    Minimum Cost to Cut the Stick

    Problem Statement:  Given a wooden stick of length n units. The stick is labelled from 0 to n.
                        Given an integer array cuts where cuts[i] denotes a position you should perform a cut at.
                        You should perform the cuts in order, you can change the order of the cuts as you wish.
                        The cost of one cut is the length of the stick to be cut, the total cost is the sum of costs of all cuts. When you cut a stick, it will be split into two smaller sticks (i.e. the sum of their lengths is the length of the stick before the cut). Please refer to the first example for a better explanation.
                        Return the minimum total cost of the cuts.

    Problem Link:   https://leetcode.com/problems/minimum-cost-to-cut-a-stick/

    Refer:  https://takeuforward.org/data-structure/minimum-cost-to-cut-the-stick-dp-50/
            https://www.youtube.com/watch?v=xwomavsC86c&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=51

*/

#include<bits/stdc++.h>
using namespace std;

//Recursive function
//Time Complexity:  O(2^n * n) -> Exponential
//Space Complexity: O(n) -> Auxillary Space
int costOfCuttingR(int i, int j, vector<int> &cuts){
    //base case:
    if(i>j) return 0;

    int mini = 1e9;
    //partition
    for(int k=i; k<=j; k++){
        int cost = (cuts[j+1] - cuts[i-1]) + costOfCuttingR(i,k-1,cuts) + costOfCuttingR(k+1,j, cuts);
        mini = min(mini, cost); 
    }
    return mini;
}

//Memomization
//Time Complexity:  O(n^3)
//Space Complexity: O(n^2) + O(n)
int costOfCuttingM(int i, int j, vector<int> &cuts, vector<vector<int>> &dp){
    if(i>j) return 0;

    if(dp[i][j] != -1)  return dp[i][j];

    int mini = 1e9;
    for(int k=i; k<=j; k++){
        int cost = cuts[j+1] - cuts[i-1] + costOfCuttingM(i,k-1,cuts,dp) + costOfCuttingM(k+1,j,cuts,dp);
        mini = min(mini, cost);
    }
    return dp[i][j] = mini;
}

//Tabulation
//Time Complexity:  O(n^3)
//Space Complexity: O(n^2)
int costOfCuttingT(vector<int> &cuts){
    int c = cuts.size()-2;
    vector<vector<int>> dp(c+2, vector<int>(c+2,0));

    for(int i=c; i>=1; i--){
        for(int j=1; j<=c; j++){
            //base case
            if(i>j) continue;

            int mini = 1e9;
            for(int k=i; k<=j; k++){
                int cost = cuts[j+1] - cuts[i-1] + dp[i][k-1] + dp[k+1][j];
                mini = min(mini, cost);
            }
            dp[i][j] = mini;
        }
    }
    return dp[1][c];
}

int main(){
    int n,c;
    cin>>n>>c;
    vector<int> cuts(c);
    for(auto &i:cuts)    cin>>i;

    cuts.push_back(n);
    cuts.insert(cuts.begin(), 0);
    sort(cuts.begin(), cuts.end());

    vector<vector<int>> dp(c+1, vector<int> (c+1,-1));
    cout<<costOfCuttingT(cuts);
    
    return 0;
}