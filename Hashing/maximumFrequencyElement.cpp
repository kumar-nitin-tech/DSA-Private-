#include<bits/stdc++.h>
using namespace std;

int maxFrequencyElement(vector<int>&nums){
    unordered_map<int,int>count;
    int maxFreq = INT_MIN;
    int ans = -1;

    for(int i=0;i<nums.size();i++){
        count[nums[i]]++;
        maxFreq = max(maxFreq,count[nums[i]]);
    }

    for(int i =0;i<nums.size();i++){
        if(maxFreq == count[nums[i]]){
            ans = nums[i];
            break;
        }
    }
    return ans;
}

int main(){
    int n;
    cin>>n;
    vector<int>nums(n);
    
    for(auto &i:nums){
        cin>>i;
    }

    cout<<maxFrequencyElement(nums);
    return 0;
}