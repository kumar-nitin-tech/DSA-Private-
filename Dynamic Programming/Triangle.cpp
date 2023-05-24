/*
Given a triangle array, return the minimum path sum from top to bottom.
For each step, you may move to an adjacent number of the row below.
More formally, if you are on index i on the current row, you may move to either index i or index i + 1 on the next row.

Detailed expalanation refer to https://takeuforward.org/data-structure/minimum-path-sum-in-triangular-grid-dp-11/
*/

#include<bits/stdc++.h>
using namespace std;

//Recursive Approach
int minSumR(int i, int j, vector<vector<int>> &triangle){
    if(i == triangle.size()-1){
        return triangle[i][j];
    }

    int down = triangle[i][j] + minSumR(i+1,j,triangle);
    int diagonal = triangle[i][j] + minSumR(i+1,j+1,triangle);

    return min(down,diagonal);
}

//Memomization
int minSumM(int i,int j, vector<vector<int>> &triangle, vector<vector<int>> &dp){
    if(i == triangle.size()-1){
        return triangle[i][j];
    }
    if(dp[i][j] != -1){
        return dp[i][j];
    }
    int down = triangle[i][j] + minSumM(i+1,j,triangle,dp);
    int diagonal = triangle[i][j] + minSumM(i+1,j+1,triangle,dp);

    return dp[i][j] = min(down,diagonal);
}

//Tabulation
int minSumT(vector<vector<int>> &triangle, vector<vector<int>> &dp){
    int n = triangle.size();
    //Intialising the dp for last row and pushing all values of last row in dp
    for(int j=0;j<n;j++){
        dp[n-1][j] = triangle[n-1][j];
    }

    //Now we move opposite to recursion 
    //So
    for(int i=n-2;i>=0;i--){
        //As it is a triangle so start from i as for every i row there are i+1 element
        for(int j=i;j>=0;j--){
            int down = triangle[i][j] + dp[i+1][j];
            int diagonal = triangle[i][j] + dp[i+1][j+1];
            dp[i][j] = min(down,diagonal);
        }
    }
    return dp[0][0];
}

//Space Optimization
int minSumTS(vector<vector<int>> &triangle){
    int n =triangle.size();
    vector<int> prev(n),temp(n,0);;
    for(int j=0;j<n;j++){
        prev[j] = triangle[n-1][j];
    }
    for(int i=n-2;i>=0;i--){
        for(int j=i;j>=0;j--){
            int down = triangle[i][j] + prev[j];
            int diagonal = triangle[i][j] + prev[j+1];
            temp[j] = min(down,diagonal);
        }
        prev =temp;
    }
    return prev[0];
}

int main(){
    int n;
    cin>>n;
    vector<vector<int>> triangle(n,vector<int>(n));

    for(int i=0;i<n;i++){
        for(int j=0;j<=i;j++){
            cin>>triangle[i][j];
        }
    }
    vector<vector<int>> dp(n,vector<int>(n,-1));
    cout<<minSumTS(triangle);
    return 0;
}