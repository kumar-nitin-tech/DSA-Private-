#include<bits/stdc++.h>
using namespace std;

//Time Complexity: O(n)
//Space Complexity: O(1)
vector<int> SumWindowK(vector<int>&nums, int k){
    int sum = 0;
    vector<int>ans;
    for(int i=0;i<k;i++){
        sum += nums[i];
    }
    ans.push_back(sum);
    for(int i=k;i<nums.size();i++){
        sum = sum + nums[i] - nums[i-k];
        ans.push_back(sum);
    }
    return ans;
}
//Time Complexity: O(n)
//Space Complexity: O(1)
int minSumWindowK(vector<int>&nums, int k){
    int sum = 0;
    int minSum = INT_MAX;
    for(int i=0;i<k;i++){
        sum += nums[i];
    }
    minSum = sum;
    for(int i=k;i<nums.size();i++){
        sum = sum + nums[i] - nums[i-k];
        minSum = min(minSum,sum);
    }
    return minSum;
}

int main(){
    int n,k;
    cin>>n>>k;
    vector<int>nums(n);
    for(auto &i:nums){
        cin>>i;
    }
    vector<int>ans;
    ans = SumWindowK(nums,k);
    for(auto i:ans){
        cout<<i<<" ";
    }

    cout<<"\nMinimum Sum of among window size array: "<<minSumWindowK(nums,k);
    return 0;
}