#include<bits/stdc++.h>
using namespace std;

//recursive approach
//TC: O(2^N)
//SC: O(n)
int energy(int n, vector<int> &height){
    if(n==0){
        return 0;
    }
    int leftEnergyLoss = energy(n-1,height) + abs(height[n] - height[n-1]);
    int rightEnergyLoss = INT_MAX;
    if(n>1) 
        rightEnergyLoss = energy(n-2,height) + abs(height[n] - height[n-2]); 

    return min(leftEnergyLoss,rightEnergyLoss);
}

//memozation approach
//TC: O(n)
//SC: O(n) + O(n)
int energyLossMemo(int n, vector<int> &height, vector<int> &dp){
    if(n==0){
        return 0;
    }
    if(dp[n] != -1){
        return dp[n];
    }
    int left = energyLossMemo(n-1,height,dp) + abs(height[n] - height[n-1]);
    int right = INT_MAX;
    if(n>1){
        right = energyLossMemo(n-2,height,dp) + abs(height[n] - height[n-2]);
    }

    return dp[n] = min(left,right);
}

//Tabulation Approach
int energyLossTab(int n, vector<int> &height, vector<int> &dp){
    dp[0] = 0;

    for(int i=1;i<=n;i++){
        int left = dp[i-1] + abs(height[i] - height[i-1]);
        int right = INT_MAX;
        if(i>1)
            right = dp[i-2] + abs(height[i] - height[i-2]);

        dp[i] = min(left,right);
    
    }
    return dp[n-1];
}

//Tabulation with space optiization
int energyLossTabSpace(int n, vector<int> &height){
    int prev = 0;
    int prev1 = 0;
    int minAns = INT_MAX;
    for(int i=1;i<n;i++){
        int left = prev + abs(height[i] - height[i-1]);
        int right = INT_MAX;
        if(i>1) right = prev1 + abs(height[i] - height[i-2]);
        minAns = min(left,right);
        prev = prev1;
        prev1 = minAns;
    }
    return prev1;
}

int main(){
    int n;
    cin>>n;
    vector<int> height(n);
    for(auto &i:height){
        cin>>i;
    }
    vector<int> dp(n+1,-1);
    cout<<energyLossTabSpace(n,height);
    return 0;
}