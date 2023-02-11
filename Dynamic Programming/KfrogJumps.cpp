#include<bits/stdc++.h>
using namespace std;

//Recursive approach
int KFrogJumpR(int n, int k, vector<int> &heights){
    if(n == 0){
        return 0;
    }
    int minAns =  INT_MAX;
    for(int i=1;i<=k;i++){
        if(n-i >= 0){
            int jump = KFrogJumpR(n-i,k,heights) + abs(heights[n] - heights[n-i]);
            minAns = min(jump,minAns);
        }
        
    }
    return minAns;
}

//Memomization
int KfrogJumpM(int n, int k, vector<int> &heights, vector<int> &dp){
    if(n==0){
        return 0;
    }
    //step 2
    if(dp[n] != -1){
        return dp[n];
    }
    int minAns = INT_MAX;
    for(int i=1;i<=k;i++){
        if(n-i>=0){
            int jump = KfrogJumpM(n-i,k,heights,dp) + abs(heights[n] - heights[n-i]);
            minAns = min(minAns,jump);
        }
    }
    //step 3
    return dp[n] = minAns;
}

//Tabultaion 
int KfrogJumpT(int n, int k, vector<int> &heights, vector<int> &dp){
    /*    if(n==0)
            return 0;
    */
    dp[0] = 0;
    
    for(int i=1;i<n;i++){
        int minANs = INT_MAX;
        for(int j=1;j<=k;j++){
            if(i-j>=0){
                int jumps = dp[i-j] + abs(heights[i] - heights[i-j]);
                minANs = min(minANs,jumps);
            }    
        }
        dp[i] = minANs;
    }
    for(auto i:dp){
        cout<<i<<" ";
    }
    return dp[n-1];
}

int main(){
    int n,k;
    cin>>n>>k;
    vector<int> heights(n);
    for(auto &i:heights){
        cin>>i;
    }
    //step 1
    vector<int> dp(n, -1);
    cout<<KfrogJumpT(n,k,heights,dp);
    return 0;
}