#include<bits/stdc++.h>
using namespace std;

//recursive approach
int maxSumSubSequenceR(vector<int> &nums, int n){
    if(n==0){
        return nums[n];
    }
    if(n<0){
        return 0;
    }

    int incl = nums[n] + maxSumSubSequenceR(nums,n-2);
    int excl = 0 + maxSumSubSequenceR(nums,n-1);
    return max(incl,excl);
}

//memomization
int maxSumSubsequenceM(vector<int> &nums, vector<int> &dp, int n){
    if(n==0)    return nums[n];
    if(n<0)     return 0;
    if(dp[n] != -1){
        return dp[n];
    }
    int include = nums[n] + maxSumSubsequenceM(nums,dp,n-2);
    int exclude = 0 + maxSumSubsequenceM(nums,dp,n-1);

    return dp[n] = max(include,exclude);
}

//Tabulation
int maxSumSubsequenceT(vector<int> &nums){
    int n = nums.size();
    vector<int> dp(n,-1);
    dp[0] = nums[0];
    for( int i=1;i<n;i++){
        int pick = nums[i];
        if(i>1) pick += dp[i-2];
        int notpick = 0 + dp[i-1];
        dp[i] = max(pick,notpick);
    }
    return dp[n-1];
}

//Tabulation space optimazation
int maxSumSubsequenceTS(vector<int> &nums){
    int prev = nums[0];
    int prev2 = 0;
    for(int i=1;i<nums.size();i++){
        int pick = nums[i] + prev2;
        int notPick = 0 + prev;
        int ans = max(pick,notPick);
        prev2 = prev;
        prev = ans;
    }
    return prev;
}

int main(){
    int n;
    cin>>n;
    vector<int> nums(n);
    for(auto &i:nums){
        cin>>i;
    }
    vector<int> dp(n+1 , -1);
    cout<<maxSumSubsequenceTS(nums);
    return 0;
}