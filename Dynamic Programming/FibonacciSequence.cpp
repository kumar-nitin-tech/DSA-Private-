#include<bits/stdc++.h>
using namespace std;

//Brute normal recursive solution
int fiboBrute(int n){
    if(n<=1){
        return  n;
    }
    return fiboBrute(n-2) + fiboBrute(n-1);
}

//Memoization approach
int fiboMemoization(int n, vector<int> &dp){
    if(n<=1){
        return n;
    }
    if(dp[n] != -1){
        return dp[n];
    }
    return dp[n] = fiboMemoization(n-2,dp) + fiboMemoization(n-1,dp);
}

//Tabulation approach(without space optimization)
int fiboTabulation(int n, vector<int> &dp){
    dp[0] = 0;
    dp[1] = 1;
    for(int i=2;i<=n;i++){
        dp[i] = dp[i-2] + dp[i-1];
    }
    return dp[n];
}

//Tabulation approach using space optimization
int fibonacciTabulation(int n){
    int prev= 0;
    int prev1 = 1;
    for(int i=2;i<=n;i++){
        int temp = prev + prev1;
        prev = prev1;
        prev1 = temp;
    }
    return prev1;
}

int main(){
    int n;
    cin>>n;
    vector<int> dp(n+1,-1);
    cout<<fibonacciTabulation(n);
    return 0;
}